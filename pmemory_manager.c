#include <stdint.h>

#define BITMAP_SIZE 8192 

uint32_t memory_bitmap[BITMAP_SIZE / 32];

void set_bit(int bit) {
    memory_bitmap[bit / 32] |= (1 << (bit % 32));
}

void clear_bit(int bit) {
    memory_bitmap[bit / 32] &= ~(1 << (bit % 32));
}

int test_bit(int bit) {
    return memory_bitmap[bit / 32] & (1 << (bit % 32));
}

void* allocate_frame() {
    for (int i = 0; i < BITMAP_SIZE; i++) {
        if (!test_bit(i)) {
            set_bit(i);
            return (void*)(i * 4096); 
        }
    }
    return 0; 
}

void free_frame(void* frame) {
    int bit = (uint32_t)frame / 4096;
    clear_bit(bit);
}
