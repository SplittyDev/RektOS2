#ifndef __string__
#define __string__

#include <types.h>

char *itoa (int32_t num, uint8_t buffer[]) {
  uint8_t const digits[] = "0123456789";
  uint8_t *str = buffer;

  // Check if the number is negative
  if (num < 0) {
    *str++ = '-';
    num *= -1;
  }

  int32_t shift = num;
  do {
    ++str;
    shift /= 10;
  } while (shift);

  *str = '\0';

  do {
    *--str = digits[num % 10];
    num /= 10;
  } while (num);

  return str;
}

void strcat (char *str1, char *str2) {
  while (*str1)
    str1++;
  while (*str2) {
    *str1 = *str2;
    str2++;
    str1++;
  }
  *str1 = '\0';
}

uint32_t strlen (const char *str) {
  uint32_t i = 0;
  while (str[i] != '\0')
    i++;
  return i;
}

#endif
