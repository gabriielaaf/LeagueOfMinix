#pragma once
#include <lcom/lcf.h>


#define ESC 0x01

#define KBD_IRQ 1

#define BREAKCODE BIT(7)

#define CODE_PREFIX 0xE0

#define OUTPUT_BUFFER 0x60

#define INPUT_BUFFER 0x60

#define STATUS_REGISTER 0x64

#define COMMAND_REGISTER 0x64

// Status Register bit-mask

#define PARITY_ERROR BIT(7)
#define TIMEOUT_ERROR BIT(6)
#define AUX BIT(5)
#define INPUT_BUFFER_FULL BIT(1)
#define OUTPUT_BUFFER_FULL BIT(0)
