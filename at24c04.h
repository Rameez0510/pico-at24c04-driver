/**
 * @file at24c04.h
 * 
 * AT24C04 EEPROM driver for Raspberry Pi Pico
 */

#include "pico/stdlib.h"
#include "hardware/i2c.h"

/**
 * @brief holds info about the device
 */
typedef struct{
    uint8_t ADDR; /**< Address of the device */
    i2c_inst_t *i2c_i; /**< I2C instance */
} at24c04_t;


/**
 * @brief initialize the address based on A2 and A1 pins state
 * @param at  pointer for at24c04_t
 * @param A2 A2 pin
 * @param A1 A1 pin
 * @param i2c_port instance for i2c communication
 */
void at24c04_init(at24c04_t *at, uint8_t A2, uint8_t A1, i2c_inst_t *i2c_port);


/**
 * @brief Write a single byte at index "n"
 * @warning Must write next data after "Self-timed write cylce", maximum wait time ~ 5ms
 * @param at instance for device
 * @param n Index between 0-511
 * @param data data to write
 * @return -1 if address not acknowledged 
 */
int at24c04_write(at24c04_t at, uint16_t n, uint8_t data);


/**
 * @brief Read a single byte at index "n"
 * @param at instance for device
 * @param n Index between 0-511
 * @param buf Buffer pointer to store data
 * @return -1 if address not acknowledged 
 */
int at24c04_read(at24c04_t at, uint16_t n, uint8_t *buf);


/**
 * @brief Write data on a page
 * @warning Length of data should not be more than 16 bytes
 * @warning Must write next data after "Self-timed write cylce", maximum wait time ~ 5ms
 * @param at instance for device
 * @param page Page for the data to write on, 0-31
 * @param data Pointer of the data to write
 * @param length Length of data to write, 1-16
 * @return Number of bytes written, -1 if address not acknowleged 
 */
int at24c04_write_page(at24c04_t at, uint8_t page, uint8_t *data, uint8_t length);


/**
 * @brief Read bytes sequentially
 * @param at Instance for the device
 * @param n Address in the memory
 * @param buf Buffer to store data
 * @param length Number of bytes to read
 * @return Number of bytes read, -1 if address not acknowledged 
 */
int at24c04_read_sequential(at24c04_t at, uint16_t n, uint8_t *buf, uint16_t length);