#include <types.h>
#include <memory.h>
#include <idt.h>
#include <terminal.h>

struct {
  uint16_t limit;
  void* pointer;
} __attribute__((packet)) idtp = {
  .limit = IDT_ENTRIES * 8 - 1,
  .pointer = idt,
};

void idt_init (void) {
  memsetw (&idt, 0, sizeof(idt) * 255);

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
	idt_set_gate (17, (unsigned)exc17, 0x08, 0x8E);
	idt_set_gate (18, (unsigned)isr18, 0x08, 0x8E);
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

void interrupt_handler (void) {
  puts ("Interrupt!");
  while (true) {
    asm volatile ("cli; hlt");
  }
}