#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "at24c04.h"

void at24c04_init(at24c04_t *at, uint8_t A2, uint8_t A1, i2c_inst_t *i2c_port){
    at->ADDR = (0xA0 >> 1) | (A2 << 2) | (A1 << 1);
    at->i2c_i = i2c_port;
}

int at24c04_write(at24c04_t at, uint16_t n, uint8_t data){
    at.ADDR = n > 255 ? at.ADDR + 1 : at.ADDR; //set ADDR based on n
    
    uint8_t N = n % 256; //keep index between 0-255 
    uint8_t data_w[] = {N, data};
    int ret = i2c_write_blocking(at.i2c_i, at.ADDR, data_w, 2, false);
    return ret;
}

int at24c04_read(at24c04_t at, uint16_t n, uint8_t *buf){
    at.ADDR = n > 255 ? at.ADDR + 1 : at.ADDR; //set ADDR based on n
    uint8_t N = n % 256; //keep index between 0-255 

    int ret = i2c_write_blocking(at.i2c_i, at.ADDR, &N, 1, false); //point to the address reading from
    if (ret<0) return ret;
    ret = i2c_read_blocking(at.i2c_i, at.ADDR, buf, 1, false);
    return ret;
}


int at24c04_write_page(at24c04_t at, uint8_t page, uint8_t *data, uint8_t length){
    at.ADDR = page > 15 ? at.ADDR+1 : at.ADDR;
    length = length > 16? 16 : length; //length should not be more than 16
    uint8_t data_w[length+1];
    data_w[0] = 16*(page%16); //starting address in the memory
    for (uint8_t i = 1; i < length+1; i++)
    {
        data_w[i] = data[i-1];
    }
    int ret = i2c_write_blocking(at.i2c_i, at.ADDR, data_w, length+1, false);
    return ret;
}


int at24c04_read_sequential(at24c04_t at, uint16_t n, uint8_t *buf, uint16_t length){
    at.ADDR = n > 255 ? at.ADDR + 1 : at.ADDR; //set ADDR based on n
    uint8_t N = n % 256; //keep index between 0-255 
    if (i2c_write_blocking(at.i2c_i, at.ADDR, &N, 1, false) < 0) return PICO_ERROR_GENERIC;
    int ret = i2c_read_blocking(at.i2c_i, at.ADDR, buf, length, false);
    return ret;
}
