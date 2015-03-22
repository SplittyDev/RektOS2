#include <types.h>
#include <gdt.h>

struct {
  uint16_t limit;
  void *pointer;
} __attribute__((packed)) gdtp = {
  .limit = GDT_ENTRIES * 8 - 1,
  .pointer = gdt,
};

void gdt_create_descriptor (uint32_t base, uint32_t limit, uint16_t flag) {
  uint64_t descriptor;
  descriptor  = limit         & 0x000F0000;
  descriptor |= (flag <<  8)  & 0x00F0FF00;
  descriptor |= (base >> 16)  & 0x000000FF;
  descriptor |=  base         & 0xFF000000;
  descriptor <<= 32;
  descriptor |=  base << 16;
  descriptor |= limit         & 0x0000FFFF;
}

void gdt_init (void) {
  gdt_create_descriptor (0, 0, 0); // Null descriptor
  gdt_create_descriptor (0, 0x000FFFFF, (GDT_CODE_PL0));
  gdt_create_descriptor (0, 0x000FFFFF, (GDT_DATA_PL0));
  gdt_create_descriptor (0, 0x000FFFFF, (GDT_CODE_PL3));
  gdt_create_descriptor (0, 0x000FFFFF, (GDT_DATA_PL3));
  gdt_load ();
  gdt_reload_segments ();
}

void gdt_load (void) {
  asm volatile ("lgdt %0" : : "m" (gdtp));
}
