// The following class implements the	methods to set, get, and read from the Triple
// Axis Acceleromter - QMA6100P.

#pragma once

#include <Wire.h>
#include "QMA6100P_regs.h"

#define QMA6100P_ADDRESS_HIGH 0x13
#define QMA6100P_ADDRESS_LOW 0x12

#define QMA6100P_CHIP_ID 0x90

// CNTL1 GSEL<1:0>
#define SFE_QMA6100P_RANGE2G 0b0001
#define SFE_QMA6100P_RANGE4G 0b0010
#define SFE_QMA6100P_RANGE8G 0b0100
#define SFE_QMA6100P_RANGE16G 0b1000
#define SFE_QMA6100P_RANGE32G 0b1111

#define TOTAL_ACCEL_DATA_8BIT 3
#define TOTAL_ACCEL_DATA_16BIT 6

struct outputData
{
  float xData;
  float yData;
  float zData;
};

struct rawOutputData
{
  int16_t xData;
  int16_t yData;
  int16_t zData;
};

class QwDevQMA6100P
{
public:

  bool begin();
  uint8_t getUniqueID();
  bool writeRegisterByte(uint8_t registerAddress, uint8_t data);
  bool readRegisterRegion(uint8_t registerAddress, uint8_t* sensorData, int len);
  

  bool getAccelData(outputData *userData);
  bool convAccelData(outputData *userAccel, rawOutputData *rawAccelData);

  // General Settings
  bool enableAccel(bool enable = true);
  bool softwareReset();
  int8_t getOperatingMode();
  bool setRange(uint8_t);
  bool enableDataEngine(bool enable = true);
  bool dataReady();
  bool getRawAccelRegisterData(rawOutputData *);
  void offsetValues(float &x, float &y, float &z);

  int getRange();

  rawOutputData rawAccelData;

  // QMA6100P conversion values
  const double convRange2G = .000244;
  const double convRange4G = .000488;
  const double convRange8G = .000977;
  const double convRange16G = .001950;
  const double convRange32G = .003910;

protected:
  int _range = -1; // Keep a local copy of the range. Default to "unknown" (-1).
};