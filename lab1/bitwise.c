#include "bitwise.h"

#define TODO return 255

uint8_t clear(uint8_t msk, int pos) { 

  uint8_t b = (1<<pos);
  b = ~b;

  return msk & b;

 }

uint8_t set(uint8_t msk, int pos) { 

  uint8_t b = (1<<pos);

  return msk | b;

 }

bool is_set(uint8_t msk, int pos) { 

  return msk & (1<<pos);

 }

uint8_t lsb(uint16_t wide_msk) { 

  return (uint8_t)(wide_msk & 0x00FF);

 }

uint8_t msb(uint16_t wide_msk) {

  return (uint8_t)(wide_msk>>8); 

 }

uint8_t mask(int pos, ...) { 



 }
