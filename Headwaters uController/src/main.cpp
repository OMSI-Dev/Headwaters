#include <Arduino.h>
#include <FastLED.h>
#include <Timer.h>
#include <Adafruit_Thermal.h>
#include <testTube.h>


//setup print to hardware serial
//RX0 TX1
Adafruit_Thermal printer(&Serial);

void setup() {

}

void loop() {
  // Print the 75x75 pixel logo in adalogo.h:
  printer.printBitmap(tubeWidth, tubeHeight, testTube);

}
