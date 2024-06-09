#include "Qwiic_QMA6100P.h"

uint8_t QwDevQMA6100P::getUniqueID()
{
  uint8_t tempVal;
  if(!readRegisterRegion(SFE_QMA6100P_CHIP_ID, &tempVal, 1))
    return 0xFF;

  return tempVal;
}

//////////////////////////////////////////////////
// softwareReset()
//
// writing 0xB6 to 0x36, soft reset all of the registers. 
// After soft-reset, user should write 0x00 back
//
bool QwDevQMA6100P::softwareReset()
{
  if(!writeRegisterByte(SFE_QMA6100P_SR, static_cast<uint8_t>(0xb6)))
    return false;

  sfe_qma6100p_sr_bitfeild_t sr;

  for(int i = 0; i < 10; i ++){
    if(!readRegisterRegion(SFE_QMA6100P_SR, &sr.all, 1))
      return false;

    if(sr.all == 0xb6)
      break;
    delay(1);
  }

  if(!writeRegisterByte(SFE_QMA6100P_SR, 0x00))
    return false;

  return true;
}

//////////////////////////////////////////////////
// enableAccel()
//
// Enables accelerometer data. In addition
// some settings can only be set when the accelerometer is
// powered down
//
// Parameter:
// enable - enables or disables the accelerometer
//
//
bool QwDevQMA6100P::enableAccel(bool enable)
{

  uint8_t tempVal;

  if(!readRegisterRegion(SFE_QMA6100P_PM, &tempVal, 1))
    return false;

  sfe_qma6100p_pm_bitfield_t pm;
  pm.all = tempVal;
  pm.bits.mode_bit = enable; // sets QMA6100P to active mode
  tempVal = pm.all;

  if(!writeRegisterByte(SFE_QMA6100P_PM, tempVal))
    return false;

  return true;
}

//////////////////////////////////////////////////
// getOperatingMode()
//
// Retrieves the current operating mode - stanby/active mode
//
int8_t QwDevQMA6100P::getOperatingMode()
{

  uint8_t tempVal;
  int retVal;

  if(!readRegisterRegion(SFE_QMA6100P_PM, &tempVal, 1))
    return false;

  sfe_qma6100p_pm_bitfield_t pm;
  pm.all = tempVal; // This is a long winded but definitive way of getting the operating mode bit

  return (pm.bits.mode_bit); // Return the operating mode bit
}

//////////////////////////////////////////////////
// setRange()
//
// Sets the operational g-range of the accelerometer.
//
// Parameter:
// range - sets the range of the accelerometer 2g - 32g depending
// on the version. 2g - 32g for the QMA6100P.
//
bool QwDevQMA6100P::setRange(uint8_t range)
{

  uint8_t tempVal;
  int retVal;

  if (range > SFE_QMA6100P_RANGE32G)
    return false;

  // Read - Modify - Write
  if(!readRegisterRegion(SFE_QMA6100P_PM, &tempVal, 1))
    return false;

  sfe_qma6100p_fsr_bitfield_t fsr;
  fsr.all = tempVal;
  fsr.bits.range =  range; // This is a long winded but definitive way of setting the range (g select)
  tempVal = fsr.all;

  if(!writeRegisterByte(SFE_QMA6100P_FSR, tempVal))
    return false;

  _range = range; // Update our local copy

  return true;
}

//////////////////////////////////////////////////
// enableDataEngine()
//
// Enables the data ready bit. and maps it to INT1
//
// Parameter:
// enable - enable/disables the data ready bit.
//
bool QwDevQMA6100P::enableDataEngine(bool enable)
{
  uint8_t tempVal;

  if(!readRegisterRegion(SFE_QMA6100P_PM, &tempVal, 1))
    return false;

  sfe_qma6100p_int_map1_bitfield_t int_map1;
  int_map1.all = tempVal;
  int_map1.bits.int1_data = enable; // data ready interrupt to INT1
  tempVal = int_map1.all;

  if(!writeRegisterByte(SFE_QMA6100P_INT_MAP1, tempVal))
    return false;

  // enable data ready interrupt
  if(!readRegisterRegion(SFE_QMA6100P_INT_EN1, &tempVal, 1))
    return false;

  sfe_qma6100p_int_en1_bitfield_t int_en1;
  int_en1.all = tempVal;
  int_en1.bits.int_data_en = enable; // set data ready interrupt
  tempVal = int_en1.all;

  if(!writeRegisterByte(SFE_QMA6100P_INT_EN1, tempVal))
    return false;

  return true;
}
//////////////////////////////////////////////////
// dataReady()
//
// Checks the data ready bit indicating new accelerometer data
// is ready in the X/Y/Z Out regsiters. This is cleared automatically
// on read of LSB and MSB
bool QwDevQMA6100P::dataReady()
{

  uint8_t tempRegData[6] = {0};

  if(!readRegisterRegion(SFE_QMA6100P_DX_L, tempRegData, 6));
    return false;

  bool ready = 0;
  ready |= tempRegData[0] & 0x01;
  ready |= tempRegData[2] & 0x01;
  ready |= tempRegData[4] & 0b01;

  return ready;
}

