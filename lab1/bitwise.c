#include "bitwise.h"

<<<<<<< HEAD
uint8_t clear(uint8_t msk, int pos) { 
    return msk & ~(1 << pos);
}

uint8_t set(uint8_t msk, int pos) {
    return msk | 1 << pos;
}

bool is_set(uint8_t msk, int pos) {
    return (msk | 1 << pos) == msk;
}

uint8_t lsb(uint16_t wide_msk) {
    return (uint8_t)(wide_msk & 0xFF);
}

uint8_t msb(uint16_t wide_msk) {
    return (uint8_t)(wide_msk >> 8);
}

uint8_t mask(int pos, ...) {
    uint8_t result = 0;
    va_list arguments;

    va_start(arguments, pos);

    int cur = pos;
    while (cur != MSK_END)
    {
        result |= (uint8_t)(1 << cur);

        cur = va_arg(arguments, int);
    }

    va_end(arguments);
    return result;
}
=======
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
  uint8_t m = 0;

  va_list ap;
  va_start(ap, pos);              

  while (pos != MSK_END) {        
    if (pos >= 0 && pos < 8) {
      m |= (uint8_t)(1 << pos);
    }
    pos = va_arg(ap, int);        
  }

  va_end(ap);
  return m;
}


>>>>>>> 20c8c3a53f16cfc0133721d61c000e721f50ecc6
