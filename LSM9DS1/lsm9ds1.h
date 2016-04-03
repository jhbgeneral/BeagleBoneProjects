#ifndef LSM9DS1_H
#define LSM9DS1_H

#include "i2cdevice.h"

#define DEVID_REG   0x0F
// #define DEVADDR     0x1E    // Magnetometer sensor, should readback 0x3d
#define ACC_DEVADDR     0x6B    // Accelerometer / Gyroscope sensor ID,
#define ACC_DEVID       0x68    // should readback 0x68
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


class LSM9DS1 : public I2CDevice
{

public:
    LSM9DS1(unsigned int i2cBus, unsigned int i2cAddress);
    ~LSM9DS1();

    short combineRegisters(unsigned char msb, unsigned char lsb);
    virtual int readSensorState();

private:
    unsigned int i2cBus, i2cAddress;
    unsigned char *registers;
};

#endif // LSM9DS1_H
