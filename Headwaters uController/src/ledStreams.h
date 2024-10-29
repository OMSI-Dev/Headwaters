#include <Arduino.h>
#include <FastLED.h>

// Calico created September 26th, 2024
// Header file to keep the code that creates the streams
// and the rivers in the LED strip and potential ring.

// LED strip
#define LED_STRIP_PIN 23
// Declare number of pixels in each section, total of these will be
// the total number of LEDs in the strip.
#define NUM_LEDS_STREAM_1 22 // pixels 0-21
#define NUM_LEDS_STREAM_2 11 // pixels 108-119
#define NUM_LEDS_STREAM_3 11 // pixels 120-131
#define NUM_LEDS_RIVER_A 22  // pixels 0-21
#define NUM_LEDS_RIVER_B 31  // pixels 22-53
#define NUM_LEDS_RIVER_C 33  // pixels 54-88
#define NUM_LEDS_TOTAL (NUM_LEDS_STREAM_1 + NUM_LEDS_STREAM_2 + NUM_LEDS_STREAM_3 + NUM_LEDS_RIVER_A + NUM_LEDS_RIVER_B + NUM_LEDS_RIVER_C)

// Create the array of LEDs for the strip.
CRGB ledStrip[NUM_LEDS_TOTAL];

// Setups the LED strip and ring.
void setupLED(){
  FastLED.addLeds<NEOPIXEL, LED_STRIP_PIN>(ledStrip, NUM_LEDS_TOTAL);
  
  FastLED.setBrightness(255);
  FastLED.show();
}

void testLED(){
  EVERY_N_MILLISECONDS( 200 ){
    for(uint8_t i = 0; i < NUM_LEDS_TOTAL; i++){
      ledStrip[i] = CRGB::Red;
      FastLED.show();
    }
  }
  EVERY_N_MILLISECONDS( 200 ){
    for(uint8_t i = 0; i < NUM_LEDS_TOTAL; i++){
      ledStrip[i] = CRGB::Black;
      FastLED.show();
    }
  }
}

// Break up the LED strip to set the required colors 
// for each stream and river under normal climate conditions.
void normalConditionsLED(){
  // River A
  for(uint8_t i = 0; i < NUM_LEDS_RIVER_A; i++){
    ledStrip[i] = CRGB::Blue;
    FastLED.show();
  }
  
  // River B
  for(uint8_t i = 0; i < NUM_LEDS_RIVER_B; i++){
    ledStrip[NUM_LEDS_RIVER_A + i] = CRGB::Blue;
    FastLED.show();
  }
  
  // River C
  for(uint8_t i = 0; i < NUM_LEDS_RIVER_C; i++){
    ledStrip[NUM_LEDS_RIVER_A + NUM_LEDS_RIVER_B + i] = CRGB::Green;
    FastLED.show();
  }
  
  // Stream 3
  for(uint8_t i = 0; i < NUM_LEDS_STREAM_3; i++){
    ledStrip[NUM_LEDS_RIVER_A + NUM_LEDS_RIVER_B + NUM_LEDS_RIVER_C + i] = CRGB::Green;
    FastLED.show();
  }
  
  // Stream 2
  for(uint8_t i = 0; i < NUM_LEDS_STREAM_2; i++){
    ledStrip[NUM_LEDS_RIVER_A + NUM_LEDS_RIVER_B + NUM_LEDS_RIVER_C + NUM_LEDS_STREAM_3 + i] = CRGB::Green;
    FastLED.show();
  }
  
  // Stream 1
  for(uint8_t i = 0; i < NUM_LEDS_STREAM_1; i++){
    ledStrip[NUM_LEDS_RIVER_A + NUM_LEDS_RIVER_B + NUM_LEDS_RIVER_C + NUM_LEDS_STREAM_3 + NUM_LEDS_STREAM_2 + i] = CRGB::Blue;
    FastLED.show();
  }
}

