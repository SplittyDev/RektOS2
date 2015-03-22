#include <types.h>
#include <terminal.h>
#include <gdt.h>

// Main entry point
void init (void) {
  asm volatile ("cli");
  terminal_init ();
  puts ("Initializing TextMode [OK]\n");
  puts ("Initializing GDT ");
  gdt_init ();
  puts ("[OK]\n");
  asm volatile ("hlt");
}
