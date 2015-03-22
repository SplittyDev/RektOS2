#include <types.h>
#include <ports.h>
#include <terminal.h>
#include <memory.h>

uint16_t *vmem;
uint8_t terminal_x, terminal_y;
uint8_t attrib;

void terminal_init (void) {
  vmem = (uint16_t *)0xB8000;
  terminal_x = 0;
  terminal_y = 0;
  attrib = 0x0F;
}

void clear (void) {
  uint8_t blank = 0x20 | (attrib << 8);
  uint8_t i = 0;
  for (; i < 25; i++)
    memsetw (vmem + i * 80, blank, 80);
  terminal_x = 0;
  terminal_y = 0;
  move_cursor ();
}

void putc (const char chr) {
  switch (chr) {
    // Backspace
    case 0x08:
      if (terminal_x != 0)
        terminal_x--;
      break;
    // Carriage return
    case '\r':
      terminal_x = 0;
      break;
    // Line feed
    case '\n':
      terminal_y++;
      break;
    default:
      vmem[terminal_y * 80 + terminal_x] = chr | (attrib << 8);
      terminal_x++;
  }
  scroll ();
  move_cursor ();
}

void puts (const char *str) {
  uint8_t i = 0;
  while (str[i] != '\0') {
    putc (str[i]);
    i++;
  }
}

void scroll (void) {
  uint8_t blank, tmp;
  blank = 0x20 | (attrib << 8);
  if (terminal_y >= 25) {
    tmp = terminal_y - 25 + 1;
    memcpyw (vmem, vmem + tmp * 80, (25 - tmp) * 80 * 2);
    memsetw (vmem + (25 - tmp) * 80, blank, 80);
    terminal_y = 25 - 1;
  }
}

void move_cursor (void) {
  uint8_t attr = terminal_y * 80 + terminal_x;
  outb (0x3D4, 14);
  outb (0x3D5, attr >> 8);
  outb (0x3D4, 15);
  outb (0x3D5, attr);
}

uint8_t makecolor (uint8_t fc, uint8_t bc) {
  return fc | (bc << 4);
}
