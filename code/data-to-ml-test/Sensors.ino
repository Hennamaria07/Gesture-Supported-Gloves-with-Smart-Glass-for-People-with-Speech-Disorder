#include "Wire.h"
const int MPU_ADDR = 0x68;

// from thumb
const int RingPin = 34;
const int MiddlePin = 35;
const int IndexPin = 32;
const int ThumbPin = 33;
const int PinkyPin = 39;

void ReadFlexSensors()
{
  ThumbReading = analogRead(ThumbPin);
  IndexReading = analogRead(IndexPin);
  MiddleReading = analogRead(MiddlePin);
  RingReading = analogRead(RingPin);
  PinkyReading = analogRead(PinkyPin);
  Serial.println();
  Serial.print("Thumb : ");
  Serial.print(ThumbReading);
  Serial.print(", Index : ");
  Serial.print(IndexReading);
  Serial.print(", Middle : ");
  Serial.print(MiddleReading);
  Serial.print(", Ring : ");
  Serial.print(RingReading);
  Serial.print(", Pinky : ");
  Serial.print(PinkyReading);
}


void ReadAcceleroMeter()
{
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B);                        // starting with register 0x3B (ACCEL_XOUT_H) [MPU-6000 and MPU-6050 Register Map and Descriptions Revision 4.2, p.40]
  Wire.endTransmission(false);             // the parameter indicates that the Arduino will send a restart. As a result, the connection is kept active.
  Wire.requestFrom(MPU_ADDR, 7 * 2, true); // request a total of 7*2=14 registers

  accelerometer_x = Wire.read() << 8 | Wire.read(); // reading registers: 0x3B (ACCEL_XOUT_H) and 0x3C (ACCEL_XOUT_L)
  accelerometer_y = Wire.read() << 8 | Wire.read(); // reading registers: 0x3D (ACCEL_YOUT_H) and 0x3E (ACCEL_YOUT_L)
  accelerometer_z = Wire.read() << 8 | Wire.read(); // reading registers: 0x3F (ACCEL_ZOUT_H) and 0x40 (ACCEL_ZOUT_L)

  // print out data
  // Serial.print("aX = ");
  // Serial.print(accelerometer_x);
  // Serial.print(" | aY = ");
  // Serial.print(accelerometer_y);
  // Serial.println();
}


void InitializeAccleroMeter () 
{
  // Initialize I2C START
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR); // Begins a transmission to the I2C slave (GY-521 board)
  Wire.write(0x6B);                 // PWR_MGMT_1 register
  Wire.write(0);                    // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  // Initialize I2C END
}