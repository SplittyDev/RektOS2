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

.global _start
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

.section .bss

.space 8192
kernel_stack:
