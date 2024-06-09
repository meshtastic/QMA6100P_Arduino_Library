/*example1-BasicReadings*/
#include <Wire.h>
#include <Qwiic_QMA6100P.h> // Click here to get the library: http://librarymanager/All# QMA6100P

#define USB_TX_PIN PA12 // D- pin
#define USB_RX_PIN PA11 // D+ pin
#define I2C_SDA_PIN PB11
#define I2C_SCL_PIN PB10
#define ACCEL_INT1 PB5
#define ACCEL_INT2 PB6
#define DB_LED_PIN PA15

bool buffer_enable = false;

QwDevQMA6100P qmaAccel;

outputData myData; // Struct for the accelerometer's data

#include <SoftwareSerial.h>

SoftwareSerial softSerial(USB_RX_PIN, USB_TX_PIN);

void setup()
{
  softSerial.begin(38400);

  // put your setup code here, to run once:
  pinMode(DB_LED_PIN, OUTPUT);

  // Configure I2C
  Wire.setSDA(I2C_SDA_PIN);
  Wire.setSCL(I2C_SCL_PIN);
  Wire.begin();

  if (!qmaAccel.begin())
  {
    softSerial.println("ERROR: Could not communicate with the the QMA6100P. Freezing.");
    while (1)
      ;
  }

  softSerial.println("Ready.");

  if (!qmaAccel.softwareReset())
    softSerial.println("ERROR: Failed to reset");

  // Give some time for the accelerometer to reset.
  // It needs two, but give it five for good measure.
  delay(5);

  if(!qmaAccel.setRange(SFE_QMA6100P_RANGE32G))        // 32g for the QMA6100P
    softSerial.println("ERROR: failed to set range");

  if(!qmaAccel.enableDataEngine(false)) // Enables the bit that indicates data is ready.
    softSerial.println("ERROR: failed to map and set data ready interrupt");

  if(!qmaAccel.enableAccel())
    softSerial.println("ERROR: failed to set active mode");
}

void loop()
{
  // Check if data is ready.
  if (qmaAccel.dataReady())
  {
    qmaAccel.getAccelData(&myData, buffer_enable);
    softSerial.print("X: ");
    softSerial.print(myData.xData, 4);
    softSerial.print(" Y: ");
    softSerial.print(myData.yData, 4);
    softSerial.print(" Z: ");
    softSerial.print(myData.zData, 4);
    softSerial.println();
  }
  delay(20); // Delay should be 1/ODR (Output Data Rate), default is 1/50ODR
}
