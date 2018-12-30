#include "IMU.h"

/****************
public functions
****************/

IMU::IMU(int gyroAddr, int gyroScale, int accAddr, int accScale)
  :gyroDeviceAddress(gyroAddr), gyroscopeScale(gyroScale), accDeviceAddress(accAddr), accelerometerScale(accScale)
{
  updateTime(0); // initialize time to 0
}

float IMU::getAccPitch(){
  return accPitch;
}

float IMU::getAccRoll(){
  return accRoll;
}

float IMU::getAccYaw(){
  return accYaw;
}

float IMU::getGyroPitch(){
  return gyroPitch;
}

float IMU::getGyroRoll(){
  return gyroRoll;
}

float IMU::getGyroYaw(){
  return gyroYaw;
}

void IMU::updateIMU(){
  // update accelerometer vals
  updateAccelerometerAttitudeValues(true );
  // update gyro vals
  updateGyroscopeAttitudeValue();
}

void IMU::updateTime(float t){
  dt = t;
}

void IMU::configureICs(){
  int deviceAddress;
  int confRegisterAddresses[5];
  int confValues[4];
  int * confRegAddrPtr = confRegisterAddresses;
  int * confValPtr = confValues;

  Serial.println("Configuring IMU ICs");

  // configure LSM303C accelerometer
  // Set register addresses for device id and control registers
  deviceAddress = 0x1D;    // LSM303C device id
  confRegisterAddresses[0] = 0x20; // Ctrl register one
  confRegisterAddresses[1] = 0x21; // Ctrl register two
  confRegisterAddresses[2] = 0x22; // Ctrl register three
  confRegisterAddresses[3] = 0x23; // Ctrl register four
  confRegisterAddresses[4] = 0x24; // Ctrl register five
  // Set control registers values
  confValues[0] = 0b01000111; // Ctrl register one: Enable x, y, z and turn off power down:
  confValues[1] = 0b00000000; // Ctrl register two: High Pass Filter configuration
  confValues[2] = 0b00001000; // Ctrl register three: Interupts configuration
  if(accelerometerScale == 2){
    confValues[3] = 0b00000000; // Ctrl register four
  }else if(accelerometerScale == 4){
    confValues[3] = 0b00100000; // Ctrl register four
  }else{
    confValues[3] = 0b00110000; // Ctrl register four
  }
  confValues[4] = 0b00000000; // Ctrl register five: controls the self test among other things
  configureIC(deviceAddress,confRegAddrPtr,confValPtr);
  
  // configure L3GD20 gyroscope
  deviceAddress = 0x6B;
  // Configuration registers' addresses are as for the LSM303C above
  // Set control registers values
  confValues[0] = 0b00001111; // Ctrl register one: Enable x, y, z and turn off power down:
  confValues[1] = 0b00000000; // Ctrl register two: High Pass Filter configuration
  confValues[2] = 0b00001000; // Ctrl register three: Interupts configuration
  if(gyroscopeScale == 2){
    confValues[3] = 0b00000000; // Ctrl register four
  }else if(gyroscopeScale == 4){
    confValues[3] = 0b00100000; // Ctrl register four
  }else{
    confValues[3] = 0b00110000; // Ctrl register four
  }
  confValues[4] = 0b00000000; // Ctrl register five: controls the self test among other things
  configureIC(deviceAddress,confRegAddrPtr,confValPtr);
}

void IMU::calibrateICs(){
  // calibrate accelerometer
  calibrateAcc();
  // calibrate gyro
  calibrateGyro();
}

void IMU::debugg(){
  
}

/****************
private functions
****************/

// This function writes the specified values to the specified registers using I2C
void IMU::configureIC(int deviceAddr, int * confRegAddrPtr, int * confValPtr){
  for(size_t i = 0; i < sizeof(*confRegAddrPtr)/sizeof(confRegAddrPtr[0]); i++){
    writeRegister(deviceAddr, confRegAddrPtr[i], confValPtr[i]);
  }
}

void IMU::calibrateAcc(){
  Serial.println();
  Serial.print("Calibrating Accelerometer");
  for (int cal_int = 0; cal_int < 2000 ; cal_int++){                  
    if(cal_int % 125 == 0) Serial.print(".");
    updateAccelerometerAttitudeValues(false); // set calibrate to false                               
    accCalVals[0] += accPitch;
    accCalVals[1] += accRoll;
    accCalVals[2] += accYaw;
  }
  Serial.println();
  accCalVals[0] /= 2000;
  accCalVals[1] /= 2000;
  accCalVals[2] /= 2000;
}

