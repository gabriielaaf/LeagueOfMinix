#include <lcom/lcf.h>
#include <string.h>

#include "video.h"
#include "vbe.h"
#include "keyboard.h"
#include "i8042.h"

static char *video_mem;          /* frame-buffer VM address */

/* Other variables that might be used */
static vbe_mode_info_t vmi;      /* VBE mode info */
static unsigned bytes_per_pixel; /* Number of VRAM bytes per pixel */


int(set_vram_mapping)(uint16_t mode) {
  struct minix_mem_range mr;
  unsigned int vram_base;
  unsigned int vram_size;


  if (vbe_get_mode_info(mode, &vmi) != 0) {
    return 1;
  }

  bytes_per_pixel = (vmi.BitsPerPixel + 7) / 8;

  /* Physical address of the framebuffer */
  vram_base = vmi.PhysBasePtr;

  vram_size = vmi.BytesPerScanLine * vmi.YResolution;

  mr.mr_base = (phys_bytes) vram_base;
  mr.mr_limit = mr.mr_base + vram_size;

  if (sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr) != OK) {
    return 1;
  }


  video_mem = vm_map_phys(SELF, (void *) mr.mr_base, vram_size);

  if (video_mem == MAP_FAILED) {
    return 1;
  }

  return 0;
}


int vbe_set_mode(uint16_t mode) {
  reg86_t r86;

  memset(&r86, 0, sizeof(r86));

  r86.intno = BIOS_VIDEO_INT;

  r86.ah = VBE_FUNCTION_AH;
  r86.al = VBE_SET_MODE_AL;

  r86.bx = mode | LINEAR_FRAMEBUFFER;

  if (sys_int86(&r86) != OK) {
    return 1;
  }

  if (r86.al != VBE_SUPPORTED || r86.ah != VBE_SUCCESS) {
    return 1;
  }

  return 0;
}

int(vg_draw_pixel)(uint16_t x, uint16_t y, uint32_t color) {
  if (video_mem == NULL) {
    return 1;
  }

  if (x >= vmi.XResolution || y >= vmi.YResolution) {
    return 1;
  }

  unsigned int offset = y * vmi.BytesPerScanLine + x * bytes_per_pixel;

  memcpy(&video_mem[offset], &color, bytes_per_pixel);

  return 0;
}

int(vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color) {
  if (y >= vmi.YResolution) {
    return 1;
  }

  if ((uint32_t)x + len > vmi.XResolution) {
    return 1;
  }

  for (uint16_t i = 0; i < len; i++) {
    if (vg_draw_pixel(x + i, y, color) != 0) {
      return 1;
    }
  }

  return 0;
}

int(vg_draw_rectangle)(uint16_t x, uint16_t y,
                       uint16_t width, uint16_t height,
                       uint32_t color) {
  if ((uint32_t)x + width > vmi.XResolution) {
    return 1;
  }

  if ((uint32_t)y + height > vmi.YResolution) {
    return 1;
  }

  for (uint16_t row = 0; row < height; row++) {
    if (vg_draw_hline(x, y + row, width, color) != 0) {
      return 1;
    }
  }

  return 0;
}

int wait_for_esc(){
    int r, ipc_status;
    message msg;
    bool running = true;
    uint8_t bit_no;

    if (kbd_subscribe_int(&bit_no) != 0) return 1;
    uint32_t irq_set = BIT(bit_no);

    while (running) {
        if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
            printf("driver_receive failed with: %d", r);
            continue;
        }
        if (is_ipc_notify(ipc_status)) {
            switch (_ENDPOINT_P(msg.m_source)) {
                case HARDWARE:
                    if (msg.m_notify.interrupts & irq_set) {
                        kbd_ih();
                        if (kbd_error) {
                            kbd_error = false;
                            reset_scancode();
                            continue;
                        }
                        if (scancode_complete()) {
                            uint8_t size = get_scancode_size();
                            uint8_t *bytes = get_scancode_bytes();
                            if (size == 1 && bytes[0] == (ESC | BREAKCODE)) running = false;
                            reset_scancode();
                        }
                    }
                    break;
                default:
                    break;
            }
        }
    }

    if (kbd_unsubscribe_int() != 0) return 1;
    return 0;
}
