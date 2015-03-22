#ifndef __memory__
#define __memory__

#include <types.h>

static inline uint8_t* memcpy (uint8_t *dest, const uint8_t *src, int count) {
  int i = 0;
  for (; i < count; i++)
    dest[i] = src[i];
  return dest;
}

static inline uint16_t memcpyw (uint16_t *dest, const uint16_t *src, int count) {
  int i = 0;
  for (; i < count; i++)
    dest[i] = src[i];
  return dest;
}

static inline uint8_t* memset (uint8_t *dest, uint8_t val, int count) {
  int i = 0;
  for (; i < count; i++)
    dest[i] = val;
  return dest;
}

static inline uint16_t* memsetw (uint16_t *dest, uint16_t val, int count) {
  int i = 0;
  for (; i < count; i++)
    dest[i] = val;
  return dest;
}

#endif
