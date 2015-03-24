#include <types.h>
#include <terminal.h>
#include <gdt.h>
#include <idt.h>
#include <pic.h>
#include <pit.h>
#include <keyboard.h>

void test (char *msg, void (*func)(void)) {
  puts (msg);
  putc ('\n');
  func ();
}

// Main entry point
void init (void) {
  // Disable Interrupts
  asm volatile ("cli");

  // Initialize VGA TextMode
  terminal_init ();

  // Setup GDT
  test ("Setting up GDT...", gdt_init);

  // Setup PIC
  test ("Remapping PIC...", pic_init);

  // Setup IDT
  test ("Setting up IDT...", idt_init);

  // Setup PIT with 100hz
  test ("Initializing PIT...", pit_init);

  // Setup Keyboard
  test ("Initializing Keyboard...", keyboard_init);

  // Enable Interrupts
  asm volatile ("sti");

  while (true) {
  }
}
