//
// Small test app to read the WHO_AM_I registers from the LSM9DS1 breakout
// board from Sparkfun, by John Burgess, 1/14/2016
//
// Based on simple I2C example to read the first address of a device in C
// Written by Derek Molloy for the book "Exploring BeagleBone: Tools and
// Techniques for Building with Embedded Linux" by John Wiley & Sons, 2014
// ISBN 9781118935125. Please see the file README.md in the repository root
// directory for copyright and GNU GPLv3 license information.
//
// This is mostly from listing 8.1
//


#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <unistd.h>


#define DEVID_REG   0x0F
// #define DEVADDR     0x1E    // Magnetometer sensor, should readback 0x3d
#define DEVADDR     0x6B    // Accelerometer / Gyroscope sensor, should readback 0x68
#define BUFFER_SIZE 40

int main(void)
{
    int file;
    printf("Starting LSM9DS1 test application\n");
    if ((file = open("/dev/i2c-1", O_RDWR)) < 0 ) {
        perror("Failed to open the bus device\n");
        return 1;
    }

    if (ioctl(file, I2C_SLAVE, DEVADDR) < 0) {
        perror("Failed to connect to the sensor\n");
        return 1;
    }

    char writeBuffer[] = {0x00};
    if (write(file, writeBuffer, 1) != 1) {
        perror("Failed to reset the read address\n");
        return 1;
    }

    char readBuffer[BUFFER_SIZE];
    if (read(file, readBuffer, BUFFER_SIZE) != BUFFER_SIZE) {
        perror("Failed to read in the full buffer\n");
        return 1;
    }

    printf("The device ID is 0x%02x\n", readBuffer[DEVID_REG]);

    close(file);
    return 0;
}

