.section multiboot

#define MB_ALIGN    1 << 0
#define MB_MEMINFO  1 << 1
#define MB_MAGIC    0x1BADB002
#define MB_FLAGS    MB_ALIGN | MB_MEMINFO
#define MB_CHECKSUM -(MB_MAGIC + MB_FLAGS)

.align 4
.int  MB_MAGIC
.int  MB_FLAGS
.int  MB_CHECKSUM

.section .text

.extern init
.extern interrupt_handler

.global _start
.global isr_wrapper
.global gdt_reload_segments

_start:
  # Point stack pointer to stack
  mov $kernel_stack, %esp
  # Call kmain
  call init

_stop:
  cli
  hlt
  jmp _stop

.align 4
isr_wrapper:
  pushal
  cld
  call interrupt_handler
  popal
  iret

gdt_reload_segments:
  mov $0x10, %ax
  mov %ax, %ds
  mov %ax, %es
  mov %ax, %fs
  mov %ax, %gs
  mov %ax, %ss
  ljmp $0x8, $.1
  ret
.1:

# Interrupt Service Routines
.macro isr num
	.global isr\num
	isr\num:
		pushl $0
		pushl $\num
		jmp isr_wrapper
.endm

.macro exc num
	.global exc\num
	exc\num:
		pushl $\num
		jmp isr_wrapper
.endm

.macro sysf num, func
	.global sysf_\num
	sysf_\num:
		pushl $0
		pushl $\num
		jmp sysf_\func
.endm

# Exceptions
isr 0
isr 1
isr 2
isr 3
isr 4
isr 5
isr 6
isr 7
exc 8
isr 9
exc 10
exc 11
exc 12
exc 13
exc 14
isr 15
isr 16
exc 17
isr 18
isr 19

isr 20
isr 21
isr 22
isr 23
isr 24
isr 25
isr 26
isr 27
isr 28
isr 29
isr 30
isr 31

# IRQs
isr 32
isr 33
isr 34
isr 35
isr 36
isr 37
isr 38
isr 39
isr 40
isr 41
isr 42
isr 43
isr 44
isr 45
isr 46
isr 47

# Syscalls
# None.

.section .bss

.space 8192
kernel_stack:
