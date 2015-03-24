#include <types.h>
#include <memory.h>
#include <idt.h>
#include <terminal.h>
#include <ports.h>
#include <string.h>

struct {
  uint16_t limit;
  void* pointer;
} __attribute__((packed)) idtp = {
  .limit = (sizeof(struct idt_entry) * 256) - 1,
  .pointer = &idt,
};

void idt_init (void) {
  // Clear IDT
  memset (&idt, 0, sizeof(struct idt_entry) * 256);

  // Exceptions
  idt_set_gate ( 0, (unsigned) isr0, 0x08, 0x8E);
	idt_set_gate ( 1, (unsigned) isr1, 0x08, 0x8E);
	idt_set_gate ( 2, (unsigned) isr2, 0x08, 0x8E);
	idt_set_gate ( 3, (unsigned) isr3, 0x08, 0x8E);
	idt_set_gate ( 4, (unsigned) isr4, 0x08, 0x8E);
	idt_set_gate ( 5, (unsigned) isr5, 0x08, 0x8E);
	idt_set_gate ( 6, (unsigned) isr6, 0x08, 0x8E);
	idt_set_gate ( 7, (unsigned) isr7, 0x08, 0x8E);
	idt_set_gate ( 8, (unsigned) exc8, 0x08, 0x8E);
	idt_set_gate ( 9, (unsigned) isr9, 0x08, 0x8E);
	idt_set_gate (10, (unsigned)exc10, 0x08, 0x8E);
	idt_set_gate (11, (unsigned)exc11, 0x08, 0x8E);
	idt_set_gate (12, (unsigned)exc12, 0x08, 0x8E);
	idt_set_gate (13, (unsigned)exc13, 0x08, 0x8E);
	idt_set_gate (14, (unsigned)exc14, 0x08, 0x8E);
	idt_set_gate (15, (unsigned)isr15, 0x08, 0x8E);
	idt_set_gate (16, (unsigned)isr16, 0x08, 0x8E);
	idt_set_gate (17, (unsigned)isr17, 0x08, 0x8E);
	idt_set_gate (18, (unsigned)isr18, 0x08, 0x8E);

  // Reserved exceptions
  idt_set_gate (19, (unsigned)isr19, 0x08, 0x8E);
	idt_set_gate (20, (unsigned)isr20, 0x08, 0x8E);
	idt_set_gate (21, (unsigned)isr21, 0x08, 0x8E);
	idt_set_gate (22, (unsigned)isr22, 0x08, 0x8E);
	idt_set_gate (23, (unsigned)isr23, 0x08, 0x8E);
	idt_set_gate (24, (unsigned)isr24, 0x08, 0x8E);
	idt_set_gate (25, (unsigned)isr25, 0x08, 0x8E);
	idt_set_gate (26, (unsigned)isr26, 0x08, 0x8E);
	idt_set_gate (27, (unsigned)isr27, 0x08, 0x8E);
	idt_set_gate (28, (unsigned)isr28, 0x08, 0x8E);
	idt_set_gate (29, (unsigned)isr29, 0x08, 0x8E);
	idt_set_gate (30, (unsigned)isr30, 0x08, 0x8E);
	idt_set_gate (31, (unsigned)isr31, 0x08, 0x8E);

	// IRQs
	idt_set_gate (32, (unsigned)isr32, 0x08, 0x8E);
	idt_set_gate (33, (unsigned)isr32, 0x08, 0x8E);
	idt_set_gate (34, (unsigned)isr32, 0x08, 0x8E);
	idt_set_gate (35, (unsigned)isr32, 0x08, 0x8E);
	idt_set_gate (36, (unsigned)isr32, 0x08, 0x8E);
	idt_set_gate (37, (unsigned)isr32, 0x08, 0x8E);
	idt_set_gate (38, (unsigned)isr32, 0x08, 0x8E);
	idt_set_gate (39, (unsigned)isr32, 0x08, 0x8E);
	idt_set_gate (40, (unsigned)isr32, 0x08, 0x8E);
	idt_set_gate (41, (unsigned)isr32, 0x08, 0x8E);
	idt_set_gate (42, (unsigned)isr32, 0x08, 0x8E);
	idt_set_gate (43, (unsigned)isr32, 0x08, 0x8E);
  idt_set_gate (44, (unsigned)isr32, 0x08, 0x8E);
	idt_set_gate (45, (unsigned)isr32, 0x08, 0x8E);
	idt_set_gate (46, (unsigned)isr32, 0x08, 0x8E);
	idt_set_gate (47, (unsigned)isr32, 0x08, 0x8E);

  // Load IDT
  idt_load ();
}

