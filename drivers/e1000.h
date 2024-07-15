#ifndef E1000_H
#define E1000_H

#include <stdint.h>

#define E1000_REG_CTRL       0x00000  // Device Control Register
#define E1000_REG_STATUS     0x00008  // Device Status Register
#define E1000_REG_TDT        0x03818  // Transmit Descriptor Tail
#define E1000_REG_TDBAL      0x03800  // Transmit Descriptor Base Low
#define E1000_REG_TDBAH      0x03804  // Transmit Descriptor Base High
#define E1000_REG_TDLEN      0x03810  // Transmit Descriptor Length
#define E1000_REG_RDT        0x02818  // Receive Descriptor Tail
#define E1000_REG_RDBAL      0x02800  // Receive Descriptor Base Low
#define E1000_REG_RDBAH      0x02804  // Receive Descriptor Base High
#define E1000_REG_RDLEN      0x02810  // Receive Descriptor Length
#define E1000_REG_RDH        0x02810  // Receive Descriptor Head

struct e1000_tx_desc {
    uint64_t address;
    uint16_t length;
    uint8_t cso;
    uint8_t cmd;
    uint8_t status;
    uint8_t css;
    uint16_t special;
};

struct e1000_rx_desc {
    uint64_t address;
    uint16_t length;
    uint16_t checksum;
    uint8_t status;
    uint8_t errors;
    uint16_t special;
};

void e1000_init(uint32_t bar0);
void e1000_send_packet(uint8_t* data, uint16_t length);
void e1000_receive_packet(uint8_t* buffer, uint16_t* length);

#endif // E1000_H
