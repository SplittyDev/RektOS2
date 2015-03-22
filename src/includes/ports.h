#ifndef __ports__
#define __ports__

#include "types.h"

static inline void outb (uint16_t port, uint8_t value) {
	asm volatile ("outb %0, %1" : : "a" (value), "Nd" (port));
}

static inline void outw (uint16_t port, uint16_t value) {
	asm volatile ("outw %0, %1" : : "a" (value), "Nd" (port));
}

static inline void outl (uint16_t port, uint32_t value) {
	asm volatile ("outl %0, %1" : : "a" (value), "Nd" (port));
}

#endif
