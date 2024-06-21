#define PAGE_DIRECTORY_SIZE 1024
#define PAGE_TABLE_SIZE 1024
#define PAGE_SIZE 1024

uint32_t page_directory[PAGE_DIRECTORY_SIZE] __attribute__((aligned(PAGE_SIZE)));
uint32_t first_page_table[PAGE_TABLE_SIZE] __attribute__((aligned(PAGE_SIZE)));

void init_paging() {
    for (int i = 0; i < PAGE_DIRECTORY_SIZE; i++) {
        page_directory[i] = 0 | 0x2;
    }
    for (int i = 0; i < PAGE_TABLE_SIZE; i++) {
        first_page_table[i] = (i * PAGE_SIZE) | 0x3;
    }
    page_directory[0] = ((uint32_t)first_page_table) | 0x3;
    load_page_directory(page_directory);
    enable_paging();
}

void load_page_directory(uint32_t* page_directory) {
    __asm__ volatile("mov %0, %%cr3" :: "r"(page_directory));
}

void enable_paging() {
    uint32_t cr0;
    __asm__ volatile("mov %%cr0, %0" : "=r"(cr0));
    cr0 |= 0x80000000;
    __asm__ volatile("mov %0, %%cr0" :: "r"(cr0));
}
