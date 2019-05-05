#include <SparkFun_I2C_GPS_Arduino_Library.h>
I2CGPS myI2CGPS;  // I2C object

#include <TinyGPS++.h>
TinyGPSPlus gps;   // GPS object

#include <Wire.h>
#include <LSM303.h>

// quickly switch to uart for walid. for fauzi, 
//#define USE_UART 1
#ifdef USE_UART
#define UART_PORT Serial4
#else
#define UART_PORT Serial
#endif

LSM303 compass;

void setup() {
  
  UART_PORT.begin(115200);
  
  if (myI2CGPS.begin(Wire2 , 400000) == false)        // Wire1 corresponds to the SDA1,SCL1 on the Teensy 3.6 (pins 38,37)
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
  UART_PORT.print("Heading");
  UART_PORT.print(" ");
  UART_PORT.print(heading);
  UART_PORT.print("\n");
  delay(500);                      // Delay figure to let the Python code handle the data, can be adjusted if needed
}

void displayInfo()                 // The function that prints the info
{
  if (gps.location.isValid())      // checks if valid location data is available 
  {
    UART_PORT.print("GPS-OK");          // string initials to allow the Pyhton code to pickup
    UART_PORT.print(" ");            // space
    UART_PORT.print(gps.location.lat(), 6);   // print the latitude with 6 digits after the point
    UART_PORT.print(" ");           // space
    UART_PORT.print(gps.location.lng(), 6);   // print the longitude with 6 digits after the point
    UART_PORT.print("--");             // new line
  }
  else
  {
    UART_PORT.print(F("GPS-N/A"));
    UART_PORT.print("--");
  }
  
}
