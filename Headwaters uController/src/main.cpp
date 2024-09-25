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
uint8_t stream = 0;
char river = 'X';

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
    stream = 1;
    river = 'X';

    // create a blue "stream" on the LED strip 
    for(int i = 0; i < NUM_LEDS + 1; i++){
      fill_solid(ledStrip, i, CRGB::Blue);
      FastLED.show();
      delay(80);
    }

    for(int i = 0; i < NUM_LEDS + 1; i++){
      fill_solid(ledStrip, i, CRGB::Black);
      FastLED.show();
      delay(80);
    }

    //normalConditions(printer, stream, river);
    //snowConditions(printer, stream, river);
    droughtConditions(printer, 0, 'B');
    //printQR(printer);
  }
}