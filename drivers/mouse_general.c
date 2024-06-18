#include <stdint.h>
#include <stddef.h>

#define MOUSE_DATA_PORT 0x60
#define MOUSE_STATUS_PORT 0x64
#define MOUSE_COMMAND_PORT 0x64
#define MOUSE_IRQ 12

void mouse_wait(uint8_t type) {
    uint32_t timeout = 100000;
    if (type == 0) {
        while (timeout--) {
            if ((inb(MOUSE_STATUS_PORT) & 1) == 1) {
                return;
            }
        }
    } else {
        while (timeout--) {
            if ((inb(MOUSE_STATUS_PORT) & 2) == 0) {
                return;
            }
        }
    }
}

void mouse_write(uint8_t data) {
    mouse_wait(1);
    outb(MOUSE_COMMAND_PORT, 0xD4);
    mouse_wait(1);
    outb(MOUSE_DATA_PORT, data);
}

uint8_t mouse_read() {
    mouse_wait(0);
    return inb(MOUSE_DATA_PORT);
}

void mouse_enable() {
    mouse_wait(1);
    outb(MOUSE_COMMAND_PORT, 0xA8);
    mouse_wait(1);
    outb(MOUSE_COMMAND_PORT, 0x20);
    uint8_t status = (inb(MOUSE_DATA_PORT) | 2);
    mouse_wait(1);
    outb(MOUSE_COMMAND_PORT, 0x60);
    mouse_wait(1);
    outb(MOUSE_DATA_PORT, status);
    mouse_write(0xF6);
    mouse_read();
    mouse_write(0xF4);
    mouse_read();
}

void init_mouse() {
    mouse_enable();
    outb(0x21, inb(0x21) & ~(1 << 2));
}

volatile int8_t mouse_byte[3];
volatile uint8_t mouse_cycle = 0;
volatile int32_t mouse_x = 0;
volatile int32_t mouse_y = 0;

void mouse_handler() {
    static uint8_t mouse_bytes[3];
    static uint8_t mouse_byte_count = 0;
    mouse_bytes[mouse_byte_count++] = inb(MOUSE_DATA_PORT);
    if (mouse_byte_count == 3) {
        mouse_byte_count = 0;
        int8_t x_offset = mouse_bytes[1];
        int8_t y_offset = mouse_bytes[2];
        mouse_x += x_offset;
        mouse_y -= y_offset;
    }
}

// Declare and define the 'idt' array
struct idt_entry {
    uint16_t base_low;
    uint16_t sel;
    uint8_t always0;
    uint8_t flags;
    uint16_t base_high;
};

struct idt_entry idt[256];

void init_idt_entry(int irq, void (*handler)(), uint8_t flags) {
    idt[irq].base_low = (uint32_t)handler & 0xFFFF;
    idt[irq].sel = 0x08;
    idt[irq].always0 = 0;
    idt[irq].flags = flags;
    idt[irq].base_high = ((uint32_t)handler >> 16) & 0xFFFF;
}

void setup_mouse_interrupt() {
    init_idt_entry(MOUSE_IRQ + 32, mouse_handler, 0x8E);
}

void init_idt() {
    setup_mouse_interrupt();
    lidt((void*)idt, sizeof(idt) - 1);
}

void lidt(void* base, uint16_t size) {
    struct {
        uint16_t length;
        uint32_t base;
    } idtr = { size, (uint32_t)base };
    asm volatile("lidt (%0)" : : "r"(&idtr));
}
