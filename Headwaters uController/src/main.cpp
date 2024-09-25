#include <Arduino.h>
#include <FastLED.h>
#include <Bounce2.h>
#include <printFunctions.h>
#include <Timer.h>

//uint16_t btnLockTime = 250; 

// setup print to hardware serial
// RX0 TX1
Adafruit_Thermal printer(&Serial2);

#define BTN_PIN1 0
Bounce2::Button button1 = Bounce2::Button();
//MoToTimer buttonLockoutTimer;

#define NUM_LEDS 14
#define LED_PIN1 15

// define the array of LEDs
CRGB ledStrip[NUM_LEDS];
int location = 0;
int stream = 0;
float isoCount = 0.0;
float temperature = 0.0;
float dissolvedOxy = 0.0;

void setup() {
  FastLED.addLeds<NEOPIXEL, LED_PIN1>(ledStrip, NUM_LEDS);

  FastLED.setBrightness(255);
  FastLED.show();

  button1.attach(BTN_PIN1, INPUT_PULLUP);
  // debounce interval in milliseconds
  button1.interval(5);
  // indicate that the low state corresponds to phsyically pressing the button
  button1.setPressedState(LOW); 

  Serial.begin(115200);
  Serial2.begin(9600);

  printer.begin();
  //ONLY USED FOR DEBUGGING OR TALKING TO A COMPUTER
  //DELETE BEFORE FINAL
  while(!Serial);
}

void loop() {
  //printer.printBitmap(tubeWidth, tubeHeight, testTube);
  button1.update();

  if(button1.pressed()){
    location = 1;
    stream = 1;
    // create a blue "stream" on the LED strip 
    for(int i = 0; i < NUM_LEDS + 1; i++){
      fill_solid(ledStrip, i, CRGB::Blue);
      FastLED.show();
      delay(100);
    }

    for(int i = 0; i < NUM_LEDS + 1; i++){
      fill_solid(ledStrip, i, CRGB::Black);
      FastLED.show();
      delay(80);
    }

    printCurrentSample(printer, location, stream, 20.7, 72, 7);
    printQR(printer);
    printer.feed(3);
  }
}