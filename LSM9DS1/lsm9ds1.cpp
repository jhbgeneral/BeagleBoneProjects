#include "lsm9ds1.h"

#include <math.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/ioctl.h>
// #include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <unistd.h>


LSM9DS1::LSM9DS1(unsigned int i2cBus, unsigned int i2cAddress) :
    I2CDevice (i2cBus, i2cAddress), // this member initialisation list calls the parent constructor
    i2cBus(i2cBus),
    i2cAddress(i2cAddress)
{

    // The I2CDevice constructor does the open() and ioctl()
    //    if ((file = open("/dev/i2c-1", O_RDWR)) < 0 ) {
    //        perror("Failed to open the bus device\n");
    //        return 1;
    //    }
    //
    //    if (ioctl(file, I2C_SLAVE, DEVADDR) < 0) {
    //        perror("Failed to connect to the sensor\n");
    //        return 1;
    //    }
}

LSM9DS1::~LSM9DS1()
{

}

/**
 * Read the sensor state. This method checks that the device is being correctly
 * read by using the device ID of the ADXL345 sensor. It will read in the accelerometer registers
 * and pass them to the combineRegisters() method to be processed.
 * @return 0 if the registers are successfully read and -1 if the device ID is incorrect.
 */
int LSM9DS1::readSensorState()
{
    // readRegisters() allocated a buffer; delete it when done
    this->registers = this->readRegisters(BUFFER_SIZE, 0x00);

    // Verify the device type
    if ( *(this->registers + DEVID_REG) != ACC_DEVID)
    {
        perror("LSM9DS1: Failure Condition - Incorrect Sensor ID");
        return -1;
    }
    perror("LSM9DS1: Verified Sensor ID");

//	this->accelerationX = this->combineRegisters(*(registers+DATAX1), *(registers+DATAX0));
//	this->accelerationY = this->combineRegisters(*(registers+DATAY1), *(registers+DATAY0));
//	this->accelerationZ = this->combineRegisters(*(registers+DATAZ1), *(registers+DATAZ0));
//	this->resolution = (ADXL345::RESOLUTION) (((*(registers+DATA_FORMAT))&0x08)>>3);
//	this->range = (ADXL345::RANGE) ((*(registers+DATA_FORMAT))&0x03);
    delete registers;

//	this->calculatePitchAndRoll();
    return 0;
}

/**
 * Method to combine two 8-bit registers into a single short, which is 16-bits on the BBB. It shifts
 * the MSB 8-bits to the left and then ORs the result with the LSB.
 * @param msb an unsigned character that contains the most significant byte
 * @param lsb an unsigned character that contains the least significant byte
 */
short LSM9DS1::combineRegisters(unsigned char msb, unsigned char lsb){
   //shift the MSB left by 8 bits and OR with LSB
   return ((short)msb<<8)|(short)lsb;
}

