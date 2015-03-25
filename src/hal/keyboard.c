#include <types.h>
#include <keyboard.h>
#include <keyboard_en.h>
#include <idt.h>
#include <ports.h>
#include <terminal.h>

void keyboard_init (void) {
  // Install handler
  keyboard_install_handler ();

  // Clear LEDs
  keyboard_send_command (0xED);
  keyboard_send_command (0);

  // Fastest refresh-rate
  keyboard_send_command (0xF3);
  keyboard_send_command (0);

  // Activate keyboard
  keyboard_send_command (0xF4);
}

void keyboard_clear_buffer (void) {
  while (inb (CONTROL_REGISTER) & 0x1)
    inb (DATA_REGISTER);
}

uint8_t keyboard_self_test (void) {
  outb (CONTROL_REGISTER, 0xAA);
  return inb (DATA_REGISTER) == 0x55;
}

void keyboard_install_handler (void) {
  idt_install_handler (KEYBOARD_IRQ, keyboard_handler);

}

void keyboard_uninstall_handler (void) {
  idt_uninstall_handler (KEYBOARD_IRQ);
}

void keyboard_send_command (uint8_t com) {
  while (inb (CONTROL_REGISTER) & 0x2);
  outb (DATA_REGISTER, com);
}

void keyboard_test_handler (void) {
  uint8_t scancode = inb (DATA_REGISTER);
  if (scancode & 0x80) {
  } else {
    putc (keymap_en[scancode]);
  }
}

void keyboard_handler (struct cpu_state *frame) {
  // Read from data register
  uint8_t scancode = inb (DATA_REGISTER);

  // Key released
  if (scancode & 0x80) {
  }

  // Key pressed
  else {
    putc (keymap_en[scancode]);
  }
}
