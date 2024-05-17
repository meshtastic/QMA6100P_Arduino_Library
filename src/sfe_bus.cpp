// sfe_bus.cpp
//
// This is a library written for SparkFun Qwiic QMA6100P
//

// The following classes specify the behavior for communicating
// over the respective data buses: Inter-Integrated Circuit (I2C)

#include "sfe_bus.h"
#include <Arduino.h>

namespace sfe_QMA6100P
{

#define kMaxTransferBuffer 32

  // What we use for transfer chunk size
  const static uint16_t kChunkSize = kMaxTransferBuffer;

  //////////////////////////////////////////////////////////////////////////////////////////////////
  // Constructor
  //

  QwI2C::QwI2C(void) : _i2cPort{nullptr}
  {
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////
  // I2C init()
  //
  // Methods to init/setup this device. The caller can provide a Wire Port, or this class
  // will use the default

  bool QwI2C::init(TwoWire &wirePort, bool bInit)
  {

    // if we don't have a wire port already
    if (!_i2cPort)
    {
      _i2cPort = &wirePort;

      if (bInit)
        _i2cPort->begin();
    }

    return true;
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////
  // I2C init()
  //
  // Methods to init/setup this device. The caller can provide a Wire Port, or this class
  // will use the default
  bool QwI2C::init()
  {
    if (!_i2cPort)
      return init(Wire);
    else
      return false;
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////
  // ping()
  //
  // Is a device connected?
  bool QwI2C::ping(uint8_t i2c_address)
  {

    if (!_i2cPort)
      return false;

    _i2cPort->beginTransmission(i2c_address);
    return _i2cPort->endTransmission() == 0;
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////
  // writeRegisterByte()
  //
  // Write a byte to a register

  bool QwI2C::writeRegisterByte(uint8_t i2c_address, uint8_t offset, uint8_t dataToWrite)
  {

    if (!_i2cPort)
      return -1;

    _i2cPort->beginTransmission(i2c_address);
    _i2cPort->write(offset);
    _i2cPort->write(dataToWrite);
    return (_i2cPort->endTransmission() == 0); // true = success, false = error
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////
  // writeRegisterRegion()
  //
  // Write a block of data to a device.

  int QwI2C::writeRegisterRegion(uint8_t i2c_address, uint8_t offset, const uint8_t *data, uint16_t length)
  {

    if (!_i2cPort)
      return -1;

    _i2cPort->beginTransmission(i2c_address);
    _i2cPort->write(offset);
    _i2cPort->write(data, (int)length);

    return _i2cPort->endTransmission() == 0 ? 0 : -1; // 0 = success, -1 = error
  }

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////
  // readRegisterRegion()
  //
  // Reads a block of data from an i2c register on the devices.
  //
  // For large buffers, the data is chuncked over KMaxI2CBufferLength at a time
  //
  //
  int QwI2C::readRegisterRegion(uint8_t addr, uint8_t reg, uint8_t *data, uint16_t numBytes)
  {
    uint8_t nChunk;
    uint16_t nReturned;

    if (!_i2cPort)
      return -1;

    int i;             // counter in loop
    int failCount = 0; // Keep track of how many times nReturned is != nChunk

    while ((numBytes > 0) && (failCount < 2)) // Give up after 2 bad requests
    {
      _i2cPort->beginTransmission(addr);
      _i2cPort->write(reg); // Write the register address we want to read from
      if (_i2cPort->endTransmission() != 0)
        return -1; // Fail immediately if the transmission isn't successful

      // We're chunking in data - keeping the max chunk to kMaxI2CBufferLength
      nChunk = numBytes > kChunkSize ? kChunkSize : numBytes;

      nReturned = _i2cPort->requestFrom((int)addr, (int)nChunk, (int)true); // Always send a stop

      // No data returned, no dice
      if (nReturned == 0)
        return -1; // error

      // Check we got back as much data as was requested.
      // (Fringe case. This should never happen... But, you know, it _could_...)
      if (nReturned != nChunk)
        failCount++; // Increment the failCount

      // Copy the retrieved data chunk to the current index in the data segment
      for (i = 0; i < nReturned; i++)
      {
        *data++ = _i2cPort->read();
      }

      // Decrement the amount of data recieved from the overall data request amount
      numBytes = numBytes - nReturned;

      // Increment reg by the same ammount
      reg += nReturned;

    } // end while

    return (numBytes == 0 ? 0 : -1); // 0 = success (all bytes read), -1 = error
  }

}