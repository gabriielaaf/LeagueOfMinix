#include "keyboard.h"
#include <lcom/lcf.h>

int mouse_send_cmd(uint8_t cmd, uint8_t *ack);

int mouse_send_command(uint8_t cmd);

int mouse_send_command_with_sync(uint8_t cmd);

void (mouse_ih)();