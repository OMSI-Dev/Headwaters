#include <Arduino.h>
#include <FastLED.h>

// Calico created September 26th, 2024
// Header file to keep the code that creates the streams
// and the rivers in the LED strip and potential ring.

// LED strip
#define LED_STRIP_PIN 23
// Declare number of pixels in each section, total of these will be
// the total number of LEDs in the strip
#define NUM_LEDS_STREAM1 22 // pixels 0-21
#define NUM_LEDS_STREAM2 11 // pixels 108-119
#define NUM_LEDS_STREAM3 11 // pixels 120-131
#define NUM_LEDS_RIVER1 22  // pixels 0-21
#define NUM_LEDS_RIVER2 31  // pixels 22-53
#define NUM_LEDS_RIVER3 33  // pixels 54-88
#define NUM_LEDS_STRIP (NUM_LEDS_STREAM1 + NUM_LEDS_STREAM2 + NUM_LEDS_STREAM3 + NUM_LEDS_RIVER1 + NUM_LEDS_RIVER2 + NUM_LEDS_RIVER3)

// Create the array of LEDs for the strip
CRGB ledStrip[NUM_LEDS_STRIP];

// Setups the LED strip and ring
void setupLED(){
  FastLED.addLeds<NEOPIXEL, LED_STRIP_PIN>(ledStrip, NUM_LEDS_STRIP);
  
  FastLED.setBrightness(255);
  FastLED.show();
}

void testLED(){
  EVERY_N_MILLISECONDS( 200 ){
    for(uint8_t i = 0; i < NUM_LEDS_STRIP; i++){
      ledStrip[i] = CRGB::Red;
      FastLED.show();
    }
  }
  EVERY_N_MILLISECONDS( 200 ){
    for(uint8_t i = 0; i < NUM_LEDS_STRIP; i++){
      ledStrip[i] = CRGB::Black;
      FastLED.show();
    }
  }
}

// Break up the LED strip to set the required colors 
// for each stream and river under normal climate conditions
void normalConditionsLED(){
  // LEDs set for Stream 1
  for(uint8_t i = 0; i < NUM_LEDS_STREAM1; i++){
    ledStrip[i] = CRGB::Blue;
    FastLED.show();
  }
  
  // LEDs set for Stream 2
  for(uint8_t i = 0; i < NUM_LEDS_STREAM2; i++){
    ledStrip[NUM_LEDS_STREAM1 + i] = CRGB::Green;
    FastLED.show();
  }
  
  // LEDs set for Stream 3
  for(uint8_t i = 0; i < NUM_LEDS_STREAM3; i++){
    ledStrip[NUM_LEDS_STREAM1 + NUM_LEDS_STREAM2 + i] = CRGB::Green;
    FastLED.show();
  }
  
  // LEDS set for River A
  for(uint8_t i = 0; i < NUM_LEDS_RIVER1; i++){
    ledStrip[NUM_LEDS_STREAM1 + NUM_LEDS_STREAM2 + NUM_LEDS_STREAM3 + i] = CRGB::Blue;
    FastLED.show();
  }
  
  // LEDS set for River B
  for(uint8_t i = 0; i < NUM_LEDS_RIVER2; i++){
    ledStrip[NUM_LEDS_STREAM1 + NUM_LEDS_STREAM2 + NUM_LEDS_STREAM3 + NUM_LEDS_RIVER1 + i] = CRGB::Blue;
    FastLED.show();
  }
  
  // LEDS set for River C
  for(uint8_t i = 0; i < NUM_LEDS_RIVER3; i++){
    ledStrip[NUM_LEDS_STREAM1 + NUM_LEDS_STREAM2 + NUM_LEDS_STREAM3 + NUM_LEDS_RIVER1 + NUM_LEDS_RIVER2 + i] = CRGB::Green;
    FastLED.show();
  }
}

// Break up the LED strip to set the required colors 
// for each stream and river under high snowpack climate conditions
void snowConditionsLED(){
   // LEDs set for Stream 1
  for(uint8_t i = 0; i < NUM_LEDS_STREAM1; i++){
    ledStrip[i] = CRGB::Blue;
    FastLED.show();
  }
  
  // LEDs set for Stream 2
  for(uint8_t i = 0; i < NUM_LEDS_STREAM2; i++){
    ledStrip[NUM_LEDS_STREAM1 + i] = CRGB::Blue;
    FastLED.show();
  }
  
  // LEDs set for Stream 3
  for(uint8_t i = 0; i < NUM_LEDS_STREAM3; i++){
    ledStrip[NUM_LEDS_STREAM1 + NUM_LEDS_STREAM2 + i] = CRGB::Green;
    FastLED.show();
  }
  
  // LEDS set for River A
  for(uint8_t i = 0; i < NUM_LEDS_RIVER1; i++){
    ledStrip[NUM_LEDS_STREAM1 + NUM_LEDS_STREAM2 + NUM_LEDS_STREAM3 + i] = CRGB::Blue;
    FastLED.show();
  }
  
  // LEDS set for River B
  for(uint8_t i = 0; i < NUM_LEDS_RIVER2; i++){
    ledStrip[NUM_LEDS_STREAM1 + NUM_LEDS_STREAM2 + NUM_LEDS_STREAM3 + NUM_LEDS_RIVER1 + i] = CRGB::Blue;
    FastLED.show();
  }
  
  // LEDS set for River C
  for(uint8_t i = 0; i < NUM_LEDS_RIVER3; i++){
    ledStrip[NUM_LEDS_STREAM1 + NUM_LEDS_STREAM2 + NUM_LEDS_STREAM3 + NUM_LEDS_RIVER1 + NUM_LEDS_RIVER2 + i] = CRGB::Blue;
    FastLED.show();
  }
}

