#include <Arduino.h>
#include <FastLED.h>

// Calico created September 26th, 2024
// Header file to keep the code that creates the streams
// and the rivers in the LED strip and potential ring.

// LED strip
#define LED_STRIP_PIN 23

// Declare number of pixels in each section, total of these will be
// the total number of LEDs in the strip.
#define NUM_LEDS_STREAM_1 11 // pixels 115-125
#define NUM_LEDS_STREAM_2 11 // pixels 104-114
#define NUM_LEDS_STREAM_3 18 // pixels 86-103
#define NUM_LEDS_RIVER_A 24  // pixels 0-23
#define NUM_LEDS_RIVER_B 32  // pixels 24-40
#define NUM_LEDS_RIVER_C 30  // pixels 41-61
#define NUM_LEDS_TOTAL (NUM_LEDS_STREAM_1 + NUM_LEDS_STREAM_2 + NUM_LEDS_STREAM_3 + NUM_LEDS_RIVER_A + NUM_LEDS_RIVER_B + NUM_LEDS_RIVER_C)

// Define the array of LEDs for the strip.
CRGBArray <NUM_LEDS_TOTAL> ledStrip;

// Splitting the LED array into specific sections for each river and stream,
// allowing them to be their own array and manipulated as an individual array.
CRGB* riverA_array = &ledStrip[0];
CRGB* riverB_array = &ledStrip[NUM_LEDS_RIVER_A];
CRGB* riverC_array = &ledStrip[NUM_LEDS_RIVER_A + NUM_LEDS_RIVER_B];
CRGB* stream3_array = &ledStrip[NUM_LEDS_RIVER_A + NUM_LEDS_RIVER_B + NUM_LEDS_RIVER_C];
CRGB* stream2_array = &ledStrip[NUM_LEDS_RIVER_A + NUM_LEDS_RIVER_B + NUM_LEDS_RIVER_C + NUM_LEDS_STREAM_3];
CRGB* stream1_array = &ledStrip[NUM_LEDS_RIVER_A + NUM_LEDS_RIVER_B + NUM_LEDS_RIVER_C + NUM_LEDS_STREAM_3 + NUM_LEDS_STREAM_2];

// Setups the LED strip.
void setupLED(){
  FastLED.addLeds<NEOPIXEL, LED_STRIP_PIN>(ledStrip, NUM_LEDS_TOTAL);
  
  FastLED.setBrightness(255);
  fill_solid(ledStrip, NUM_LEDS_TOTAL, CRGB::Black);
  FastLED.show();
}

// Fill the stream and river LEDs with the colors
// for normal climate conditions.
void normalConditions(){
  fill_solid(stream1_array, NUM_LEDS_STREAM_1, CRGB::Blue);
  fill_solid(stream2_array, NUM_LEDS_STREAM_2, CRGB::Green);
  fill_solid(stream3_array, NUM_LEDS_STREAM_3, CRGB::Green);
  fill_solid(riverA_array, NUM_LEDS_RIVER_A, CRGB::Blue);
  fill_solid(riverB_array, NUM_LEDS_RIVER_B, CRGB::Blue);
  fill_solid(riverC_array, NUM_LEDS_RIVER_C, CRGB::Green);
  FastLED.show();
}

// Fill the stream and river LEDs with the colors
// for high snowpack climate conditions.
void snowConditions(){
  fill_solid(stream1_array, NUM_LEDS_STREAM_1, CRGB::Blue);
  fill_solid(stream2_array, NUM_LEDS_STREAM_2, CRGB::Blue);
  fill_solid(stream3_array, NUM_LEDS_STREAM_3, CRGB::Green);
  fill_solid(riverA_array, NUM_LEDS_RIVER_A, CRGB::Blue);
  fill_solid(riverB_array, NUM_LEDS_RIVER_B, CRGB::Blue);
  fill_solid(riverC_array, NUM_LEDS_RIVER_C, CRGB::Blue);
  FastLED.show();
}

// Fill the stream and river LEDs with the colors
// for drought climate conditions.
void droughtConditions(){
  fill_solid(stream1_array, NUM_LEDS_STREAM_1, CRGB::Blue);
  fill_solid(stream2_array, NUM_LEDS_STREAM_2, CRGB::Red);
  fill_solid(stream3_array, NUM_LEDS_STREAM_3, CRGB::Red);
  fill_solid(riverA_array, NUM_LEDS_RIVER_A, CRGB::Blue);
  fill_solid(riverB_array, NUM_LEDS_RIVER_B, CRGB::Green);
  fill_solid(riverC_array, NUM_LEDS_RIVER_C, CRGB::Red);
  FastLED.show();
}

// Recursive function to turn all the LEDs black.
void ledBlackout(uint8_t i){
  if(i == NUM_LEDS_TOTAL){
    return;
  }
  ledStrip[i] = CRGB::Black;
  ledBlackout(i+1);
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