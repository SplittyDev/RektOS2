#ifndef __pit__
#define __pit__

#include <types.h>
#include <idt.h>

#define PIT_IRQ   0

uint32_t pit_ticks;

void pit_init (void);
void pit_set_frequency (uint8_t hz);
void pit_install_handler (void);
void pit_uninstall_handler (void);
void pit_handler (struct cpu_state *frame);

#endif
