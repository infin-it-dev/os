uint32_t read_fat_entry(uint32_t cluster, uint8_t *fat)
{
  uint32_t fat_offset = cluster * 4;
  uint32_t fat_sector = fat_offset / 512;
  uint32_t fat_entry_offset = fat_offset % 512;
  uint8_t buffer[512];

  read_sector(fat_sector, buffer);
  return *(uint32_t*)&buffer[fat_entry_offset];

  if (fat_type == 0)
  {
    fat8 = fat;
    offset = cluster + (cluster / 2);
    if (cluster % 2)
      value = fat8[offset] >> 4;
    else
      value = fat8[offset] & 0xF;
  }
  else if (fat_type == 1)
  {
    fat16 = fat;
    value = fat16[cluster];
  }
  else
  {
    fat32 = fat;
    value = fat32[cluster];
  }
  return value;
}