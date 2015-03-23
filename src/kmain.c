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

  // Test IDT/PIC
  asm volatile ("int $0x0");
  asm volatile ("hlt");
}
