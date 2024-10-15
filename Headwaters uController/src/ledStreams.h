#include <Arduino.h>
#include <FastLED.h>

// Calico created September 26th, 2024
// Header file to keep the code that creates the streams
// and the rivers in the LED strip and potential ring.

// LED RING
// LED Pin definitino and total number of LEDs in the ring
#define LED_RING_PIN 16
#define NUM_LEDS_RING 31

// Create the array of LEDs for the ring
CRGB ledRing[NUM_LEDS_RING];

// LED STRIP 
#define LED_STRIP_PIN 15
// Declare number of pixels in each section, total of these will be
// the total number of LEDs in the strip
#define NUM_LEDS_STREAM1 2 // pixels 0-1
#define NUM_LEDS_STREAM2 4 // pixels 2-5
#define NUM_LEDS_STREAM3 0 // pixels
#define NUM_LEDS_RIVER1 6  // pixels 6-13
#define NUM_LEDS_RIVER2 2  // pixels 14-15
#define NUM_LEDS_RIVER3 0  // pixels 
#define NUM_LEDS_STRIP (NUM_LEDS_STREAM1 + NUM_LEDS_STREAM2 + NUM_LEDS_STREAM3 + NUM_LEDS_RIVER1 + NUM_LEDS_RIVER2 + NUM_LEDS_RIVER3)

// Create the array of LEDs for the strip
CRGB ledStrip[NUM_LEDS_STRIP];

// Setups the LED strip and ring
bool setupLED(){
  FastLED.addLeds<NEOPIXEL, LED_STRIP_PIN>(ledStrip, NUM_LEDS_STRIP);
  FastLED.addLeds<NEOPIXEL, LED_RING_PIN>(ledRing, NUM_LEDS_RING);
  
  FastLED.setBrightness(255);
  FastLED.show();

  // if(ledStrip.size() == 0){
  //   return false;
  // }
  return true;
}

void normalConditionsLED(){
  // LEDs set for Stream 1
  for(uint8_t i = 0; i < NUM_LEDS_STREAM1; i++){
    ledStrip[i] = CRGB::Blue;
  }
  
  // LEDs set for Stream 2
  for(uint8_t i = 0; i < NUM_LEDS_STREAM2; i++){
    ledStrip[NUM_LEDS_STREAM1 + i] = CRGB::Green;
  }
  
  // LEDs set for Stream 3
  for(uint8_t i = 0; i < NUM_LEDS_STREAM3; i++){
    ledStrip[NUM_LEDS_STREAM1 + NUM_LEDS_STREAM2 + i] = CRGB::Green;
  }
  
  // LEDS set for River A
  for(uint8_t i = 0; i < NUM_LEDS_RIVER1; i++){
    ledStrip[NUM_LEDS_STREAM1 + NUM_LEDS_STREAM2 + NUM_LEDS_STREAM3 + i] = CRGB::Blue;
  }
  
  // LEDS set for River B
  for(uint8_t i = 0; i < NUM_LEDS_RIVER2; i++){
    ledStrip[NUM_LEDS_STREAM1 + NUM_LEDS_STREAM2 + NUM_LEDS_STREAM3 + NUM_LEDS_RIVER1 + i] = CRGB::Blue;
  }
  
  // LEDS set for River C
  for(uint8_t i = 0; i < NUM_LEDS_RIVER3; i++){
    ledStrip[NUM_LEDS_STREAM1 + NUM_LEDS_STREAM2 + NUM_LEDS_STREAM3 + NUM_LEDS_RIVER1 + NUM_LEDS_RIVER2 + i] = CRGB::Green;
  }
  FastLED.show();
}

void snowConditionsLED(){
   // LEDs set for Stream 1
  for(uint8_t i = 0; i < NUM_LEDS_STREAM1; i++){
    ledStrip[i] = CRGB::Blue;
  }
  
  // LEDs set for Stream 2
  for(uint8_t i = 0; i < NUM_LEDS_STREAM2; i++){
    ledStrip[NUM_LEDS_STREAM1 + i] = CRGB::Blue;
  }
  
  // LEDs set for Stream 3
  for(uint8_t i = 0; i < NUM_LEDS_STREAM3; i++){
    ledStrip[NUM_LEDS_STREAM1 + NUM_LEDS_STREAM2 + i] = CRGB::Green;
  }
  
  // LEDS set for River A
  for(uint8_t i = 0; i < NUM_LEDS_RIVER1; i++){
    ledStrip[NUM_LEDS_STREAM1 + NUM_LEDS_STREAM2 + NUM_LEDS_STREAM3 + i] = CRGB::Blue;
  }
  
  // LEDS set for River B
  for(uint8_t i = 0; i < NUM_LEDS_RIVER2; i++){
    ledStrip[NUM_LEDS_STREAM1 + NUM_LEDS_STREAM2 + NUM_LEDS_STREAM3 + NUM_LEDS_RIVER1 + i] = CRGB::Blue;
  }
  
  // LEDS set for River C
  for(uint8_t i = 0; i < NUM_LEDS_RIVER3; i++){
    ledStrip[NUM_LEDS_STREAM1 + NUM_LEDS_STREAM2 + NUM_LEDS_STREAM3 + NUM_LEDS_RIVER1 + NUM_LEDS_RIVER2 + i] = CRGB::Blue;
  }
  FastLED.show();
}

void droughtConditionsLED(){
 // LEDs set for Stream 1
  for(uint8_t i = 0; i < NUM_LEDS_STREAM1; i++){
    ledStrip[i] = CRGB::Blue;
  }
  
  // LEDs set for Stream 2
  for(uint8_t i = 0; i < NUM_LEDS_STREAM2; i++){
    ledStrip[NUM_LEDS_STREAM1 + i] = CRGB::Red;
  }
  
  // LEDs set for Stream 3
  for(uint8_t i = 0; i < NUM_LEDS_STREAM3; i++){
    ledStrip[NUM_LEDS_STREAM1 + NUM_LEDS_STREAM2 + i] = CRGB::Red;
  }
  
  // LEDS set for River A
  for(uint8_t i = 0; i < NUM_LEDS_RIVER1; i++){
    ledStrip[NUM_LEDS_STREAM1 + NUM_LEDS_STREAM2 + NUM_LEDS_STREAM3 + i] = CRGB::Blue;
  }
  
  // LEDS set for River B
  for(uint8_t i = 0; i < NUM_LEDS_RIVER2; i++){
    ledStrip[NUM_LEDS_STREAM1 + NUM_LEDS_STREAM2 + NUM_LEDS_STREAM3 + NUM_LEDS_RIVER1 + i] = CRGB::Green;
  }
  
  // LEDS set for River C
  for(uint8_t i = 0; i < NUM_LEDS_RIVER3; i++){
    ledStrip[NUM_LEDS_STREAM1 + NUM_LEDS_STREAM2 + NUM_LEDS_STREAM3 + NUM_LEDS_RIVER1 + NUM_LEDS_RIVER2 + i] = CRGB::Red;
  }
  FastLED.show();
}

void blueStream(){
    // create a blue "stream" on the LED strip 
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
}

void greenStream(){
    // create a green "stream" on the LED strip 
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
}

void redStream(){
    // create a red "stream" on the LED strip 
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
}