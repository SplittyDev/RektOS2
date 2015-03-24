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

  // Say hello
  puts ("RektOS 2 is booting...\n");

  // Setup GDT
  gdt_init ();
  puts ("[OK] Setting up GDT\n");

  // Setup PIC
  pic_init ();
  puts ("[OK] Setting up PIC\n");

  // Setup IDT
  idt_init ();
  puts ("[OK] Setting up IDT\n");

  puts ("Dividing by zero\n");
  putc (1 / 0);

  while (true) {
    asm ("cli; hlt");
  }
}
