#include <Arduino.h>
#include <Bounce2.h>
#include <printFunctions.h>
#include <ledModes.h>
#include <haxx.h>
#include <ledStreams.h>

//uint16_t btnLockTime = 250; 

// setup print to hardware serial
// RX0 TX1
Adafruit_Thermal printer(&Serial2);


#define BTN_PIN1 0
Bounce2::Button button1 = Bounce2::Button();

// TRYING HAXX LIBRARY CIRCLE LED
haxx circleLED;

//MoToTimer buttonLockoutTimer;

#define NUM_LEDS_STRIP 14
#define NUM_LEDS_RING 31
#define LED_PIN1 15
#define LED_PIN2 16

// define the array of LEDs
CRGB ledStrip[NUM_LEDS_STRIP];
CRGB ledRing[NUM_LEDS_RING];
uint8_t stream = 0;
char river = 'X';

// climate condition settings
// 0 = normal
// 1 = high snowpack
// 2 = drought
uint8_t climateCondition = -1;

void setup() {
  FastLED.addLeds<NEOPIXEL, LED_PIN1>(ledStrip, NUM_LEDS_STRIP);
  FastLED.addLeds<NEOPIXEL, LED_PIN2>(ledRing, NUM_LEDS_RING);

  FastLED.setBrightness(255);
  FastLED.show();

  // TRYING CIRCLE LED HAXX LIBRARY
  circleLED.attach(16);

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
  button1.update();
  if(climateCondition == 0){
    pacifica_loop(ledRing);
    FastLED.show();
  }
  
  // button pressed to change the climate condition
  // should be first thing checked every loop?
  if(button1.pressed()){
    if(climateCondition == 2){
      climateCondition = 0;
    } else if(climateCondition != 2) {
      climateCondition++;
    }

    switch(climateCondition){
      case 0:
        Serial.println("Climate Condition: Normal");
        pacifica_loop(ledRing);
        FastLED.show();
        //normalConditions(printer, stream, river);
        //printQR(printer);
        break;
      case 1:
        Serial.println("Climate Conditions: High Snowpack");
        fill_solid(ledRing, NUM_LEDS_RING + 1, CRGB::Black);
        snowpack(ledRing);
        FastLED.show();
        //snowConditions(printer, stream, river);
        //printerQR(printer);
        break;
      case 2:
        Serial.println("Climate Conditions: Dought");
        fill_solid(ledRing, NUM_LEDS_RING + 1, CRGB::Black);
        drought(ledRing);
        FastLED.show(); // display this frame
        //droughtConditions(printer, stream, river);
        //printQR(printer);
        break;
    }
  }

  //blue_stream(ledStrip, NUM_LEDS_STRIP);
}

void demo(){
   // DEMO from video
   // will have to put back into main loop
   // before using I think
  uint8_t mode = 0;
  if(button1.pressed()){
    switch(mode){
      case 0:
        stream = 2;
        river = 'X';
        for(int i = 0; i < NUM_LEDS_STRIP + 1; i++){
          fill_solid(ledStrip, i, CRGB::Green);
          FastLED.show();
          delay(80);
        }

        for(int i = 0; i < NUM_LEDS_STRIP + 1; i++){
          fill_solid(ledStrip, i, CRGB::Black);
          FastLED.show();
          delay(80);
        }

        normalConditions(printer, stream, river);
        printer.feed(4);
        break;

      case 1:
        stream = 0;
        river = 'A';
        for(int i = 0; i < NUM_LEDS_STRIP + 1; i++){
          fill_solid(ledStrip, i, CRGB::Blue);
          FastLED.show();
          delay(80);
        }

        for(int i = 0; i < NUM_LEDS_STRIP + 1; i++){
          fill_solid(ledStrip, i, CRGB::Black);
          FastLED.show();
          delay(80);
        }

        snowConditions(printer, stream, river);
        printer.feed(4);
        break;
      
      case 2:
        stream = 3;
        river = 'X';
        for(int i = 0; i < NUM_LEDS_STRIP + 1; i++){
          fill_solid(ledStrip, i, CRGB::Red);
          FastLED.show();
          delay(80);
        }

        for(int i = 0; i < NUM_LEDS_STRIP + 1; i++){
          fill_solid(ledStrip, i, CRGB::Black);
          FastLED.show();
          delay(80);
        }

        droughtConditions(printer, stream, river);
        printer.feed(4);
        break;
    }
    mode++;
  }
    if(mode == 3){
      printQR(printer);
      mode++;
    }

}