// Break up the LED strip to set the required colors 
// for each stream and river under high snowpack climate conditions
void snowConditionsLED(){
  // River A
  for(uint8_t i = 0; i < NUM_LEDS_RIVER_A; i++){
    ledStrip[i] = CRGB::Blue;
    FastLED.show();
  }
  
  // River B
  for(uint8_t i = 0; i < NUM_LEDS_RIVER_B; i++){
    ledStrip[NUM_LEDS_RIVER_A + i] = CRGB::Blue;
    FastLED.show();
  }
  
  // River C
  for(uint8_t i = 0; i < NUM_LEDS_RIVER_C; i++){
    ledStrip[NUM_LEDS_RIVER_A + NUM_LEDS_RIVER_B + i] = CRGB::Blue;
    FastLED.show();
  }
  
  // Stream 3
  for(uint8_t i = 0; i < NUM_LEDS_STREAM_3; i++){
    ledStrip[NUM_LEDS_RIVER_A + NUM_LEDS_RIVER_B + NUM_LEDS_RIVER_C + i] = CRGB::Green;
    FastLED.show();
  }
  
  // Stream 2
  for(uint8_t i = 0; i < NUM_LEDS_STREAM_2; i++){
    ledStrip[NUM_LEDS_RIVER_A + NUM_LEDS_RIVER_B + NUM_LEDS_RIVER_C + NUM_LEDS_STREAM_3 + i] = CRGB::Blue;
    FastLED.show();
  }
  
  // Stream 1
  for(uint8_t i = 0; i < NUM_LEDS_STREAM_1; i++){
    ledStrip[NUM_LEDS_RIVER_A + NUM_LEDS_RIVER_B + NUM_LEDS_RIVER_C + NUM_LEDS_STREAM_3 + NUM_LEDS_STREAM_2 + i] = CRGB::Blue;
    FastLED.show();
  }
}

// Break up the LED strip to set the required colors 
// for each stream and river under drought climate conditions
void droughtConditionsLED(){
  // River A
  for(uint8_t i = 0; i < NUM_LEDS_RIVER_A; i++){
    ledStrip[i] = CRGB::Blue;
    FastLED.show();
  }
  
  // River B
  for(uint8_t i = 0; i < NUM_LEDS_RIVER_B; i++){
    ledStrip[NUM_LEDS_RIVER_A + i] = CRGB::Green;
    FastLED.show();
  }
  
  // River C
  for(uint8_t i = 0; i < NUM_LEDS_RIVER_C; i++){
    ledStrip[NUM_LEDS_RIVER_A + NUM_LEDS_RIVER_B + i] = CRGB::Red;
    FastLED.show();
  }
  
  // Stream 3
  for(uint8_t i = 0; i < NUM_LEDS_STREAM_3; i++){
    ledStrip[NUM_LEDS_RIVER_A + NUM_LEDS_RIVER_B + NUM_LEDS_RIVER_C + i] = CRGB::Red;
    FastLED.show();
  }
  
  // Stream 2
  for(uint8_t i = 0; i < NUM_LEDS_STREAM_2; i++){
    ledStrip[NUM_LEDS_RIVER_A + NUM_LEDS_RIVER_B + NUM_LEDS_RIVER_C + NUM_LEDS_STREAM_3 + i] = CRGB::Red;
    FastLED.show();
  }
  
  // Stream 1
  for(uint8_t i = 0; i < NUM_LEDS_STREAM_1; i++){
    ledStrip[NUM_LEDS_RIVER_A + NUM_LEDS_RIVER_B + NUM_LEDS_RIVER_C + NUM_LEDS_STREAM_3 + NUM_LEDS_STREAM_2 + i] = CRGB::Blue;
    FastLED.show();
  }
}

// Animate a blue stream flowing.
void blueStream(){
    for(int i = 0; i < NUM_LEDS_TOTAL + 1; i++){
      fill_solid(ledStrip, i, CRGB::Blue);
      FastLED.show();
      delay(40);
    }

    for(int i = 0; i < NUM_LEDS_TOTAL + 1; i++){
      fill_solid(ledStrip, i, CRGB::Black);
      FastLED.show();
      delay(40);
    }
}

// Animate a green stream flowing.
void greenStream(){
    for(int i = 0; i < NUM_LEDS_TOTAL + 1; i++){
      fill_solid(ledStrip, i, CRGB::Green);
      FastLED.show();
      delay(40);
    }

    for(int i = 0; i < NUM_LEDS_TOTAL + 1; i++){
      fill_solid(ledStrip, i, CRGB::Black);
      FastLED.show();
      delay(40);
    }
}

// Animate a red stream flowing.
void redStream(){
    for(int i = 0; i < NUM_LEDS_TOTAL + 1; i++){
      fill_solid(ledStrip, i, CRGB::Red);
      FastLED.show();
      delay(40);
    }

    for(int i = 0; i < NUM_LEDS_TOTAL + 1; i++){
      fill_solid(ledStrip, i, CRGB::Black);
      FastLED.show();
      delay(40);
    }
}