#include <types.h>
#include <terminal.h>
#include <gdt.h>
#include <idt.h>
#include <pic.h>
#include <pit.h>
#include <keyboard.h>

void test (char *msg, void (*func)(void)) {
  puts ("[Init] ");
  puts (msg);
  putc ('\n');
  func ();
  puts ("[ OK ] ");
  puts (msg);
  putc ('\n');
}

// Main entry point
void init (void) {
  // Disable Interrupts
  asm volatile ("cli");

  // Initialize VGA TextMode
  terminal_init ();

  // Setup GDT
  test ("GDT", gdt_init);

  // Setup PIC
  test ("PIC", pic_init);

  // Setup IDT
  test ("IDT", idt_init);

  // Setup PIT with 100hz
  test ("PIT", pit_init);

  // Setup Keyboard
  test ("Keyboard", keyboard_init);

  // Enable Interrupts
  asm volatile ("sti");

  while (true);
}
