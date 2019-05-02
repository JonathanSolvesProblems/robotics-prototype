#include <SparkFun_I2C_GPS_Arduino_Library.h>
I2CGPS myI2CGPS;  // I2C object

#include <TinyGPS++.h>
TinyGPSPlus gps;   // GPS object

#include <Wire.h>
#include <LSM303.h>

LSM303 compass;

void setup() {
  
  Serial.begin(115200);
  
  if (myI2CGPS.begin(Wire , 400000) == false)        // Wire1 corresponds to the SDA1,SCL1 on the Teensy 3.6 (pins 38,37)
  {
    while(1);                     // This will freeze the code to have the user check wiring
  }
  compass.init();
  compass.enableDefault();
  compass.m_min = (LSM303::vector<int16_t>){-9506, -6666, -8003};
  compass.m_max = (LSM303::vector<int16_t>){+5933, +7826, +6528};
}

void loop() {
  compass.read();
  float heading = compass.heading();
  
  while (myI2CGPS.available())          // returns the number of available bytes from the GPS module
  {
    gps.encode(myI2CGPS.read());       // Feeds the GPS parser
  }

  if (gps.time.isUpdated())         // Checks to see if new GPS info is available
  {
    displayInfo();                  // Print the info on the serial monitor
  }
  Serial.print("Heading");
  Serial.print(" ");
  Serial.print(heading);
  Serial.print("\n");
  delay(2000);                      // Delay figure to let the Python code handle the data, can be adjusted if needed
}

void displayInfo()                 // The function that prints the info
{
  if (gps.location.isValid())      // checks if valid location data is available 
  {
    Serial.print("GPS-OK");          // string initials to allow the Pyhton code to pickup
    Serial.print(" ");            // space
    Serial.print(gps.location.lat(), 6);   // print the latitude with 6 digits after the point
    Serial.print(" ");           // space
    Serial.print(gps.location.lng(), 6);   // print the longitude with 6 digits after the point
    Serial.print("--");             // new line
  }
  else
  {
    Serial.print(F("GPS-N/A"));
    Serial.print("--");
  }
  
}