// Break up the LED strip to set the required colors 
// for each stream and river under drought climate conditions
void droughtConditionsLED(){
 // LEDs set for Stream 1
  for(uint8_t i = 0; i < NUM_LEDS_STREAM1; i++){
    ledStrip[i] = CRGB::Blue;
    FastLED.show();
  }
  
  // LEDs set for Stream 2
  for(uint8_t i = 0; i < NUM_LEDS_STREAM2; i++){
    ledStrip[NUM_LEDS_STREAM1 + i] = CRGB::Red;
    FastLED.show();
  }
  
  // LEDs set for Stream 3
  for(uint8_t i = 0; i < NUM_LEDS_STREAM3; i++){
    ledStrip[NUM_LEDS_STREAM1 + NUM_LEDS_STREAM2 + i] = CRGB::Red;
    FastLED.show();
  }
  
  // LEDS set for River A
  for(uint8_t i = 0; i < NUM_LEDS_RIVER1; i++){
    ledStrip[NUM_LEDS_STREAM1 + NUM_LEDS_STREAM2 + NUM_LEDS_STREAM3 + i] = CRGB::Blue;
    FastLED.show();
  }
  
  // LEDS set for River B
  for(uint8_t i = 0; i < NUM_LEDS_RIVER2; i++){
    ledStrip[NUM_LEDS_STREAM1 + NUM_LEDS_STREAM2 + NUM_LEDS_STREAM3 + NUM_LEDS_RIVER1 + i] = CRGB::Green;
    FastLED.show();
  }
  
  // LEDS set for River C
  for(uint8_t i = 0; i < NUM_LEDS_RIVER3; i++){
    ledStrip[NUM_LEDS_STREAM1 + NUM_LEDS_STREAM2 + NUM_LEDS_STREAM3 + NUM_LEDS_RIVER1 + NUM_LEDS_RIVER2 + i] = CRGB::Red;
    FastLED.show();
  }
}

// Function to animate a blue stream flowing
void blueStream(){
    // create a blue "stream" on the LED strip 
    for(int i = 0; i < NUM_LEDS_STRIP + 1; i++){
      fill_solid(ledStrip, i, CRGB::Blue);
      FastLED.show();
      delay(40);
    }

    for(int i = 0; i < NUM_LEDS_STRIP + 1; i++){
      fill_solid(ledStrip, i, CRGB::Black);
      FastLED.show();
      delay(40);
    }
}

// Function to animate a green stream flowing
void greenStream(){
    // create a green "stream" on the LED strip 
    for(int i = 0; i < NUM_LEDS_STRIP + 1; i++){
      fill_solid(ledStrip, i, CRGB::Green);
      FastLED.show();
      delay(40);
    }

    for(int i = 0; i < NUM_LEDS_STRIP + 1; i++){
      fill_solid(ledStrip, i, CRGB::Black);
      FastLED.show();
      delay(40);
    }
}

// Function to animate a red stream flowing
void redStream(){
    // create a red "stream" on the LED strip 
    for(int i = 0; i < NUM_LEDS_STRIP + 1; i++){
      fill_solid(ledStrip, i, CRGB::Red);
      FastLED.show();
      delay(40);
    }

    for(int i = 0; i < NUM_LEDS_STRIP + 1; i++){
      fill_solid(ledStrip, i, CRGB::Black);
      FastLED.show();
      delay(40);
    }
}

void streamAnimation(uint8_t climateCondition){
  switch(climateCondition){
    case 0:
      for(uint8_t i = 0; i < NUM_LEDS_STRIP; i++){
        EVERY_N_MILLISECONDS( 100 ){
          for(uint8_t j = 0; j < NUM_LEDS_STRIP; j++){
            ledStrip[i] = CRGB::Blue;
          }
          EVERY_N_MILLISECONDS( 100 ){
            ledStrip[i] = CRGB::Black;
          }
        }
      }
      break;
    case 1:
      snowConditionsLED();
      break;
    case 2:
      droughtConditionsLED();
      break;
  }

}