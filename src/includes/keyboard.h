#ifndef __keyboard__
#define __keyboard__

#include <types.h>
#include <idt.h>

#define KEYBOARD_IRQ      1
#define DATA_REGISTER     0x60
#define CONTROL_REGISTER  0x64

void keyboard_init (void);
void keyboard_install_handler (void);
void keyboard_uninstall_handler (void);
void keyboard_send_command (uint8_t);
void keyboard_handler (struct cpu_state *);

#endif
