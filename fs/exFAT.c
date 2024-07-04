#include <stdint.h>
#include <string.h>

int read_sector(uint32_t lba, uint8_t* buffer);
int init_exfat();
uint32_t read_fat_entry(uint32_t cluster);
int read_cluster(uint32_t cluster, uint8_t* buffer);
void read_directory(uint32_t cluster);
int exfat_open(struct exFAT_File* file, const char* path);
int exfat_read(struct exFAT_File* file, uint8_t* buffer, uint32_t size);

int main() {
    if (init_exfat() == -1) {
        // Handle error
    }

    struct exFAT_File file;
    if (exfat_open(&file, "/path/to/file") == -1) {
        // Handle error
    }

    uint8_t buffer[4096];
    if (exfat_read(&file, buffer, sizeof(buffer)) == -1) {
        // Handle error
    }

    // Process the file data

    return 0;
}
