#include <pic.h>
#include <ports.h>

void pic_init (void) {
  pic_init_master ();
  pic_init_slave  ();
  pic_unmask_irqs ();
}

void pic_init_master (void) {
  outb (0x20, 0x11);
  outb (0x21, 0x20);
  outb (0x21, 0x04);
  outb (0x21, 0x01);
}

void pic_init_slave (void) {
  outb (0xA0, 0x11);
  outb (0xA1, 0x28);
  outb (0xA1, 0x02);
  outb (0xA1, 0x01);
}

void pic_unmask_irqs (void) {
  outb (0x21, 0x0);
  outb (0xA1, 0x0);
}
