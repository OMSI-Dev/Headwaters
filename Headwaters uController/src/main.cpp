#include <Arduino.h>
#include <FastLED.h>
#include <Timer.h>
#include <Adafruit_Thermal.h>
#include <testTube.h>
#include <Bounce2.h>

MoToTimer buttonLockoutTimer;

uint16_t btnLockTime = 250; 

//setup print to hardware serial
//RX0 TX1
Adafruit_Thermal printer(&Serial);

void setup() {

}

void loop() {

  printer.printBitmap(tubeWidth, tubeHeight, testTube);
  if(testbutton.ispressed() && testAllow)
  {
    //print!
  }
  printer.availableForWrite();

}
