#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "at24c04.h"
#include <string.h>


#define I2C_PORT i2c0
#define I2C_SDA 4
#define I2C_SCL 5


int main()
{
    stdio_init_all();

    // I2C Initialisation. Using it at 100Khz.
    i2c_init(I2C_PORT, 100*1000);
    
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    at24c04_t eeprom;

    at24c04_init(&eeprom, 0, 0, I2C_PORT);
    
    
    
    // uint8_t ADDR = (AD>>1) + (A2<<2) + (A1<<1) + A8;
    // uint8_t data_w[] = {0x00, 0x69, 0x67};
    // uint8_t add_set = 0x00;
    // uint8_t data_r;
    // int ret;
    uint8_t buf;
    char name[] = "0blahablahablahjdrw";
    char buuf[550];
    char n[32];
    sleep_ms(5000);

    while (true) {
        
        // for (uint8_t i = 0; i < sizeof(name); i++)
        // {
        //     if (at24c04_read(eeprom, i, buuf+i) < 0){
        //         printf("Data not read\n");
        //     }
        //     // sleep_ms(5);
        int ret;
        // }
        // name[0] = 0x00;
        // int ret = i2c_write_blocking(eeprom.i2c_i, eeprom.ADDR, name, 18, false);
        // printf("Data bytes written: %d\n", ret);
        // sleep_ms(10);
        
        strcpy(n, "fff");
        ret = at24c04_write_page(eeprom, 0+16, n, strlen(n)+1);
        printf("Written: %s\tBytes: %d\n", n, ret);
        sleep_ms(10);
        strcpy(n, "pokemon");
        ret = at24c04_write_page(eeprom, 1+16, n, strlen(n)+1);
        printf("Written: %s\tBytes: %d\n", n, ret);
        sleep_ms(10);
        strcpy(n, "aage badho");
        ret = at24c04_write_page(eeprom, 2+16, n, strlen(n)+1);
        printf("Written: %s\tBytes: %d\n", n, ret);
        sleep_ms(10);
        strcpy(n, "dattebayo");
        ret = at24c04_write_page(eeprom, 3+16, n, strlen(n)+1);
        printf("Written: %s\tBytes: %d\n", n, ret);
        sleep_ms(10);
        strcpy(n, "bleach");
        ret = at24c04_write_page(eeprom, 4+16, n, strlen(n)+1);
        printf("Written: %s\tBytes: %d\n", n, ret);
        sleep_ms(10);
        strcpy(n, "ball");
        ret = at24c04_write_page(eeprom, 5+16, n, strlen(n)+1);
        printf("Written: %s\tBytes: %d\n", n, ret);
        sleep_ms(10);
        strcpy(n, "aizen");
        ret = at24c04_write_page(eeprom, 6+16, n, strlen(n)+1);
        printf("Written: %s\tBytes: %d\n", n, ret);
        sleep_ms(10);
        strcpy(n, "ohayo");
        ret = at24c04_write_page(eeprom, 7+16, n, strlen(n)+1);
        printf("Written: %s\tBytes: %d\n", n, ret);
        sleep_ms(10);
        strcpy(n, "let's go");
        ret = at24c04_write_page(eeprom, 8+16, n, strlen(n)+1);
        printf("Written: %s\tBytes: %d\n", n, ret);
        sleep_ms(10);
        strcpy(n, "wait a sec");
        ret = at24c04_write_page(eeprom, 9+16, n, strlen(n)+1);
        printf("Written: %s\tBytes: %d\n", n, ret);
        sleep_ms(10);
        strcpy(n, "leg");
        ret = at24c04_write_page(eeprom, 10+16, n, strlen(n)+1);
        printf("Written: %s\tBytes: %d\n", n, ret);
        sleep_ms(10);
        strcpy(n, "help");
        ret = at24c04_write_page(eeprom, 11+16, n, strlen(n)+1);
        printf("Written: %s\tBytes: %d\n", n, ret);
        sleep_ms(10);
        strcpy(n, "Wake up to");
        ret = at24c04_write_page(eeprom, 12+16, n, strlen(n)+1);
        printf("Written: %s\tBytes: %d\n", n, ret);
        sleep_ms(10);
        strcpy(n, "reality");
        ret = at24c04_write_page(eeprom, 13+16, n, strlen(n)+1);
        printf("Written: %s\tBytes: %d\n", n, ret);
        sleep_ms(10);
        strcpy(n, "ghar ja bete");
        ret = at24c04_write_page(eeprom, 14+16, n, strlen(n)+1);
        printf("Written: %s\tBytes: %d\n", n, ret);
        sleep_ms(10);
        strcpy(n, "aur soja");
        ret = at24c04_write_page(eeprom, 15+16, n, strlen(n)+1);
        printf("Written: %s\tBytes: %d\n", n, ret);
        sleep_ms(10);
        

        // uint8_t test = 0x00;
        // if(i2c_write_blocking(eeprom.i2c_i, eeprom.ADDR, &test, 1, false) < 0)  printf("Unable to access address\n");
        ret = at24c04_read_sequential(eeprom, 0, buuf, 512);
        printf("read bytes : %d\n", ret);
        printf("Data read : %s\n", buuf);
        printf("Page = %d\tData = %s\n", 0, buuf + 16*0);
        printf("Page = %d\tData = %s\n", 1, buuf + 16*1);
        printf("Page = %d\tData = %s\n", 2, buuf + 16*2);
        printf("Page = %d\tData = %s\n", 3, buuf + 16*3);
        printf("Page = %d\tData = %s\n", 4, buuf + 16*4);
        printf("Page = %d\tData = %s\n", 5, buuf + 16*5);
        printf("Page = %d\tData = %s\n", 6, buuf + 16*6);
        printf("Page = %d\tData = %s\n", 7, buuf + 16*7);
        printf("Page = %d\tData = %s\n", 8, buuf + 16*8);
        printf("Page = %d\tData = %s\n", 9, buuf + 16*9);
        printf("Page = %d\tData = %s\n", 10, buuf + 16*10);
        printf("Page = %d\tData = %s\n", 11, buuf + 16*11);
        printf("Page = %d\tData = %s\n", 12, buuf + 16*12);
        printf("Page = %d\tData = %s\n", 13, buuf + 16*13);
        printf("Page = %d\tData = %s\n", 14, buuf + 16*14);
        printf("Page = %d\tData = %s\n", 15, buuf + 16*15);
        
        
        printf("Page = %d\tData = %s\n", 0+16, buuf + 16*(0+16));
        printf("Page = %d\tData = %s\n", 1+16, buuf + 16*(1+16));
        printf("Page = %d\tData = %s\n", 2+16, buuf + 16*(2+16));
        printf("Page = %d\tData = %s\n", 3+16, buuf + 16*(3+16));
        printf("Page = %d\tData = %s\n", 4+16, buuf + 16*(4+16));
        printf("Page = %d\tData = %s\n", 5+16, buuf + 16*(5+16));
        printf("Page = %d\tData = %s\n", 6+16, buuf + 16*(6+16));
        printf("Page = %d\tData = %s\n", 7+16, buuf + 16*(7+16));
        printf("Page = %d\tData = %s\n", 8+16, buuf + 16*(8+16));
        printf("Page = %d\tData = %s\n", 9+16, buuf + 16*(9+16));
        printf("Page = %d\tData = %s\n", 10+16, buuf + 16*(10+16));
        printf("Page = %d\tData = %s\n", 11+16, buuf + 16*(11+16));
        printf("Page = %d\tData = %s\n", 12+16, buuf + 16*(12+16));
        printf("Page = %d\tData = %s\n", 13+16, buuf + 16*(13+16));
        printf("Page = %d\tData = %s\n", 14+16, buuf + 16*(14+16));
        printf("Page = %d\tData = %s\n", 15+16, buuf + 16*(15+16));
        
        

        /*
        //write data test
        at24c04_write(eeprom, 2, 0x43);
        sleep_ms(5);
        at24c04_write(eeprom, 255, 0x33);
        sleep_ms(5);
        at24c04_write(eeprom, 300, 0x53);
        sleep_ms(5);
        at24c04_write(eeprom, 511, 0x21);
        sleep_ms(5);
        at24c04_write(eeprom, 256, 0x78);
        sleep_ms(5);
        printf("Written data\n");
        sleep_ms(5000);
        */

        /*
        //read data test
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
        */
        /*
        //Testing available
        int ret = i2c_write_blocking(I2C_PORT, eeprom.ADDR, data_w, 1, false);
        if (ret > 0)
        {
            printf("Successfully sent data on device at: 0x%02X\n", eeprom.ADDR);
        }
        else
        {
            printf("Error: %d\n", ret);
        }
        
        sleep_ms(5000);
        */
       /*write and then read
        //write data
        ret = i2c_write_blocking(I2C_PORT, ADDR, data_w, 3, false);
       if(ret>0) printf("Data succesful written, written : %d\n", ret);
       sleep_ms(5); //t_wr

       //read data
       ret = i2c_write_blocking(I2C_PORT, ADDR, &add_set, 1, false);
       if(ret>0) printf("Address set success\n");
       ret = i2c_read_blocking(I2C_PORT, ADDR, &data_r, 1, false);
       if (ret > 0)
       {
        printf("Read success, data read is: 0x%02X\n", data_r);
       }
       else
       {
        printf("unable to read, error : %d\n", ret);
       }
       ret = i2c_read_blocking(I2C_PORT, ADDR, &data_r, 1, false);
       if (ret > 0)
       {
        printf("Read success, data read is: 0x%02X\n", data_r);
       }
       else
       {
        printf("unable to read, error : %d\n", ret);
       }
       sleep_ms(5000);
    //    PICO_ERROR_GENERIC
    */
       
        sleep_ms(5000);
        

    }
}
