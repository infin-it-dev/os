struct exFAT_File {
    uint32_t firstCluster;
    uint32_t fileSize;
    uint32_t currentCluster;
    uint32_t currentOffset;
};

int exfat_open(struct exFAT_File* file, const char* path) {
    // Parse the path and find the directory entry
    // Initialize the file structure with the starting cluster and size
}

int exfat_read(struct exFAT_File* file, uint8_t* buffer, uint32_t size) {
    uint32_t cluster = file->currentCluster;
    uint32_t offset = file->currentOffset;

    while (size > 0) {
        uint8_t clusterBuffer[512 * sectors_per_cluster];
        read_cluster(cluster, clusterBuffer);

        uint32_t bytesToRead = 512 * sectors_per_cluster - offset;
        if (bytesToRead > size) {
            bytesToRead = size;
        }

        memcpy(buffer, clusterBuffer + offset, bytesToRead);
        buffer += bytesToRead;
        size -= bytesToRead;
        offset += bytesToRead;

        if (offset >= 512 * sectors_per_cluster) {
            cluster = read_fat_entry(cluster);
            offset = 0;
        }
    }

    file->currentCluster = cluster;
    file->currentOffset = offset;

    return 0;
}
