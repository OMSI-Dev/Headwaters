#include <printFunctions.h>
#include <ledModes.h>
#include <ledStreams.h>
#include <loadButtons.h>
 
// Setup printer to hardware serial
// RX0 TX1
Adafruit_Thermal printer(&Serial2);

//MoToTimer buttonLockoutTimer;
//uint16_t btnLockTime = 250;

#define NUM_LEDS_STRIP 14
#define NUM_LEDS_RING 31
#define LED_PIN1 15
#define LED_PIN2 16

// Define the array of LEDs
CRGB ledStrip[NUM_LEDS_STRIP];
CRGB ledRing[NUM_LEDS_RING];

// Climate condition modes
// 0 = Normal
// 1 = High Snowpack
// 2 = Drought
uint8_t climateCondition = 2;

void setup() {
  FastLED.addLeds<NEOPIXEL, LED_PIN1>(ledStrip, NUM_LEDS_STRIP);
  FastLED.addLeds<NEOPIXEL, LED_PIN2>(ledRing, NUM_LEDS_RING);

  FastLED.setBrightness(255);
  FastLED.show();

  if(setupButtons() == false){
    Serial.println("Problem with setting up buttons.");
  }

  Serial.begin(115200);
  Serial2.begin(9600);

  printer.begin();
  //ONLY USED FOR DEBUGGING OR TALKING TO A COMPUTER
  //DELETE BEFORE FINAL
  while(!Serial);
}

void loop() {
  updateButtons();

  if(modeButton.pressed()){
    if(climateCondition == 2){
      climateCondition = 0;
      Serial.println("Climate Condition: Normal");
      //pacifica_loop(ledRing);
    }else{
      climateCondition++;
      if(climateCondition == 1){
        Serial.println("Climate Conditions: High Snowpack");
        //snowpack(ledRing);
      } else if(climateCondition == 2){
        Serial.println("Climate Conditions: Dought");
        //drought_loop(ledRing);
      }
    }
  }

  if(stream1Button.pressed()){
    printStream(printer, climateCondition, 1);
  }

  if(stream2Button.pressed()){
    printStream(printer, climateCondition, 2);
  }

  if(stream3Button.pressed()){
    printStream(printer, climateCondition, 3);
  }

  if(river1Button.pressed()){
    printRiver(printer, climateCondition, 'A');
  }

  if(river2Button.pressed()){
    printRiver(printer, climateCondition, 'B');
  }

  if(river3Button.pressed()){
    printRiver(printer, climateCondition, 'C');
  }

  if(precip1Button.pressed()){
    printPrecipitation(printer, climateCondition, 1);
  }

  if(precip2Button.pressed()){
    printPrecipitation(printer, climateCondition, 2);
  }

  if(precip3Button.pressed()){
    printPrecipitation(printer, climateCondition, 3);
  }
  //printQR(printer);
}