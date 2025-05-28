#include "gpio.h" 
#include "i2c.h"

void i2c_init(void) {
    I2C1->DIV = 2500;
    I2C1->S = I2C_S_DONE | I2C_S_ERR | I2C_S_CLKT;
}

int i2c_write(uint8_t *data, uint32_t length) {
    int count = 0;

    I2C1->A = 0x3C;
    I2C1->C = I2C_C_CLEAR;
    I2C1->S = I2C_S_DONE | I2C_S_ERR | I2C_S_CLKT;
    I2C1->DLEN = length;
    I2C1->C = I2C_C_I2CEN | I2C_C_ST;

    delay(1000000);
    led_on();
    while (!(I2C1->S & I2C_S_DONE)) {
        while (count < length && I2C1->S & I2C_S_TXD) {
            I2C1->FIFO = *data++;
            count++;
        }
    }
    delay(1000000);
    led_off();

    I2C1->S = I2C_S_DONE | I2C_S_ERR | I2C_S_CLKT;
    return 0; 
}