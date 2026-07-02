# AT24C04 EEPROM Driver for Raspberry Pi Pico (Pico SDK)
A simple driver for using the AT24C04 EEPROM with the Raspberry Pi Pico and pico-sdk. This driver provides basic functionality to read and write data to the AT24C04 EEPROM using the I2C interface.

## Features
- Read single byte
- Write single byte
- Read multiple bytes (sequential read)
- Write multiple bytes (page write)
- Configurable I2C device address via A2 and A1 hardware address pins
- Configurable I2C port and pins

## Hardware Connections
| Pico | AT24C04 | Description |
|------|---------|-------------|
| 3.3V | VCC     | Power supply |
| GND  | GND     | Ground      |
| Selected SDA pin | SDA     | Serial Data Line |
| Selected SCL pin | SCL     | Serial Clock Line |

## API Description
The driver provides the following functions:
| Function | Description | Example Usage |
|----------|-------------|----------------|
| `at24c04_t` | Structure representing the AT24C04 device. Contains the I2C address and port information. | `at24c04_t eeprom;` |
| `at24c04_init()` | Initializes the AT24C04 device with the specified A2 and A1 pin values and I2C port. | `at24c04_init(&eeprom, 0, 0, I2C_PORT);` |
| `at24c04_write()` | Writes a single byte to the specified address in the EEPROM. | `at24c04_write(eeprom, 2, 0x43);` |
| `at24c04_read()` | Reads a single byte from the specified address in the EEPROM and stores it in a buffer. | `at24c04_read(eeprom, 2, &buf);` |
| `at24c04_write_page()` | Writes multiple bytes to the EEPROM at a specified page. Maximum 16 bytes per page. | `strcpy(n, "Rasp. Pi Pico");` `at24c04_write_page(eeprom, 0, n, strlen(n)+1);` |
| `at24c04_read_sequential()` | Reads multiple bytes from the EEPROM starting at a specified address and stores them in a buffer. | `at24c04_read_sequential(eeprom, 0, buff, 64);` |

## Usage
- Copy the `at24c04.h` and `at24c04.c` files into your project directory.
- Include `at24c04.c` in `add_executable()` in your `CMakeLists.txt` file.
    ```CMake
    add_executable(eeprom_24c04 at24c04_example.c ../at24c04.c )
    ```
## Example
The [Examples/at24c04_example.c](./Examples/at24c04_example.c) file demonstrates how to use the driver. Here's how you can compile and run the example:
1. Open the `Examples` directory, and build the example using CMake.
    ```bash
    mkdir build && cd build && cmake .. && make
    ```
2. Upload the generated UF2 file to your Raspberry Pi Pico.

### Example explanation and output
1. First, create an instance of the EEPROM device and initialize it with the desired A2 and A1 pin values.
    ```c
    at24c04_t eeprom;
    at24c04_init(&eeprom, 0, 0, I2C_PORT);
    ```
2. Then, write single bytes of data to the EEPROM at specific addresses. Wait for the self-timed write cycle after each write operation.
    ```c
    at24c04_write(eeprom, 2, 0x43);
    sleep_ms(5); //wait for  self-timed write cycle
    at24c04_write(eeprom, 255, 0x33);
    sleep_ms(5);
    at24c04_write(eeprom, 300, 0x53);
    ```
3. Read the single bytes back from the EEPROM and print them to the serial monitor.
    ```c
    at24c04_read(eeprom, 2, &buf);
    printf("Read: 0x%02X\n", buf);
    at24c04_read(eeprom, 255, &buf);
    printf("Read: 0x%02X\n", buf);
    at24c04_read(eeprom, 300, &buf);
    printf("Read: 0x%02X\n", buf);
    ```
    **Output**
    ```
    Writing single byte data...
    Reading single byte data....
    Read: 0x43
    Read: 0x33
    Read: 0x53
    ```
4. Write a string of data to the EEPROM using the page write function. The maximum number of bytes that can be written in a single page write operation is 16 bytes.
    ```c
    strcpy(n, "Rasp. Pi Pico");
    ret = at24c04_write_page(eeprom, 0, n, strlen(n)+1); 
    printf("Written: %s\tBytes: %d\n", n, ret);
    sleep_ms(5); //self-timed write cycle
    ``` 
    **Output**
    ```
    Writing data to page....
    Written: Rasp. Pi Pico  Bytes: 15
    ```
5. Read the string of data back from the EEPROM using the sequential read function and print it to the serial monitor.
    ```c
    at24c04_read_sequential(eeprom, 0, buff, 64);
    printf("Page = %d\tData = %s\n", 0, buff + 16*0);
    ```
    **Output**
    ```
    Reading data sequentially...
    Page = 0        Data = Rasp. Pi Pico
    ```

## References
- [AT24C04 Datasheet](https://ww1.microchip.com/downloads/en/DeviceDoc/AT24C04C-AT24C08C-I2C-Compatible-%20Two-Wire-Serial-EEPROM-4-Kbit-8-Kbit-20006127A.pdf)
- [Raspberry Pi Pico C/C++ SDK](https://pip-assets.raspberrypi.com/categories/609-microcontroller-boards/documents/RP-009085-KB-1-raspberry-pi-pico-c-sdk.pdf)
- [RP2040 Datasheet](https://pip-assets.raspberrypi.com/categories/814-rp2040/documents/RP-008371-DS-1-rp2040-datasheet.pdf)

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.