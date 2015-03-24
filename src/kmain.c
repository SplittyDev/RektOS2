#include <types.h>
#include <terminal.h>
#include <gdt.h>
#include <idt.h>

// Main entry point
void init (void) {
  // Disable Interrupts
  asm volatile ("cli");

  // Initialize VGA TextMode
  terminal_init ();
  puts ("[OK] Setting up textmode\n");

  // Setup GDT
  gdt_init ();
  puts ("[OK] Setting up GDT\n");

  // Setup IDT
  idt_init ();
  puts ("[OK] Setting up IDT\n");

  // Setup PIC
  pic_init ();
  puts ("[OK] Setting up PIC\n");

  // Tests
  puts ("Testing divide by zero\n");
  int i = 10 / 0;
  puts ("Testing overflow\n");
  int8_t x = 99999999999999999999;

  puts ("lolwtf");

  while (true) {
    puts ("x");
  }
}