//////////////////////////////////////////////////
// getRawAccelRegisterData()
//
// Retrieves the raw register values representing accelerometer data.
//
// Note: this method does not check if the registers contain valid data.
// The user needs to do that externally by calling dataReady
// or using the INT pins to indicate that data is ready.
//
// Parameter:
// *rawAccelData - a pointer to the data struct that holds acceleromter X/Y/Z data.
//
bool QwDevQMA6100P::getRawAccelRegisterData(rawOutputData *rawAccelData)
{
  uint8_t tempRegData[6] = {0};

  if(!readRegisterRegion(SFE_QMA6100P_DX_L, tempRegData, 6)); // Read 3 * 16-bit
    return false;

  rawAccelData->xData = (tempRegData[0] >> 1) & 0b01111111;
  rawAccelData->xData |= (uint16_t)tempRegData[1] << 8;
  rawAccelData->yData = (tempRegData[2] >> 1) & 0b01111111;
  rawAccelData->yData |= (uint16_t)tempRegData[3] << 8;
  rawAccelData->zData = (tempRegData[4] >> 1) & 0b01111111 ;
  rawAccelData->zData |= (uint16_t)tempRegData[5] << 8;

  return true;
}

//////////////////////////////////////////////////////////////////////////////////
// readRegisterRegion()

bool QwDevQMA6100P::readRegisterRegion(uint8_t registerAddress, uint8_t* sensorData, int len)
{
  Wire.beginTransmission(QMA6100P_ADDRESS_HIGH);
  Wire.write(registerAddress); // Register address to read from
  uint8_t err = Wire.endTransmission(); // Send the request without stopping the transmission

  if (err > 0) {
    return false;
  }

  uint8_t bytesAvailable = Wire.requestFrom(static_cast<int>(QMA6100P_ADDRESS_HIGH), static_cast<int>(len), static_cast<int>(true)); // Request len byte of data

  delay(10);

  if (bytesAvailable >= 1) {
    *sensorData = Wire.read(); // Read the byte from the sensor and store it in the variable pointed to by sensorData
    return true; // Return 0 if the read operation was successful
  } else {
    return false;
  }
}


//////////////////////////////////////////////////////////////////////////////////
// writeRegisterRegion()

bool QwDevQMA6100P::writeRegisterByte(uint8_t registerAddress, uint8_t data)
{
  Wire.beginTransmission(QMA6100P_ADDRESS_HIGH);
  Wire.write(registerAddress); // Register address to write to
  Wire.write(data); // Data to write, dereferenced from the pointer
  uint8_t err = Wire.endTransmission(); // End the transmission

  if (err > 0) {
    return false; // Return false if there's a communication error
  }

  return true; // Return true if the write operation was successful
}


//***************************************** QMA6100P ******************************************************


bool QwDevQMA6100P::begin()
{
  if (getUniqueID() != QMA6100P_CHIP_ID)
    return false;

  return true;
}

//////////////////////////////////////////////////////////////////////////////////
// getAccelData()
//
// Retrieves the raw accelerometer data and calls a conversion function to convert the raw values.
//
// Parameter:
// *userData - a pointer to the user's data struct that will hold acceleromter data.
//
bool QwDevQMA6100P::getAccelData(outputData *userData)
{

  if(!getRawAccelRegisterData(&rawAccelData))
    return false;

  if(!convAccelData(userData, &rawAccelData))
    return false;

  return true;
}

//////////////////////////////////////////////////////////////////////////////////
// convAccelData()
//
// Converts raw acceleromter data with the current accelerometer's range settings.
//
// Parameter:
// *userData - a pointer to the user's data struct that will hold acceleromter data.
// *rawAccelData - a pointer to the data struct that holds acceleromter X/Y/Z data.
//
bool QwDevQMA6100P::convAccelData(outputData *userAccel, rawOutputData *rawAccelData)
{
  if (_range < 0) // If the G-range is unknown, read it
  {
    uint8_t regVal;
    int retVal;

    if(!readRegisterRegion(SFE_QMA6100P_FSR, &regVal, 1))
      return false;

    sfe_qma6100p_fsr_bitfield_t fsr;
    fsr.all = regVal;

    _range = fsr.bits.range; // Record the range
  }

  switch (_range)
  {
  case SFE_QMA6100P_RANGE2G:
    userAccel->xData = (float)rawAccelData->xData * convRange2G;
    userAccel->yData = (float)rawAccelData->yData * convRange2G;
    userAccel->zData = (float)rawAccelData->zData * convRange2G;
    break;
  case SFE_QMA6100P_RANGE4G:
    userAccel->xData = (float)rawAccelData->xData * convRange4G;
    userAccel->yData = (float)rawAccelData->yData * convRange4G;
    userAccel->zData = (float)rawAccelData->zData * convRange4G;
    break;
  case SFE_QMA6100P_RANGE8G:
    userAccel->xData = (float)rawAccelData->xData * convRange8G;
    userAccel->yData = (float)rawAccelData->yData * convRange8G;
    userAccel->zData = (float)rawAccelData->zData * convRange8G;
    break;
  case SFE_QMA6100P_RANGE16G:
    userAccel->xData = (float)rawAccelData->xData * convRange16G;
    userAccel->yData = (float)rawAccelData->yData * convRange16G;
    userAccel->zData = (float)rawAccelData->zData * convRange16G;
    break;
  case SFE_QMA6100P_RANGE32G:
    userAccel->xData = (float)rawAccelData->xData * convRange32G;
    userAccel->yData = (float)rawAccelData->yData * convRange32G;
    userAccel->zData = (float)rawAccelData->zData * convRange32G;
    break;
  default:
    return false;
  }

  return true;
}