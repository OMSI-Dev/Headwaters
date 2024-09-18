#include <Arduino.h>
#include <FastLED.h>
#include <Timer.h>
#include <Adafruit_Thermal.h>
#include <testTube.h>
#include <Bounce2.h>
#include <OMSI_QR.h>

MoToTimer buttonLockoutTimer;
Bounce2::Button test_button = Bounce2::Button();

uint16_t btnLockTime = 250; 

//setup print to hardware serial
//RX0 TX1
Adafruit_Thermal printer(&Serial);

// change to number of LED in the strip
#define NUM_LEDS 1
// change to proper pin number
#define DATA_PIN 3
// Define the array of leds
CRGB leds[NUM_LEDS];

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
}

void loop() {
  printer.printBitmap(tubeWidth, tubeHeight, testTube);

  // initial LED is ? or only blue when button is pushed? 
  // led[#] CRGB:: ? ;
  // FastLED.show();

  if(test_button.pressed() && printer.availableForWrite())
  {
    // LED stream
    //led[#] = CRGB::Blue;
    //FastLED.show();
    // print O^#, isotopes and QR code pointing to OMSI website
    printer.boldOn();
    printer.println("O numbers: #");
    printer.boldOff();

    printer.boldOn();
    printer.println("Isotope count: ");
    printer.boldOff();

    printer.printBitmap(QRWidth, QRHeight, OMSI_QR);
  }

}