void IMU::calibrateGyro(){
  Serial.print("Calibrating Gyro");

  for (int cal_int = 0; cal_int < 2000 ; cal_int++){                  
    if(cal_int % 125 == 0) Serial.print(".");   
    gyroCalVals[0] += getAttitudeValue(gyroDeviceAddress,0x29,0x28); // x values
    gyroCalVals[1] += getAttitudeValue(gyroDeviceAddress,0x2B,0x2A); // y values
    gyroCalVals[2] += getAttitudeValue(gyroDeviceAddress,0x2D,0x2C); // z values
    delay(3);                                                          
  }
  Serial.println();
  gyroCalVals[0] /= 2000;                                                  
  gyroCalVals[1] /= 2000;                                                  
  gyroCalVals[2] /= 2000;
}

// This function writes to a 1 byte register with I2C protocol 
void IMU::writeRegister(int deviceAddress, byte address, byte val) {
    Wire.beginTransmission(deviceAddress); // start transmission to device
    Wire.write(address);       // send register address
    Wire.write(val);         // send value to write
    Wire.endTransmission();     // end transmission
}

// This function reads a 1 byte register with I2C protocol and returns the value as an int
int IMU::readRegister(int deviceAddress, byte address){

    int v;
    Wire.beginTransmission(deviceAddress);
    Wire.write(address); // register to read
    Wire.endTransmission();
 
    Wire.requestFrom(deviceAddress, 1); // read a byte
 
    while(!Wire.available()) {
        // waiting
    }
    v = Wire.read();
    return v;
}

int IMU::getAttitudeValue(int deviceAddr, int MSBAddr, int LSBAddr){
  int val;
  byte xMSB = readRegister(deviceAddr, MSBAddr);
  byte xLSB = readRegister(deviceAddr, LSBAddr);
  val = ((xMSB << 8) | xLSB);
  return val;
}

void IMU::updateAccelerometerAttitudeValues(bool calibrate){
  float accVals [3];

  accVals[0] = getAttitudeValue(accDeviceAddress,0x29,0x28); // x values
  accVals[1] = getAttitudeValue(accDeviceAddress,0x2B,0x2A); // y values
  accVals[2] = getAttitudeValue(accDeviceAddress,0x2D,0x2C); // z values

  float sensitivity_factor;
  if(accelerometerScale == 2){
    sensitivity_factor = 0.061; // in mg/LSB from datasheet
  } else if(accelerometerScale == 4){
    sensitivity_factor = 0.122; // in mg/LSB from datasheet
  } else if(accelerometerScale == 8){
    sensitivity_factor = 0.244; // in mg/LSB from datasheet
  }

  accVals[0] = (accVals[0] * sensitivity_factor) / 1000;
  accVals[1] = (accVals[1] * sensitivity_factor) / 1000;
  accVals[2] = (accVals[2] * sensitivity_factor) / 1000;

  // Calculate angle in radians
  accPitch = atan(accVals[1]/accVals[2]);
  accRoll = -atan(accVals[0]/accVals[2]);
  accYaw = atan(accVals[1]/accVals[0]);

  // convert radians to degrees
  accPitch = accPitch * (180/PI);
  accRoll = accRoll * (180/PI) - 90;
  accYaw = accYaw * (180/PI);

  if(calibrate){
    accPitch -= accCalVals[0];
    accRoll -= accCalVals[1];
    accYaw -= accCalVals[2];
  }
}

void IMU::updateGyroscopeAttitudeValue(){
  int gyroVals [3];

  gyroVals[0] = getAttitudeValue(gyroDeviceAddress,0x29,0x28); // x values
  gyroVals[1] = getAttitudeValue(gyroDeviceAddress,0x2B,0x2A); // y values
  gyroVals[2] = getAttitudeValue(gyroDeviceAddress,0x2D,0x2C); // z values

  // apply calibration offset
  gyroVals[0] -= gyroCalVals[0];
  gyroVals[1] -= gyroCalVals[1];
  gyroVals[2] -= gyroCalVals[2];

  float sensitivity_factor;
  if(gyroscopeScale == 250){
    sensitivity_factor = 8.75; // in mdps/LSB from datasheet
  } else if(gyroscopeScale == 500){
    sensitivity_factor = 17.5; // in mdps/LSB from datasheet
  } else if(gyroscopeScale == 2000){
    sensitivity_factor = 70; // in mdps/LSB from datasheet
  }
    
    // Gyro values in deg/s
    gyroVals[0] = (gyroVals[0] * sensitivity_factor) / 1000;
    gyroVals[1] = (gyroVals[1] * sensitivity_factor) / 1000;
    gyroVals[2] = (gyroVals[2] * sensitivity_factor) / 1000;

  // Gyro dps to deg
  float angle_x_change = gyroVals[0] * dt;
  float angle_y_change = gyroVals[1] * dt;
  float angle_z_change = gyroVals[2] * dt;

  // Uptade old angular position
  gyroPitch = gyroPitch - angle_x_change;
  gyroRoll = gyroRoll + angle_y_change;
  gyroYaw = gyroYaw + angle_z_change;
}