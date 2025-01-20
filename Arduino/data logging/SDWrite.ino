#include "SD.h"
#include <Wire.h>


#include "RTClib.h"        // define the Real Time Clock object
const int chipSelect = 10; // for the data logging shield, we use digital pin 10 for the SD cs line

void setup(){
  Serial.begin(9600);
  Serial.println("Set up mode");

  /**** SD card initialisation check ****/
  Serial.print("Initializing SD card...");
  // make sure that the default chip select pin is set to output, even if you don't use it:
  pinMode(10, OUTPUT);
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");
  
  /**** create a new file on to SD card ****/
  char filename[] = "LOGGER00.CSV";
  for (uint8_t i = 0; i < 100; i++) {
    filename[6] = i/10 + '0';
    filename[7] = i%10 + '0';
    if (! SD.exists(filename)) {
      // only open a new file if it doesn't exist
      logfile = SD.open(filename, FILE_WRITE); 
      break;  // leave the loop!
    }
  }
  if (! logfile) {
    error("couldnt create file");
  }
  Serial.print("Logging to: ");
  Serial.println(filename);

  /**** Writing onto SD card ****/
  wire.begin();
  logfile.pritln(" Writen on to SD card ");
  Serial.println(" Written on to SD card")

}



void loop(){
  
}









