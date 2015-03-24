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
  idt_set_gate (0, (unsigned)isr0, 0x08, 0x8E);
	idt_set_gate (1, (unsigned)isr1, 0x08, 0x8E);
	idt_set_gate (2, (unsigned)isr2, 0x08, 0x8E);
	idt_set_gate (3, (unsigned)isr3, 0x08, 0x8E);
	idt_set_gate (4, (unsigned)isr4, 0x08, 0x8E);
	idt_set_gate (5, (unsigned)isr5, 0x08, 0x8E);
	idt_set_gate (6, (unsigned)isr6, 0x08, 0x8E);
	idt_set_gate (7, (unsigned)isr7, 0x08, 0x8E);
	idt_set_gate (8, (unsigned)exc8, 0x08, 0x8E);
	idt_set_gate (9, (unsigned)isr9, 0x08, 0x8E);
	idt_set_gate (10, (unsigned)exc10, 0x08, 0x8E);
	idt_set_gate (11, (unsigned)exc11, 0x08, 0x8E);
	idt_set_gate (12, (unsigned)exc12, 0x08, 0x8E);
	idt_set_gate (13, (unsigned)exc13, 0x08, 0x8E);
	idt_set_gate (14, (unsigned)exc14, 0x08, 0x8E);
	idt_set_gate (15, (unsigned)isr15, 0x08, 0x8E);
	idt_set_gate (16, (unsigned)isr16, 0x08, 0x8E);
  // Not sure if it is isr17 or exc17.
  // isr17 will probably do it for now.
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

	// Common
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

void idt_load (void) {
  asm volatile ("lidt %0" : : "m" (idtp));
}

void idt_set_gate (uint8_t num, uint32_t base, uint16_t sel, uint8_t flags) {
  idt[num].base_lo = (base & 0xFFFF);
  idt[num].base_hi = (base >> 16) & 0xFFFF;
  idt[num].sel = sel;
  idt[num].zero = 0;
  idt[num].flags = flags;
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

void interrupt_handler (struct cpu_state *frame) {
  // Exceptions
  if (frame->intr <= 0x1F) {
    // Print exception message
    puts (exception_messages[frame->intr]);

    /*
    uint32_t gs, fs, es, ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
    uint32_t intr, error;
    uint32_t eip, cs, eflags, useresp, ss;
    */

    // Print debug information
    uint8_t buf[13];
    puts ("Interrupt number: "); puts (itoa (frame->intr, buf));
    puts ("\nError number: "); puts (itoa (frame->error, buf));
    puts ("\nCPU State:");
    puts ("\nGS: "); puts (itoa (frame->gs, buf));
    puts ("\tFS: "); puts (itoa (frame->fs, buf));
    puts ("\tES: "); puts (itoa (frame->es, buf));
    puts ("\tDS: "); puts (itoa (frame->ds, buf));
    puts ("\nEDI: "); puts (itoa (frame->edi, buf));
    puts ("\tESI: "); puts (itoa (frame->esi, buf));
    puts ("\tEBP: "); puts (itoa (frame->ebp, buf));
    puts ("\tESP: "); puts (itoa (frame->esp, buf));
    puts ("\nEBX: "); puts (itoa (frame->ebx, buf));
    puts ("\tEDX: "); puts (itoa (frame->edx, buf));
    puts ("\tECX: "); puts (itoa (frame->ecx, buf));
    puts ("\tEAX: "); puts (itoa (frame->eax, buf));
    puts ("\nEIP: "); puts (itoa (frame->eip, buf));
    puts ("\tCS: "); puts (itoa (frame->cs, buf));
    puts ("\tEFLAGS: "); puts (itoa (frame->eflags, buf));
    puts ("\tUSERESP: "); puts (itoa (frame->useresp, buf));
    puts ("\tSS: "); puts (itoa (frame->ss, buf));

    while (true) {
      asm ("cli; hlt");
    }
  }

  // Hardware interrupts
  if (frame->intr >= 0x20 && frame->intr <= 0x2F) {
    if (frame->intr == 0x28) {
      // Send EOI to slave interrupt controller
      outb (0xA0, 0x20);
    }
    // Send EOI to master interrupt controller
    outb (0x20, 0x20);
  }
}
