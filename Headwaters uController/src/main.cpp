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


#define MODE_PIN 0
#define STREAM1_PIN 1
#define STREAM2_PIN 2
#define STREAM3_PIN 3
#define RIVER1_PIN 4
#define RIVER2_PIN 5
#define RIVER3_PIN 6
Bounce2::Button modeButton = Bounce2::Button();
Bounce2::Button stream1Button = Bounce2::Button();
Bounce2::Button stream2Button = Bounce2::Button();
Bounce2::Button stream3Button = Bounce2::Button();
Bounce2::Button river1Button = Bounce2::Button();
Bounce2::Button river2Button = Bounce2::Button();
Bounce2::Button river3Button = Bounce2::Button();

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

// climate condition settings
// 0 = normal
// 1 = high snowpack
// 2 = drought
uint8_t climateCondition = 2;

void setup() {
  FastLED.addLeds<NEOPIXEL, LED_PIN1>(ledStrip, NUM_LEDS_STRIP);
  FastLED.addLeds<NEOPIXEL, LED_PIN2>(ledRing, NUM_LEDS_RING);

  FastLED.setBrightness(255);
  FastLED.show();

  // TRYING CIRCLE LED HAXX LIBRARY
  circleLED.attach(16);

  modeButton.attach(MODE_PIN, INPUT_PULLUP);
  stream1Button.attach(STREAM1_PIN, INPUT_PULLUP);
  stream2Button.attach(STREAM2_PIN, INPUT_PULLUP);
  stream3Button.attach(STREAM3_PIN, INPUT_PULLUP);
  river1Button.attach(RIVER1_PIN, INPUT_PULLUP);
  river2Button.attach(RIVER2_PIN, INPUT_PULLUP);
  river1Button.attach(RIVER3_PIN, INPUT_PULLUP);
  // debounce interval in milliseconds
  modeButton.interval(5);
  stream1Button.interval(5);
  stream2Button.interval(5);
  stream3Button.interval(5);
  river1Button.interval(5);
  river2Button.interval(5);
  river3Button.interval(5);
  // indicate that the low state corresponds to phsyically pressing the button
  modeButton.setPressedState(LOW); 
  stream1Button.setPressedState(LOW);
  stream2Button.setPressedState(LOW);
  stream3Button.setPressedState(LOW);
  river1Button.setPressedState(LOW);
  river2Button.setPressedState(LOW);
  river3Button.setPressedState(LOW);

  Serial.begin(115200);
  Serial2.begin(9600);

  printer.begin();
  //ONLY USED FOR DEBUGGING OR TALKING TO A COMPUTER
  //DELETE BEFORE FINAL
  while(!Serial);
}

void loop() {
  modeButton.update();
  // stream1Button.update();
  // stream2Button.update();
  // stream3Button.update();
  // river1Button.update();
  // river2Button.update();
  // river3Button.update();

  if(modeButton.pressed()){
    if(climateCondition == 2){
      climateCondition = 0;
      Serial.println("Climate Condition: Normal");
      pacifica_loop(ledRing);
    }else{
      climateCondition++;
      if(climateCondition == 1){
        Serial.println("Climate Conditions: High Snowpack");
        snowpack(ledRing);
      } else if(climateCondition == 2){
        Serial.println("Climate Conditions: Dought");
        drought_loop(ledRing);
      }
    }
  }

  if(stream1Button.pressed()){
    switch(climateCondition){
      case 0:
        printNormalConditions(printer, 1, 'X');
        break;
      case 1:
        printSnowConditions(printer, 1, 'X');
        break;
      case 2:
        printDroughtConditions(printer, 1, 'X');
        break;
    }
    printQR(printer);
  }

  if(stream2Button.pressed()){
    switch(climateCondition){
      case 0:
        printNormalConditions(printer, 2, 'X');
        break;
      case 1:
        printSnowConditions(printer, 2, 'X');
        break;
      case 2:
        printDroughtConditions(printer, 2, 'X');
        break;
    }
    printQR(printer);
  }

  if(stream3Button.pressed()){
    switch(climateCondition){
      case 0:
        printNormalConditions(printer, 3, 'X');
        break;
      case 1:
        printSnowConditions(printer, 3, 'X');
        break;
      case 2:
        printDroughtConditions(printer, 3, 'X');
        break;
    }
    printQR(printer);
  }

  if(river1Button.pressed()){
    switch(climateCondition){
      case 0:
        printNormalConditions(printer, 0, 'A');
        break;
      case 1:
        printSnowConditions(printer, 0, 'A');
        break;
      case 2:
        printDroughtConditions(printer, 0, 'A');
        break;
    }
    printQR(printer);
  }

  if(river2Button.pressed()){
    switch(climateCondition){
      case 0:
        printNormalConditions(printer, 0, 'B');
        break;
      case 1:
        printSnowConditions(printer, 0, 'B');
        break;
      case 2:
        printDroughtConditions(printer, 0, 'B');
        break;
    }
    printQR(printer);
  }

  if(river3Button.pressed()){
    switch(climateCondition){
      case 0:
        printNormalConditions(printer, 0, 'C');
        break;
      case 1:
        printSnowConditions(printer, 0, 'C');
        break;
      case 2:
        printDroughtConditions(printer, 0, 'C');
        break;
    }
    printQR(printer);
  }
  
}

void demo(){
   // DEMO from video
   // will have to put back into main loop
   // before using I think
  uint8_t mode = 0;
  uint8_t stream = 0;
  char river = 'X';

  if(modeButton.pressed()){
    switch(mode){
      case 0:
        stream = 2;
        river = 'X';
        greenStream(ledStrip, NUM_LEDS_STRIP);
        printNormalConditions(printer, stream, river);
        printer.feed(4);
        break;

      case 1:
        stream = 0;
        river = 'A';
        blueStream(ledStrip, NUM_LEDS_STRIP);
        printSnowConditions(printer, stream, river);
        printer.feed(4);
        break;
      
      case 2:
        stream = 3;
        river = 'X';
        redStream(ledStrip, NUM_LEDS_STRIP);
        printDroughtConditions(printer, stream, river);
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