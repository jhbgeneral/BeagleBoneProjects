/** Sample I2C LSM9DS1 Code that outputs the x,y and z accelerometer values
*   on a single line for sixty seconds.
* Original by Derek Molloy for the book "Exploring BeagleBone: Tools and
* Techniques for Building with Embedded Linux" by John Wiley & Sons, 2014
* ISBN 9781118935125.       */

#include <iostream>
// #include <stdio.h>
// #include <fcntl.h>
#include <unistd.h>

using namespace std;

// Write a single value to a single register
int writeRegister (int file, unsigned char address, char value) {
   unsigned char buffer[2];
   buffer[0] = address;
   buffer[1] = value;
   if (write (file, buffer, 2) != 2) {
      cout << "Failed write to the device" << endl;
      return 1;
   }
   return 0;
}

// Read the entire ??? 40 ??? registers into the buffer
int readRegisters (int file)
{
    // Write a 0x00 to the device to set the address to 0x00 for the
    // coming block read
    writeRegister (file, 0x00, 0x00);
    return 0;
}
