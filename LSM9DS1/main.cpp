#include <iostream>
#include <math.h>

#include "i2cdevice.h"

int writeRegister (int file, unsigned char address, char value);
int readRegisters (int file);

using namespace std;

// // Main application entry point
// int main (int argc, char *argv[])
// {
//     cout << "argc = " << argc << "; argv[0] = \"" << argv[0] << "\"" << endl;
// }


#if 1
//
// Small test app to read the WHO_AM_I registers from the LSM9DS1 breakout
// board from Sparkfun, by John Burgess, 1/14/2016
//
// Based on simple I2C example to read the first address of a device in C
// Written by Derek Molloy for the book "Exploring BeagleBone: Tools and
// Techniques for Building with Embedded Linux" by John Wiley & Sons, 2014
// ISBN 9781118935125. Please see the file README.md in the repository root
// directory for copyright and GNU GPLv3 license information.


#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
// #include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <unistd.h>


#define DEVID_REG   0x0F
// #define DEVADDR     0x1E    // Magnetometer sensor, should readback 0x3d
#define DEVADDR     0x6B    // Accelerometer / Gyroscope sensor, should readback 0x68
#define BUFFER_SIZE 0x40
#define ACCEL_VALS_BASE 0x28
enum {
    ACCEL_X_LO_OFST = 0,
    ACCEL_X_HI_OFST,
    ACCEL_Y_LO_OFST,
    ACCEL_Y_HI_OFST,
    ACCEL_Z_LO_OFST,
    ACCEL_Z_HI_OFST,
    ACCEL_VALS_SIZE
};

// Small macro to display value in hexadecimal with 2 places
#define COMBINE_VALUES(lo,hi) ((short)((((short) hi) << 8) | ((short) lo)))

char readBuffer[BUFFER_SIZE];

int main(void)
{
    printf("Starting LSM9DS1 test application\n");

    // The constructor does the open() and ioctl()
    I2CDevice dev (1, DEVADDR);

// The above constructor does the open() and ioctl()
//    if ((file = open("/dev/i2c-1", O_RDWR)) < 0 ) {
//        perror("Failed to open the bus device\n");
//        return 1;
//    }
//
//    if (ioctl(file, I2C_SLAVE, DEVADDR) < 0) {
//        perror("Failed to connect to the sensor\n");
//        return 1;
//    }

    readBuffer[0] = dev.readRegister(DEVID_REG);

// The above does the write (to set the address) and the read
//    {
//        char writeBuffer[] = {DEVID_REG};
//        if (write(file, writeBuffer, sizeof(writeBuffer)) != sizeof(writeBuffer)) {
//            perror("Failed to set the read address\n");
//            return 1;
//        }
//    }
//
//    if (read(file, readBuffer, 1) != 1) {
//        perror("Failed to read in the full buffer\n");
//        return 1;
//    }

    printf("The device ID is 0x%02x\n", readBuffer[0]);

    int file = 0;

    // Turn the accelerometer ON by writing 0x20 to register address 0x20
    dev.writeRegister(0x20, 0x20);

// The above does the register write
//    {
//        char writeBuffer[] = {0x20, 0x20};
//        if (write(file, writeBuffer, sizeof(writeBuffer)) != sizeof(writeBuffer)) {
//            perror("Failed to set the read address\n");
//            return 1;
//        }
//    }

    // Let it settle
    usleep(200000);

    // Read and display the accelerometer X, Y, & Z values a bunch of times
    double sum = 0;
    do
    {
        // Read the raw accelerometer values registers
        unsigned char *readBuffer = dev.readRegisters(ACCEL_VALS_SIZE, ACCEL_VALS_BASE);

//        // Set the address to read from
//        char writeBuffer[] = { ACCEL_VALS_BASE };
//        if (write(file, writeBuffer, sizeof(writeBuffer)) != sizeof(writeBuffer)) {
//            perror("Failed to set the read address\n");
//            return 1;
//        }
//
//        // Read the raw accelerometer values registers
//        char readBuffer[ACCEL_VALS_SIZE];
//        if (read(file, readBuffer, ACCEL_VALS_SIZE) != ACCEL_VALS_SIZE) {
//            perror("Failed to read in the accelerometer value regs\n");
//            return 1;
//        }

        // Convert register values into real numbers
        double x = COMBINE_VALUES (readBuffer[ACCEL_X_LO_OFST], readBuffer[ACCEL_X_HI_OFST]);
        double y = COMBINE_VALUES (readBuffer[ACCEL_Y_LO_OFST], readBuffer[ACCEL_Y_HI_OFST]);
        double z = COMBINE_VALUES (readBuffer[ACCEL_Z_LO_OFST], readBuffer[ACCEL_Z_HI_OFST]);
        double scale = 16384;
        x /= scale; y /= scale; z /= scale;

        sum = x * x + y * y + z * z;
        sum = sqrt(sum);

//        cout << "X = " << x  << "; Y = " << y << "; Z = " << z << "; sum = " << sum << endl;
        printf ("X = %6.3f, Y = %6.3f, Z = %6.3f, sum = %6.3f", x, y, z, sum);
        cout << endl;
//        flush(STDOUT_FILENO);
        usleep(200000);

        if (readBuffer) delete readBuffer;

    } while (sum > 0.2);

    // Turn the accelerometer OFF by writing 0x00 to register address 0x20
    dev.writeRegister(0x20, 0x00);

//    {
//        char writeBuffer[] = {0x20, 0x00};
//        if (write(file, writeBuffer, sizeof(writeBuffer)) != sizeof(writeBuffer)) {
//            perror("Failed to set the read address\n");
//            return 1;
//        }
//    }


//    printf("0x21 0x00 = %d\n", COMBINE_VALUES(0x21, 0x00));
//    printf("0x1c 0xff = %d\n", COMBINE_VALUES(0x1c, 0xff));
//    printf("0xac 0x3f = %d\n", COMBINE_VALUES(0xac, 0x3f));
//    printf("0x18 0x00 = %d\n", COMBINE_VALUES(0x18, 0x00));

    close(file);
    return 0;
}
#endif
