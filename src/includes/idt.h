#ifndef __idt__
#define __idt__

#include <types.h>

#define IDT_ENTRIES 255

struct idt_entry
{
    unsigned short base_lo;
    unsigned short sel;
    unsigned char zero;
    unsigned char flags;
    unsigned short base_hi;
} __attribute__((packed));

struct idt_entry idt[IDT_ENTRIES];
void idt_init (void);
void idt_load (void);
void idt_set_gate(uint8_t, uint32_t, uint16_t, uint8_t);
struct cpu_state *interrupt_handler (struct cpu_state *);

struct cpu_state
{
	uint32_t   eax;
  uint32_t   ebx;
  uint32_t   ecx;
  uint32_t   edx;
  uint32_t   esi;
  uint32_t   edi;
  uint32_t   ebp;

  uint32_t   intr;
  uint32_t   error;

  uint32_t   eip;
  uint32_t   cs;
  uint32_t   eflags;
  uint32_t   esp;
  uint32_t   ss;
};

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
extern void exc17 (void);
extern void isr18 (void);

/*
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
*/

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
