#include "mouse.h"
#include "i8042.h"
#define MAX_ATTEMPTS 5
static uint8_t packet_bytes[3];
static uint8_t packet_index = 0;
static struct packet pp;
uint8_t hook_id_mouse = MOUSE_IRQ;

static int mouse_send_cmd(uint8_t cmd, uint8_t* ack){
    if (kbc_send_command(WRITE_TO_MOUSE) != 0) return 1;
    if (kbc_write_data(cmd) != 0) return 1;
    if (kbc_read_response(ack) != 0) return 1;
    return 0;
}


int mouse_send_command(uint8_t cmd){
    uint8_t ack;
    int attempts = 0;

    while (attempts < MAX_ATTEMPTS){
        if (mouse_send_cmd(cmd,&ack) != 0) return 1;

        if (ack == ACK) return 0;

        attempts++;
    }

    return 1;
}


// This functions is only used if one single command is intended to be sent. If more than one disable first send them and enable again
int mouse_send_command_with_sync(uint8_t cmd) { 
    if (cmd != DISABLE_DATA_REPORTING) {
        if (mouse_send_command(DISABLE_DATA_REPORTING) != 0) return 1;
    }

    if (mouse_send_command(cmd) != 0) return 1;

    if (cmd != ENABLE_DATA_REPORTING && cmd != DISABLE_DATA_REPORTING) {
        if (mouse_send_command(ENABLE_DATA_REPORTING) != 0) return 1;
    }

    return 0;
}

int (mouse_subscribe_int)(uint8_t *bit_no) {
    *bit_no = hook_id_mouse;
    if (sys_irqsetpolicy(KBD_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_id_mouse) != 0) return 1;
    return 0;
}

int (mouse_unsubscribe_int)() {
    if (sys_irqrmpolicy(&hook_id_mouse) != 0) return 1;
    return 0;
}
