/*example1-BasicReadings*/
#include <Wire.h>
#include <QMA6100P.h> // Click here to get the library: http://librarymanager/All# QMA6100P

QMA6100P qmaAccel;

outputData myData; // Struct for the accelerometer's data

void setup()
{

  Wire.begin();

  Serial.begin(115200);
  Serial.println("Welcome.");

  // Wait for the Serial monitor to be opened.
  while (!Serial)
    delay(50);

  if (!qmaAccel.begin())
  {
    Serial.println("Could not communicate with the the QMA6100P. Freezing.");
    while (1)
      ;
  }

  Serial.println("Ready.");

  if (qmaAccel.softwareReset())
    Serial.println("Reset.");

  // Give some time for the accelerometer to reset.
  // It needs two, but give it five for good measure.
  delay(5);

  // Many settings for QMA6100P can only be
  // applied when the accelerometer is powered down.
  // However there are many that can be changed "on-the-fly"
  // check datasheet for more info, or the comments in the
  // "...regs.h" file which specify which can be changed when.
  qmaAccel.enableAccel(false);

  qmaAccel.setRange(SFE_QMA6100P_RANGE32G);         // 32g for the QMA6100P

  qmaAccel.enableDataEngine(); // Enables the bit that indicates data is ready.
  // qmaAccel.setOutputDataRate(); // Default is 50Hz
  qmaAccel.enableAccel();
}

void loop()
{
  // Check if data is ready.
  if (qmaAccel.dataReady())
  {
    qmaAccel.getAccelData(&myData);
    Serial.print("X: ");
    Serial.print(myData.xData, 4);
    Serial.print(" Y: ");
    Serial.print(myData.yData, 4);
    Serial.print(" Z: ");
    Serial.print(myData.zData, 4);
    Serial.println();
  }
  delay(20); // Delay should be 1/ODR (Output Data Rate), default is 1/50ODR
}
