// sfe_bus.h
//
// This is a library written for SparkFun Qwiic  QMA6100P boards

// The following classes specify the behavior for communicating
// over the respective data buses: Inter-Integrated Circuit (I2C)
// an abstract interface (QwIDeviceBus) is used.

#pragma once

#include <Wire.h>

namespace sfe_QMA6100P
{

  // The following abstract class is used an interface for upstream implementation.
  class QwIDeviceBus
  {
  public:
    virtual bool ping(uint8_t address) = 0;

    virtual bool writeRegisterByte(uint8_t address, uint8_t offset, uint8_t data) = 0;

    virtual int writeRegisterRegion(uint8_t address, uint8_t offset, const uint8_t *data, uint16_t length) = 0;

    virtual int readRegisterRegion(uint8_t addr, uint8_t reg, uint8_t *data, uint16_t numBytes) = 0;
  };

  // The QwI2C device defines behavior for I2C implementation based around the TwoWire class (Wire).
  // This is Arduino specific.
  class QwI2C : public QwIDeviceBus
  {
  public:
    QwI2C(void);

    bool init();

    bool init(TwoWire &wirePort, bool bInit = false);

    bool ping(uint8_t address);

    bool writeRegisterByte(uint8_t address, uint8_t offset, uint8_t data);

    int writeRegisterRegion(uint8_t address, uint8_t offset, const uint8_t *data, uint16_t length);

    int readRegisterRegion(uint8_t addr, uint8_t reg, uint8_t *data, uint16_t numBytes);

  private:
    TwoWire *_i2cPort;
  };

};