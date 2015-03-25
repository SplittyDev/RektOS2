#include <types.h>
#include <pit.h>
#include <idt.h>
#include <ports.h>

void pit_init (void) {
  // Initialize the ticks variable
  pit_ticks = 0;

  // Install IRQ handler
  pit_install_handler ();

  // Set frequency to 100hz
  pit_set_frequency (100);
}

void pit_set_frequency (uint8_t hz) {
  uint32_t divisor = 1193182 / hz;
  outb (0x43, 0x36);
  outb (0x40, divisor & 0xFF);
  outb (0x40, divisor >> 8);
}

void pit_install_handler (void) {
  idt_install_handler (PIT_IRQ, pit_handler);
}

void pit_uninstall_handler (void) {
  idt_uninstall_handler (PIT_IRQ);
}

void pit_handler (struct cpu_state *frame) {
  pit_ticks++;
}
