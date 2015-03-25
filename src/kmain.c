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

/**
 * Main entry point
 * Called from boot.S
 */
void init (void) {
  /**
   * We don't want any interrupts
   * to fire while we're setting
   * up the essential parts of the kernel.
   */
  disable_interrupts ();

  /**
   * We will need to print some
   * messages.
   */
  terminal_init ();

  /**
   * The GDT (Global Descriptor Table)
   * is essential for out kernel.
   * It allows us to do basic memory
   * management and control our
   * IRSs (Interrupt Service Routines).
   */
  test ("Setting up GDT...", gdt_init);

  /**
   * The PIC (Programmable Interrupt Controller)
   * allows us to map the exceptions,
   * hardware- and software-interrupts to
   * other numbers so we can easily
   * handle them.
   */
  test ("Remapping PIC...", pic_init);

  /**
   * The IDT (Interrupt Descriptor Table)
   * is needed for being able to handle
   * exceptions, hardware- and software-
   * interrupts correctly.
   */
  test ("Setting up IDT...", idt_init);

  /**
   * The PIT (Programmable Interrupt Timer)
   * generates interrupts on IRQ 0 (Interrupt 0x20).
   * We will reprogram it to fire at a rate of
   * 100hz and use it for preemptive multitasking.
   */
  test ("Initializing PIT...", pit_init);

  /**
   * The PS/2 keyboard will be used for
   * handling input from the user.
   */
  test ("Initializing Keyboard...", keyboard_init);

  /**
   * Our interrupt handlers are set up,
   * now we can safely re-enable interrupts.
   */
  enable_interrupts ();

  while (true) {
  }
}

void disable_interrupts (void) {
  asm volatile ("cli");
}

void enable_interrupts (void) {
  asm volatile ("sti");
}
