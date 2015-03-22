#ifndef __terminal__
#define __terminal__

#include <types.h>

void terminal_init (void);
void putc (const char);
void puts (const char*);
uint8_t makecolor (uint8_t, uint8_t);
void move_cursor (void);
void scroll (void);
void clear (void);

#endif
