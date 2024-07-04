int read_cluster(uint32_t cluster, uint8_t* buffer) {
    uint32_t first_sector = cluster_heap_offset + (cluster - 2) * sectors_per_cluster;
    for (uint32_t i = 0; i < sectors_per_cluster; i++) {
        read_sector(first_sector + i, buffer + i * bytes_per_sector);
    }
    return 0;
}
