#ifndef __gdt__
#define __gdt__

#include <types.h>

#define GDT_ENTRIES 5

static uint64_t gdt[GDT_ENTRIES];
void gdt_create_descriptor (uint64_t i, uint32_t, uint32_t, uint16_t);
void gdt_init (void);
void gdt_load (void);
extern void gdt_reload_segments (void);

#define SEG_DESCTYPE(x) ((x) << 0x04) // Descriptor type
#define SEG_PRESENT(x)  ((x) << 0x07) // Present
#define SEG_SAVAIL(x)   ((x) << 0x0C) // Available for system use
#define SEG_LONG(x)     ((x) << 0x0D) // Long mode
#define SEG_SIZE(x)     ((x) << 0x0E) // Size (0 = 16bit, 1 = 32bit)
#define SEG_GRAN(x)     ((x) << 0x0F) // Granulatiry (0 = 1MB, 1 = 4GB)
#define SEG_PRIV(x)    (((x)  & 0x03) << 0x05) // Ring ([0..3])

#define SEG_DATA_RD         0x00 // Read-Only
#define SEG_DATA_RDA        0x01 // Read-Only, accessed
#define SEG_DATA_RDWR       0x02 // Read/Write
#define SEG_DATA_RDWRA      0x03 // Read/Write, accessed
#define SEG_DATA_RDEXPD     0x04 // Read-Only, expand-down
#define SEG_DATA_RDEXPDA    0x05 // Read-Only, expand-down, accessed
#define SEG_DATA_RDWREXPD   0x06 // Read/Write, expand-down
#define SEG_DATA_RDWREXPDA  0x07 // Read/Write, expand-down, accessed
#define SEG_CODE_EX         0x08 // Execute-Only
#define SEG_CODE_EXA        0x09 // Execute-Only, accessed
#define SEG_CODE_EXRD       0x0A // Execute/Read
#define SEG_CODE_EXRDA      0x0B // Execute/Read, accessed
#define SEG_CODE_EXC        0x0C // Execute-Only, conforming
#define SEG_CODE_EXCA       0x0D // Execute-Only, conforming, accessed
#define SEG_CODE_EXRDC      0x0E // Execute/Read, conforming
#define SEG_CODE_EXRDCA     0x0F // Execute/Read, conforming, accessed

#define GDT_CODE_PL0  SEG_DESCTYPE(1) | SEG_PRESENT(1)  | SEG_SAVAIL(0) \
                      | SEG_LONG(0)   | SEG_SIZE(1)     | SEG_GRAN(1)   \
                      | SEG_PRIV(0)   | SEG_CODE_EXRD
#define GDT_DATA_PL0  SEG_DESCTYPE(1) | SEG_PRESENT(1)  | SEG_SAVAIL(0) \
                      | SEG_LONG(0)   | SEG_SIZE(1)     | SEG_GRAN(1)   \
                      | SEG_PRIV(0)   | SEG_DATA_RDWR
#define GDT_CODE_PL3  SEG_DESCTYPE(1) | SEG_PRESENT(1)  | SEG_SAVAIL(0) \
                      | SEG_LONG(0)   | SEG_SIZE(1)     | SEG_GRAN(1)   \
                      | SEG_PRIV(3)   | SEG_CODE_EXRD
#define GDT_DATA_PL3  SEG_DESCTYPE(1) | SEG_PRESENT(1)  | SEG_SAVAIL(0) \
                      | SEG_LONG(0)   | SEG_SIZE(1)     | SEG_GRAN(1)   \
                      | SEG_PRIV(3)   | SEG_DATA_RDWR

#endif