void idt_set_gate (uint8_t num, uint32_t base, uint16_t sel, uint8_t flags) {
  idt[num].base_lo = (base & 0xFFFF);
  idt[num].base_hi = (base >> 16) & 0xFFFF;
  idt[num].sel = sel;
  idt[num].zero = 0;
  idt[num].flags = flags;
}

void idt_load (void) {
  asm volatile ("lidt %0" : : "m" (idtp));
}

uint8_t* exception_messages[] =
{
	"*** DIVIDE BY ZERO EXCEPTION\n",              //  0
	"*** DEBUG EXCEPTION\n",                       //  1
	"*** NON MASKABLE INTERRUPT EXCEPTION\n",      //  2
	"*** INTO DETECTED OVERFLOW EXCEPTION\n",      //  3
	"*** OUT OF BOUNDS EXCEPTION\n",               //  4
	"*** INVALID OPCODE EXCEPTION\n",              //  5
	"*** NO COPROCESSOR EXCEPTION\n",              //  6
	"*** DOUBLE FAULT EXCEPTION\n",                //  7
	"*** COPROCESSOR SEGMENT OVERRUN EXCEPTION\n", //  8
	"*** BAD TSS EXCEPTION\n",                     //  9
	"*** SEGMENT NOT PRESENT EXCEPTION\n",         // 10
	"*** STACK FAULT EXCEPTION\n",                 // 11
	"*** GENERAL PROTECTION FAULT EXCEPTION\n",    // 12
	"*** PAGE FAULT EXCEPTION\n",                  // 13
	"*** UNKNOWN INTERRUPT EXCEPTION\n",           // 14
	"*** COPROCESSOR FAULT EXCEPTION\n",           // 15
	"*** ALIGNMENT CHECK EXCEPTION\n",             // 16
	"*** MACHINE CHECK EXCEPTION\n",               // 17
  "*** I FUCKED UP THE EXCEPTION TEXT HERE\n",   // 18  // uhm.. yeah..
};

void *irq_handlers[16] = {
  0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0,
};

void idt_install_handler (int8_t irq,
  void (*handler)(struct cpu_state *frame)) {
  irq_handlers[irq] = handler;
}

void idt_uninstall_handler (int8_t irq) {
  irq_handlers[irq] = 0;
}

void idt_handle_exception (struct cpu_state *frame) {
  // Print exception message
  puts (exception_messages[frame->intr]);

  // Print debug information
  uint8_t buf[13];
  puts ("[CPU State]");
  puts ("\nGS: ");      puts (itoa (frame->gs,      buf));
  puts ("\t\tFS: ");    puts (itoa (frame->fs,      buf));
  puts ("\t\tES: ");    puts (itoa (frame->es,      buf));
  puts ("\nDS: ");      puts (itoa (frame->ds,      buf));
  puts ("\t\tEDI: ");   puts (itoa (frame->edi,     buf));
  puts ("\t\tESI: ");   puts (itoa (frame->esi,     buf));
  puts ("\nEBP: ");     puts (itoa (frame->ebp,     buf));
  puts ("\t\tESP: ");   puts (itoa (frame->esp,     buf));
  puts ("\tEBX: ");     puts (itoa (frame->ebx,     buf));
  puts ("\nEDX: ");     puts (itoa (frame->edx,     buf));
  puts ("\t\tECX: ");   puts (itoa (frame->ecx,     buf));
  puts ("\tEAX: ");     puts (itoa (frame->eax,     buf));
  puts ("\nEIP: ");     puts (itoa (frame->eip,     buf));
  puts ("\tCS: ");      puts (itoa (frame->cs,      buf));
  puts ("\t\tSS: ");    puts (itoa (frame->ss,      buf));
  puts ("\nEFLAGS: ");  puts (itoa (frame->eflags,  buf));
  puts ("\tUSERESP: "); puts (itoa (frame->useresp, buf));

  // Halt
  while (true) {
    asm ("cli; hlt");
  }
}

void idt_handle_irq (struct cpu_state *frame) {
  // Blank IRQ handler
  void (*handler)(struct cpu_state *frame);

  // Set our handler to the actual IRQ handler
  handler = irq_handlers[frame->intr - 32];

  // Call the handler
  if (handler)
    handler (frame);
}

void idt_handle_syscall (struct cpu_state *frame) {
}

void idt_handle_general (struct cpu_state *frame) {
  // Exceptions
  if (frame->intr <= 0x1F) {
    // Call exception handler
    idt_handle_exception (frame);
  }

  // IRQs
  if (frame->intr >= 0x20 && frame->intr <= 0x2F) {
    // Call IRQ handler
    idt_handle_irq (frame);

    // Send EOI to slave interrupt controller
    if (frame->intr == 0x28) {
      outb (0xA0, 0x20);
    }

    // Send EOI to master interrupt controller
    outb (0x20, 0x20);
  }
}
