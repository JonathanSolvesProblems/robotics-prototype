#include <SparkFun_I2C_GPS_Arduino_Library.h>
I2CGPS myI2CGPS;

#include <TinyGPS++.h>
TinyGPSPlus gps;







void setup() {
  
  Serial.begin(115200);

  if (myI2CGPS.begin(Wire1 , 400000) == false)
  {
    while(1);
  }
}

void loop() {
  
  while (myI2CGPS.available()) 
  {
    gps.encode(myI2CGPS.read()); 
  }

  if (gps.time.isUpdated())
  {
    displayInfo();
  }

  delay(5000);
}

void displayInfo()
{
  if (gps.location.isValid())
  {
    Serial.println();
    Serial.print(gps.location.lat(), 6);
    Serial.print(" ");
    Serial.print(gps.location.lng(), 6);
  }
  else
  {
    Serial.println(F("N/A"));
  }
}
