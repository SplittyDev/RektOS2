#include <types.h>
#include <keyboard.h>
#include <idt.h>
#include <ports.h>
#include <terminal.h>

void keyboard_init (void) {
  keyboard_install_handler ();
}

void keyboard_install_handler (void) {
  idt_install_handler (KEYBOARD_IRQ, keyboard_handler);
}

void keyboard_uninstall_handler (void) {
  idt_uninstall_handler (KEYBOARD_IRQ);
}

uint8_t keymap_en[128] = {
  0,                        //               0
  27,                       // ESC ^[        1
  '1', '2', '3', '4', '5',  // Numbers       2 -  6
  '6', '7', '8', '9', '0',  // Numbers       7 - 11
  '-', '=', '\b', '\t',     //              12 - 15
  'q', 'w', 'e', 'r', 't',  // Chars        16 - 20
  'y', 'u', 'i', 'o', 'p',  // Chars        21 - 25
  '[', ']', '\n',           //              26 - 28
  0,                        // Control      29
  'a', 's', 'd', 'f', 'g',  // Chars        30 - 34
  'h', 'j', 'k', 'l',       // Chars        35 - 38
  ';', '\'', '`',           //              39 - 41
  0,                        // Lshift       42
  '\\',                     //              43
  'z', 'x', 'c', 'v', 'b',  // Chars        44 - 48
  'n', 'm',                 // Chars        49 - 50
  ',', '.', '/',            //              51 - 53
  0,                        // Rshift       54
  '*',                      //              55
  0,                        // Alt          56
  ' ',                      // Space        57
  0,                        // Caps lock    58
  0, 0, 0, 0, 0,            // F1 - F5      59 - 63
  0, 0, 0, 0, 0,            // F6 - F10     64 - 68
  0,                        // Num lock     69
  0,                        // Scroll lock  70
  0,                        // Home key     71
  0,                        // Arrow up     72
  0,                        // Page up      73
  '-',                      // Num minus    74
  0,                        // Arrow left   75
  0,                        //              76
  0,                        // Arrow right  77
  '+',                      // Num plus     78
  0,                        // End          79
  0,                        // Arrow down   80
  0,                        // Page down    81
  0,                        // Insert       82
  0,                        // Delete       83
  0, 0, 0,                  //              84 - 87
  0, 0,                     // F11 - F12    88 - 89
  0,                        //              90
};

void keyboard_handler (struct cpu_state *frame) {
  // Read from data register
  uint8_t scancode = inb (DATA_REGISTER);

  // Key released
  if (scancode & 0x80) {
  }

  // Key pressed
  else {
    putc (keymap_en[scancode]);
  }
}
