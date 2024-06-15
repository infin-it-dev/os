#include <stdint.h>
#include <stddef.h>

#define KEYBOARD_DATA_PORT 0x60
#define KEYBOARD_STATUS_PORT 0x64

volatile uint8_t key_buffer[256];
volatile size_t buffer_index = 0;

void keyboard_interrupt_handler() {
    uint8_t status = inb(KEYBOARD_STATUS_PORT);
    if (status & 0x01) {
        uint8_t keycode = inb(KEYBOARD_DATA_PORT);
        key_buffer[buffer_index++] = keycode;
    }
}

void init_keyboard() {
   
    outb(0x21, inb(0x21) & ~0x01);
}
