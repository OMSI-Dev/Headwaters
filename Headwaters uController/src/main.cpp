#include <Arduino.h>
//#include <FastLED.h>
#include <Bounce2.h>
#include <printFunctions.h>
#include <haxx.h>

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
uint8_t climateCondition = 0;

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

  // TRYING THE RING LED
  //circleLED.centerFill(255, 0, 0);
    // for(int i = 0; i < NUM_LEDS_RING + 1; i++){
    //   fill_solid(ledRing, i, CRGB::Blue);
    //   FastLED.show();
    //   delay(250);
    // }

  // for(int i = 0; i < NUM_LEDS_RING + 1; i++){
  //   fill_solid(ledRing, i, CRGB::Blue);
  //   FastLED.show();
  //   delay(80);
  // }

  // for(int i = 0; i < NUM_LEDS_RING + 1; i++){
  //   fill_solid(ledRing, i, CRGB::Black);
  //   FastLED.show();
  //   delay(80);
  // }

  // for(int i = 0; i < NUM_LEDS_STRIP + 1; i++){
  //   fill_solid(ledStrip, i, CRGB::Green);
  //   FastLED.show();
  //   delay(80);
  // }

  // for(int i = 0; i < NUM_LEDS_STRIP + 1; i++){
  //   fill_solid(ledStrip, i, CRGB::Black);
  //   FastLED.show();
  //   delay(80);
  // }

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
        //normalConditions(printer, stream, river);
        //printQR(printer);
        break;
      case 1:
        Serial.println("Climate Conditions: High Snowpack");
        //snowConditions(printer, stream, river);
        //printerQR(printer);
        break;
      case 2:
        Serial.println("Climate Conditions: Dought");
        //droughtConditions(printer, stream, river);
        //printQR(printer);
        break;
    }
  }

  // // DEMO MODE
  // if(button1.pressed()){
  //   switch(mode){
  //     case 0:
  //       stream = 2;
  //       river = 'X';
  //       for(int i = 0; i < NUM_LEDS_STRIP + 1; i++){
  //         fill_solid(ledStrip, i, CRGB::Green);
  //         FastLED.show();
  //         delay(80);
  //       }

  //       for(int i = 0; i < NUM_LEDS_STRIP + 1; i++){
  //         fill_solid(ledStrip, i, CRGB::Black);
  //         FastLED.show();
  //         delay(80);
  //       }

  //       normalConditions(printer, stream, river);
  //       printer.feed(4);
  //       break;

  //     case 1:
  //       stream = 0;
  //       river = 'A';
  //       for(int i = 0; i < NUM_LEDS_STRIP + 1; i++){
  //         fill_solid(ledStrip, i, CRGB::Blue);
  //         FastLED.show();
  //         delay(80);
  //       }

  //       for(int i = 0; i < NUM_LEDS_STRIP + 1; i++){
  //         fill_solid(ledStrip, i, CRGB::Black);
  //         FastLED.show();
  //         delay(80);
  //       }

  //       snowConditions(printer, stream, river);
  //       printer.feed(4);
  //       break;
      
  //     case 2:
  //       stream = 3;
  //       river = 'X';
  //       for(int i = 0; i < NUM_LEDS_STRIP + 1; i++){
  //         fill_solid(ledStrip, i, CRGB::Red);
  //         FastLED.show();
  //         delay(80);
  //       }

  //       for(int i = 0; i < NUM_LEDS_STRIP + 1; i++){
  //         fill_solid(ledStrip, i, CRGB::Black);
  //         FastLED.show();
  //         delay(80);
  //       }

  //       droughtConditions(printer, stream, river);
  //       printer.feed(4);
  //       break;
  //   }
  //   mode++;
  // }
    // if(mode == 3){
    //   printQR(printer);
    //   mode++;
    // }

  //   // REGULAR CODE 
  //   stream = 1;
  //   river = 'X';

  //   // create a blue "stream" on the LED strip 
  //   for(int i = 0; i < NUM_LEDS_STRIP + 1; i++){
  //     fill_solid(ledStrip, i, CRGB::Blue);
  //     FastLED.show();
  //     delay(80);
  //   }

  //   for(int i = 0; i < NUM_LEDS_STRIP + 1; i++){
  //     fill_solid(ledStrip, i, CRGB::Black);
  //     FastLED.show();
  //     delay(80);
  //   }

      // switch(climateCondition){
      //   case 0:
      //     normalConditions(printer, stream, river);
      //     printQR(printer);
      //     break;
      //   case 1:
      //     snowConditions(printer, stream, river);
      //     printQR(printer);
      //     break;
      //   case 2:
      //     droughtConditions(printer, stream, river);
      //     printQR(printer);
      //     break;
      // }
}