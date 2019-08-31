#include "IMU.h"
#include "Sensor.h"
#include <Wire.h>
#include <vector> // Sensor Class uses vector

// Declare IMU and initialize IMU object
#define L3GD20_Address 0x6B //I2C address of the L3GD20 gyro
#define LSM303C_Address 0x1D //I2C address of the LSM303C accelerometer

// Create Sensor objects for IMU sensor devices
Sensor myAcc(0x1D,"LSM303C_accelerometer",0.061); // initialize device address, name, and sensitivity factor
Sensor myGyro(0x6B,"L3GD20_gyroscope",8.75); // initialize device address, name, and sensitivity factor
// Sensor myMagnetometer(); 

// Set up accelerometer
std::vector<int> accConfRegs = {
  0x20,0b01000111, // conf reg 1
  0x21,0b00000000, // conf reg 2
  0x22,0b00001000, // conf reg 3
  0x23,0b00000000, // conf reg 4
  0x24,0b00000000  // conf reg 5
};
std::std::vector<int> accDataRegs = {
  0x29,0x28, // x-axis MSB,LSB
  0x2B,0x2A, // y-axis MSB,LSB
  0x2D,0x2C  // z-axis MSB,LSB
};

// Set up gyroscope
std::vector<int> gyroConfRegs = {
  0x20,0b00001111, // conf reg 1
  0x21,0b00000000, // conf reg 2
  0x22,0b00001000, // conf reg 3
  0x23,0b00000000, // conf reg 4
  0x24,0b00000000  // conf reg 5
};
std::std::vector<int> gyroDataRegs = {
  0x29,0x28, // x-axis MSB,LSB
  0x2B,0x2A, // y-axis MSB,LSB
  0x2D,0x2C  // z-axis MSB,LSB
};

// Initialize sensors' registers
myAcc.setConfigurationRegisters(&accConfRegs);
myAcc.setDataRegisters(&accDataRegs);
myGyro.setConfigurationRegisters(&gyroConfRegs);
myGyro.setDataRegisters(&gyroDataRegs);

// Instantiate IMU object
IMU myIMU();

// set IMU devices
myIMU.setAccelerometer(myAcc);
myIMU.setGyroscope(myGyro);

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