#include "mouse.h"
#include "i8042.h"
#define MAX_ATTEMPTS 5
static uint8_t packet_bytes[3];
static uint8_t packet_index = 0;
static struct packet pp;

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