#pragma once

#include <stdint.h>

#ifndef I2C_H
#define I2C_H

#define I2C1_BASE    (PERIPHERAL_BASE + 0x00804000)

#define I2C_S_CLKT   (1 << 9)
#define I2C_S_ERR    (1 << 8)
#define I2C_S_RXF    (1 << 7)
#define I2C_S_TXE    (1 << 6)
#define I2C_S_RXD    (1 << 5)
#define I2C_S_TXD    (1 << 4)
#define I2C_S_RXR    (1 << 3)
#define I2C_S_TXW    (1 << 2)
#define I2C_S_DONE   (1 << 1)
#define I2C_S_TA     (1 << 0)

#define I2C_C_I2CEN  (1 << 15)
#define I2C_C_INTR   (1 << 10)
#define I2C_C_INTT   (1 << 9)
#define I2C_C_INTD   (1 << 8)
#define I2C_C_ST     (1 << 7) 
#define I2C_C_CLEAR  (1 << 5)
#define I2C_C_READ   (1 << 0) 

struct I2C_Registers {
    volatile uint32_t C;      // Control
    volatile uint32_t S;      // Status
    volatile uint32_t DLEN;   // Data Length
    volatile uint32_t A;      // Slave Address
    volatile uint32_t FIFO;   // Data FIFO
    volatile uint32_t DIV;    // Clock Divider
    volatile uint32_t DEL;    // Data Delay
    volatile uint32_t CLKT;   // Clock Stretch Timeout
};

#define I2C1 ((struct I2C_Registers *)I2C1_BASE)

void i2c_init(void);
int i2c_write(uint8_t *data, uint32_t length);
int i2c_read(uint8_t *buffer, uint32_t length);
int i2c_write_byte(const uint8_t *tx_data, uint32_t tx_len,
                   uint8_t *rx_data, uint32_t rx_len);

#endif