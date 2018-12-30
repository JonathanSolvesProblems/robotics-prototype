#include <Wire.h>
#include <Arduino.h>

class IMU{
public:
	IMU(int, int, int, int);
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
	int accelerometerScale;					// linear acceleration sensitivity in g
	int gyroscopeScale;						// Sensitivity in dps
	int gyroDeviceAddress;
	int accDeviceAddress;
	void configureIC(int, int *, int *);	// writes data to conf registers for one device over I2C
	void calibrateAcc();					// Calibrates the accelerometer
	void calibrateGyro();					// Calibrates the gyroscope
	void writeRegister(int, byte, byte);	// Writes bytes to a register using I2C and Wire.h
	int readRegister(int, byte);			// Reads bytes from a register using I2C and Wire.h
	int getAttitudeValue(int, int, int);	// Reads and returns the value from the specified register
	void updateAccelerometerAttitudeValues(bool);
	void updateGyroscopeAttitudeValue();
};