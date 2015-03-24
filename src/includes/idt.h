#ifndef __idt__
#define __idt__

#include <types.h>

#define IDT_ENTRIES 256

struct idt_entry
{
    unsigned short base_lo;
    unsigned short sel;
    unsigned char zero;
    unsigned char flags;
    unsigned short base_hi;
} __attribute__((packed));

struct cpu_state {
  uint32_t gs, fs, es, ds;
  uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
  uint32_t intr, error;
  uint32_t eip, cs, eflags, useresp, ss;
};

struct idt_entry idt[IDT_ENTRIES];

void idt_init (void);
void idt_load (void);
void idt_set_gate(uint8_t, uint32_t, uint16_t, uint8_t);
void idt_install_handler (int8_t, void (*)(struct cpu_state *));
void idt_uninstall_handler (int8_t);
void idt_handle_irq (struct cpu_state *);
void idt_handle_syscall (struct cpu_state *);
void idt_handle_general (struct cpu_state *);
void idt_handle_exception (struct cpu_state *);

// Exceptions (boot.S)
extern void isr0 (void);
extern void isr1 (void);
extern void isr2 (void);
extern void isr3 (void);
extern void isr4 (void);
extern void isr5 (void);
extern void isr6 (void);
extern void isr7 (void);
extern void exc8 (void);
extern void isr9 (void);
extern void exc10 (void);
extern void exc11 (void);
extern void exc12 (void);
extern void exc13 (void);
extern void exc14 (void);
extern void isr15 (void);
extern void isr16 (void);
extern void isr17 (void);
extern void isr18 (void);

// Reserved exceptions (boot.S)
extern void isr19 (void);
extern void isr20 (void);
extern void isr21 (void);
extern void isr22 (void);
extern void isr23 (void);
extern void isr24 (void);
extern void isr25 (void);
extern void isr26 (void);
extern void isr27 (void);
extern void isr28 (void);
extern void isr29 (void);
extern void isr30 (void);
extern void isr31 (void);

// IRQs (boot.S)
extern void isr32 (void);
extern void isr33 (void);
extern void isr34 (void);
extern void isr35 (void);
extern void isr36 (void);
extern void isr37 (void);
extern void isr38 (void);
extern void isr39 (void);
extern void isr40 (void);
extern void isr41 (void);
extern void isr42 (void);
extern void isr43 (void);
extern void isr44 (void);
extern void isr45 (void);
extern void isr46 (void);
extern void isr47 (void);

#endif
