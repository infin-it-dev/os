#include <stdint.h>




struct exFAT_BootSector {
    uint8_t jumpBoot[3];
    uint8_t fileSystemName[8];
    uint8_t reserved[53];
    uint64_t partitionOffset;
    uint64_t volumeLength;
    uint32_t fatOffset;
    uint32_t fatLength;
    uint32_t clusterHeapOffset;
    uint32_t clusterCount;
    uint32_t rootDirFirstCluster;
    uint32_t volumeSerialNumber;
    uint16_t fileSystemRevision;
    uint16_t volumeFlags;
    uint8_t bytesPerSectorShift;
    uint8_t sectorsPerClusterShift;
    uint8_t numberOfFats;
    uint8_t driveSelect;
    uint8_t percentInUse;
    uint8_t reserved2[7];
    uint8_t bootCode[390];
    uint16_t bootSignature;
} __attribute__((packed));



int read_sector(uint32_t lba, uint8_t* buffer) {
    // add bios interupts or ata
    return 0;
}



int init_exfat(){

    struct exFAT_BootSector bpb;
    read_sector(0, (uint8_t*)&bpb);


    if(bpb.bootSignature !+ 0xAA55){
        return -1; // invalid boot signature

    }

    uint32_t bytesPerSector = 1 << bpb.bytesPerSectorShift;
    uint32_t sectorsPerCluster = 1 << bpb.sectorsPerClusterShift;
    
    //set up structures based on bpb values

    
    }
