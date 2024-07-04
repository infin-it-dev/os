struct exFAT_DirectoryEntry {
    uint8_t entryType;
    uint8_t secondaryCount;
    uint16_t checksum;
    uint16_t fileAttributes;
    uint16_t reserved1;
    uint32_t createTime;
    uint32_t lastModifiedTime;
    uint32_t lastAccessedTime;
    uint8_t create10msIncrement;
    uint8_t lastModified10msIncrement;
    uint8_t createTimezoneOffset;
    uint8_t lastModifiedTimezoneOffset;
    uint8_t lastAccessedTimezoneOffset;
    uint8_t reserved2[7];
} __attribute__((packed));

void read_directory(uint32_t cluster) {
    uint8_t buffer[512 * sectors_per_cluster];
    read_cluster(cluster, buffer);
    struct exFAT_DirectoryEntry* entries = (struct exFAT_DirectoryEntry*)buffer;
    for (uint32_t i = 0; i < sectors_per_cluster * bytes_per_sector / sizeof(struct exFAT_DirectoryEntry); i++) {
        if (entries[i].entryType == 0x85) {
            // Handle directory entry
        }
    }
}
