#include "IMU.h"
#include <Wire.h>

// Declare IMU and initialize IMU object
#define L3GD20_Address 0x6B //I2C address of the L3GD20 gyro
#define LSM303C_Address 0x1D //I2C address of the LSM303C accelerometer
#define accelerometerScale 2
#define gyroscopeScale 250
IMU myIMU(L3GD20_Address,gyroscopeScale,LSM303C_Address,accelerometerScale);

float pitch, roll, yaw;
float dt = 0;
unsigned long start, finished, elapsed;

void setup(){
  Wire.begin();
    Serial.begin(9600);

    myIMU.configureICs();
    myIMU.calibrateICs();

  delay(100); //wait for the sensor to be ready
}

void loop(){
  start = millis(); // Time elapsed since program started

  myIMU.updateIMU();

  pitch = myIMU.getAccPitch();
  roll = myIMU.getAccRoll();
  yaw = myIMU.getGyroYaw();

  // display in serial plotter
  // Serial.print(pitch);
  // Serial.print(",");
  // Serial.print(roll);
  // Serial.print(",");
  // Serial.print(yaw);
  // Serial.println();

  // display in processing sketch
  Serial.print("P");
  Serial.print(pitch);
  Serial.print("R");
  Serial.print(roll);
  Serial.print("Y");
  Serial.print(yaw);
  Serial.println();

  // Calculate ellapsed time
  finished = millis(); // Time since program started
  elapsed = finished - start; // Time since void loop() started in msec
  dt = elapsed / 1000.0; // Convert to sec

  myIMU.updateTime(dt);

  // Reset start and elapsed
  start = elapsed = 0;
}