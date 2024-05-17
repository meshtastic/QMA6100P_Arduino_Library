/*
  example6-tap

  This example shows the how to enable the tap interrupts.

  Written by Elias Santistevan @ SparkFun Electronics, October 2022

  Products:

  SparkFun Triple Axis Accelerometer Breakout - QMA6100P:
    https://www.sparkfun.com/products/17871

  SparkFun Triple Axis Accelerometer Breakout - QMA6100P:
    https://www.sparkfun.com/products/17589


  Repository:

    https://github.com/sparkfun/ QMA6100P_Arduino_Library

  SparkFun code, firmware, and software is released under the MIT
  License	(http://opensource.org/licenses/MIT).
*/

#include <Wire.h>
#include < QMA6100P.h> // Click here to get the library: http://librarymanager/All# QMA6100P

SparkFun_QMA6100P kxAccel;
// SparkFun_QMA6100P kxAccel; // For the QMA6100P, uncomment this and comment line above

byte direction = 0;

void setup()
{

  Wire.begin();

  Serial.begin(115200);
  Serial.println("Welcome.");

  // Wait for the Serial monitor to be opened.
  while (!Serial)
    delay(50);

  if (!kxAccel.begin())
  {
    Serial.println("Could not communicate with the the QMA6100P. Freezing.");
    while (1)
      ;
  }

  Serial.println("Ready.");

  // Reset the chip so that old settings don't apply to new setups.
  if (kxAccel.softwareReset())
    Serial.println("Reset.");

  // Give some time for the accelerometer to reset.
  // It needs two, but give it five for good measure.
  delay(5);

  // Many settings for QMA6100P can only be
  // applied when the accelerometer is powered down.
  // However there are many that can be changed "on-the-fly"
  // check datasheet for more info, or the comments in the
  // "...regs.h" file which specify which can be changed when.
  kxAccel.enableAccel(false);

  kxAccel.setRange(SFE_QMA6100P_RANGE16G); // 16g Range
  // kxAccel.setRange(SFE_QMA6100P_RANGE16G);         // 16g for the QMA6100P

  kxAccel.enableTapEngine();        //  Enable tap Engine
  kxAccel.enableDirecTapInterupt(); //  This enables checking the direction of the interrupt
  // kxAccel.setTapDataRate(uint8_t rate); //  Default is 400Hz
  kxAccel.enableAccel();
}

void loop()
{
  // Check if tap was detected
  if (kxAccel.tapDetected())
  {
    Serial.print("Tap Detected: ");
    Serial.println(kxAccel.getDirection(), HEX);
    kxAccel.clearInterrupt();
  }

  if (kxAccel.unknownTap() || kxAccel.doubleTapDetected()) // These all share the same bit space
    kxAccel.clearInterrupt();

  delay(2.5); // Delay should be 1/ODR (Output Data Rate), default tap ODR is 400Hz
}
