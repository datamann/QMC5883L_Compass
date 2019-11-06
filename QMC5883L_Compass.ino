/*
 * Modified by Stig B. Sivertsen
 * Based on QMC5883L library example and Ghettostation Antenna Tracker requirements
 * sbsivertsen@gmail.com
 * 02.11.2019
 * @see The GNU Public License (GPL) Version 3
*/
#include <Wire.h>
#include <QMC5883L.h>
QMC5883L compass;
#define MAGDEC +3,18,'N'
float declinationAngle = 0;
void setup() {
  Wire.begin();
  compass.init();
  declinationAngle = compass.SetDeclination(MAGDEC); // Magnetic Declination, find yours here: http://www.magnetic-declination.com/
  Serial.begin(9600);
}

void loop() {
  retrieve_mag();
}

void retrieve_mag() {
  int16_t home_bearing = 0;
  float heading = compass.readHeading();
  
  Serial.print(F("Heading: "));
  Serial.println(heading);

  //Serial.print(F("Declination angle: "));
  //Serial.println(declinationAngle);
  
  heading += declinationAngle;
  if (heading < 0)    heading += 2*PI;
  if (heading > 2*PI) heading -= 2*PI;
  home_bearing = (int)round(heading * 180/M_PI);
  
  //Serial.print(F("Home bearing: "));
  //Serial.println(home_bearing);
}
