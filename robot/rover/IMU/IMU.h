#include <Wire.h>
#include <Arduino.h>
#include "Sensor.h"

class IMU{
public:
	IMU();
	float getAccPitch();
	float getAccYaw();
	float getAccRoll();
	float getGyroPitch();
	float getGyroYaw();
	float getGyroRoll();
	void updateIMU();
	void updateTime(float);
	void configureICs();					// settings for inertial measurements chips (accelerometer, gyro, and magnetometer)
	void calibrateICs();					// calibrates sensors
	void debugg();							// For debgging purposes
	void setAccelerometer(Sensor *);		// Takes in a Sensor object
	void setGyroscope(Sensor *);
	void setMagnetometer(Sensor *);			// Takes in a Sensor object
private:
	float dt;								// change in time
	float accPitch;							// in degrees
	float accRoll;							// in degrees
	float accYaw;							// in degrees
	float gyroPitch;						// in degrees
	float gyroRoll;							// in degrees
	float gyroYaw;							// in degrees
	float gyroCalVals [3];					// Stores the calibration offset for the gyroscope
	float accCalVals [3];					// Stores the calibration offset for the accelerometer: pitch, roll, yaw respectively
	Sensor gyroscope;
	Sensor accelerometer;
	Sensor magnetometer;
	void configureIC(int, int *, int *);	// writes data to conf registers for one device over I2C
	void calibrateAcc();					// Calibrates the accelerometer
	void calibrateGyro();					// Calibrates the gyroscope
	void writeRegister(int, byte, byte);	// Writes bytes to a register using I2C and Wire.h
	int readRegister(int, byte);			// Reads bytes from a register using I2C and Wire.h
	int getAttitudeValue(int, int, int);	// Reads and returns the value from the specified register
	void updateAccelerometerAttitudeValues(bool);
	void updateGyroscopeAttitudeValue();
};