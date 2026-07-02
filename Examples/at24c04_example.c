#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "at24c04.h"
#include <string.h>

/// Pin definitions for I2C
#define I2C_PORT i2c0
#define I2C_SDA 4
#define I2C_SCL 5


int main()
{
    stdio_init_all();

    // I2C Initialisation. Using it at 100Khz.
    i2c_init(I2C_PORT, 100*1000);
    
    // Set up the I2C pins
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    // Create an instance of the EEPROM device
    at24c04_t eeprom;

    // Initialize the EEPROM device with A2=0, A1=0
    at24c04_init(&eeprom, 0, 0, I2C_PORT);

    // Buffers and variables for reading/writing data
    uint8_t buf; //buffer for reading single byte
    char buff[64]; //buffer for reading sequential 'char' data
    char n[16]; //array to store data to write page
    int ret; //variable to store return value from functions
    sleep_ms(5000);


    while (true) {

        //write single byte data
        printf("Writing single byte data...\n");
        at24c04_write(eeprom, 2, 0x43);
        sleep_ms(5); //wait for  self-timed write cycle
        at24c04_write(eeprom, 255, 0x33);
        sleep_ms(5);
        at24c04_write(eeprom, 300, 0x53);
        sleep_ms(5);
        at24c04_write(eeprom, 511, 0x21);
        sleep_ms(5);
        at24c04_write(eeprom, 256, 0x78);
        sleep_ms(5);
        sleep_ms(5000);
        
        //read single byte data
        printf("Reading single byte data....\n");
        at24c04_read(eeprom, 2, &buf);
        printf("Read: 0x%02X\n", buf);
        at24c04_read(eeprom, 255, &buf);
        printf("Read: 0x%02X\n", buf);
        at24c04_read(eeprom, 300, &buf);
        printf("Read: 0x%02X\n", buf);
        at24c04_read(eeprom, 511, &buf);
        printf("Read: 0x%02X\n", buf);
        at24c04_read(eeprom, 256, &buf);
        printf("Read: 0x%02X\n", buf);
        at24c04_read(eeprom, 32, &buf);
        printf("Read: 0x%02X\n", buf);
        sleep_ms(5000);

        //write data to page
        printf("Writing data to page....\n");
        strcpy(n, "Rasp. Pi Pico");
        ret = at24c04_write_page(eeprom, 0, n, strlen(n)+1); //strlen(n)+1: +1 for including \0
        printf("Written: %s\tBytes: %d\n", n, ret);
        sleep_ms(5);
        strcpy(n, "EEPROM AT24C04");
        ret = at24c04_write_page(eeprom, 1, n, strlen(n)+1);
        printf("Written: %s\tBytes: %d\n", n, ret);
        sleep_ms(5);
        strcpy(n, "Hello World");
        ret = at24c04_write_page(eeprom, 2, n, strlen(n)+1);
        printf("Written: %s\tBytes: %d\n", n, ret);
        sleep_ms(5000);

        //read data sequentially
        printf("Reading data sequentially...\n");
        at24c04_read_sequential(eeprom, 0, buff, 64);
        printf("Page = %d\tData = %s\n", 0, buff + 16*0);
        printf("Page = %d\tData = %s\n", 1, buff + 16*1);
        printf("Page = %d\tData = %s\n", 2, buff + 16*2);
        sleep_ms(5000);
    }
}
