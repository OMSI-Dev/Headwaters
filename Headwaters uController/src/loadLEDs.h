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
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 500);
  fill_solid(ledStrip, NUM_LEDS_TOTAL, CRGB::Black);
  FastLED.show();
}

// Create a stream effect without a for loop, recursing
// in the main loop, with the correct colors for
// normal climate conditions.
// Saturation values: Blue 160, Green 96, Red 0
uint8_t normalConditionsRecurse(uint8_t ledPixel, uint8_t sinBeat){
  if(ledPixel >= NUM_LEDS_TOTAL){
    return 0;
  }

  // Set Rivers A & B
  if(ledPixel < NUM_LEDS_RIVER_A + NUM_LEDS_RIVER_B){
    ledStrip[ledPixel] = CHSV(160, 255, sinBeat);
    FastLED.show();
    return (ledPixel + 1);
  }

  // Set River C & Stream 3 & 2
  if(ledPixel >= NUM_LEDS_RIVER_A + NUM_LEDS_RIVER_B && ledPixel < NUM_LEDS_RIVER_A + NUM_LEDS_RIVER_B + NUM_LEDS_RIVER_C + NUM_LEDS_STREAM_3 + NUM_LEDS_STREAM_2){
    ledStrip[ledPixel] = CHSV(96, 255, sinBeat);
    FastLED.show();
    return (ledPixel + 1);
  }

  // Set Stream 1
  if(ledPixel >= NUM_LEDS_RIVER_A + NUM_LEDS_RIVER_B + NUM_LEDS_RIVER_C + NUM_LEDS_STREAM_3 + NUM_LEDS_STREAM_2 && ledPixel < NUM_LEDS_TOTAL){
    ledStrip[ledPixel] = CHSV(160, 255, sinBeat);
    FastLED.show();
    return (ledPixel + 1);
  }
  return 0;
}

// Fill the stream and river LEDs with the colors
// for normal climate conditions. Simple, no animation.
void normalConditions(){
  fill_solid(stream1_array, NUM_LEDS_STREAM_1, CRGB::Blue);
  fill_solid(stream2_array, NUM_LEDS_STREAM_2, CRGB::Green);
  fill_solid(stream3_array, NUM_LEDS_STREAM_3, CRGB::Green);
  fill_solid(riverA_array, NUM_LEDS_RIVER_A, CRGB::Blue);
  fill_solid(riverB_array, NUM_LEDS_RIVER_B, CRGB::Blue);
  fill_solid(riverC_array, NUM_LEDS_RIVER_C, CRGB::Green);
  FastLED.show();
}

// Create a stream effect without a for loop, recursing
// in the main loop, with the correct colors for
// high snowpack climate conditions.
// Saturation values: Blue 160, Green 96, Red 0
uint8_t snowConditionsRecurse(uint8_t ledPixel, uint8_t sinBeat){
  if(ledPixel >= NUM_LEDS_TOTAL){
    return 0;
  }

  // Set Rivers A & B & C
  if(ledPixel < NUM_LEDS_RIVER_A + NUM_LEDS_RIVER_B + NUM_LEDS_RIVER_C){
    ledStrip[ledPixel] = CHSV(160, 255, sinBeat);
    FastLED.show();
    return (ledPixel + 1);
  }

  // Set Stream 3
  if(ledPixel >= NUM_LEDS_RIVER_A + NUM_LEDS_RIVER_B + NUM_LEDS_RIVER_C && ledPixel < NUM_LEDS_RIVER_A + NUM_LEDS_RIVER_B + NUM_LEDS_RIVER_C + NUM_LEDS_STREAM_3){
    ledStrip[ledPixel] = CHSV(96, 255, sinBeat);
    FastLED.show();
    return (ledPixel + 1);
  }

  // Set Streams 2 & 1
  if(ledPixel >= NUM_LEDS_RIVER_A + NUM_LEDS_RIVER_B + NUM_LEDS_RIVER_C + NUM_LEDS_STREAM_3 && ledPixel < NUM_LEDS_TOTAL){
    ledStrip[ledPixel] = CHSV(160, 255, sinBeat);
    FastLED.show();
    return (ledPixel + 1);
  }

  return 0;
}

// Fill the stream and river LEDs with the colors
// for high snowpack climate conditions. Simple, no animation.
void snowConditions(){
  fill_solid(stream1_array, NUM_LEDS_STREAM_1, CRGB::Blue);
  fill_solid(stream2_array, NUM_LEDS_STREAM_2, CRGB::Blue);
  fill_solid(stream3_array, NUM_LEDS_STREAM_3, CRGB::Green);
  fill_solid(riverA_array, NUM_LEDS_RIVER_A, CRGB::Blue);
  fill_solid(riverB_array, NUM_LEDS_RIVER_B, CRGB::Blue);
  fill_solid(riverC_array, NUM_LEDS_RIVER_C, CRGB::Blue);
  FastLED.show();
}

// Create a stream effect without a for loop, recursing
// in the main loop, with the correct colors for
// drought climate conditions.
// Saturation values: Blue 160, Green 96, Red 0
uint8_t droughtConditionsRecurse(uint8_t ledPixel, uint8_t sinBeat){
  if(ledPixel >= NUM_LEDS_TOTAL){
    return 0;
  }

  // Set River A
  if(ledPixel < NUM_LEDS_RIVER_A){
    ledStrip[ledPixel] = CHSV(160, 255, sinBeat);
    FastLED.show();
    return (ledPixel + 1);
  }

  // Set River B
  if(ledPixel >= NUM_LEDS_RIVER_A && ledPixel < NUM_LEDS_RIVER_A + NUM_LEDS_RIVER_B){
    ledStrip[ledPixel] = CHSV(96, 255, sinBeat);
    FastLED.show();
    return (ledPixel + 1);
  }

  // Set River C & Stream 3 & 2
  if(ledPixel >= NUM_LEDS_RIVER_A + NUM_LEDS_RIVER_B && ledPixel < NUM_LEDS_RIVER_A + NUM_LEDS_RIVER_B + NUM_LEDS_RIVER_C + NUM_LEDS_STREAM_3 + NUM_LEDS_STREAM_2){
    ledStrip[ledPixel] = CHSV(0, 255, sinBeat);
    FastLED.show();
    return (ledPixel + 1);
  }

  // Set Stream 1
  if(ledPixel >= NUM_LEDS_RIVER_A + NUM_LEDS_RIVER_B + NUM_LEDS_RIVER_C + NUM_LEDS_STREAM_3 + NUM_LEDS_STREAM_2 && ledPixel < NUM_LEDS_TOTAL){
    ledStrip[ledPixel] = CHSV(160, 255, sinBeat);
    FastLED.show();
    return (ledPixel + 1);
  }

  return 0;
}

// Fill the stream and river LEDs with the colors
// for drought climate conditions. Simple, no animation.
void droughtConditions(){
  fill_solid(stream1_array, NUM_LEDS_STREAM_1, CRGB::Blue);
  fill_solid(stream2_array, NUM_LEDS_STREAM_2, CRGB::Red);
  stream2_array[0] = CRGB::Black;
  stream2_array[1] = CRGB::Black;
  stream2_array[2] = CRGB::Black;
  stream2_array[3] = CRGB::Black;
  stream2_array[4] = CHSV(0, 255, 30);
  stream2_array[5] = CHSV(0, 255, 50);
  stream2_array[6] = CHSV(0, 255, 100);
  stream2_array[7] = CHSV(0, 255, 150);
  stream2_array[8] = CHSV(0, 255, 200);
  fill_solid(stream3_array, NUM_LEDS_STREAM_3, CRGB::Red);
  stream3_array[0] = CRGB::Black;
  stream3_array[1] = CRGB::Black;
  stream3_array[2] = CRGB::Black;
  stream3_array[3] = CRGB::Black;
  stream3_array[4] = CRGB::Black;
  stream3_array[5] = CHSV(0, 255, 30);
  stream3_array[6] = CHSV(0, 255, 50);
  stream3_array[7] = CHSV(0, 255, 75);
  stream3_array[8] = CHSV(0, 255, 100);
  stream3_array[9] = CHSV(0, 255, 125);
  stream3_array[10] = CHSV(0, 255, 150);
  stream3_array[11] = CHSV(0, 255, 175);
  stream3_array[12] = CHSV(0, 255, 200);
  stream3_array[13] = CHSV(0, 255, 225);
  fill_solid(riverA_array, NUM_LEDS_RIVER_A, CRGB::Blue);
  fill_solid(riverB_array, NUM_LEDS_RIVER_B, CRGB::Green);
  fill_solid(riverC_array, NUM_LEDS_RIVER_C, CRGB::Red);
  //  River in drought should be full red, adjusted to match new request.
  // riverC_array[NUM_LEDS_RIVER_C] = CRGB::Black;
  // riverC_array[NUM_LEDS_RIVER_C - 1] = CRGB::Black;
  // riverC_array[NUM_LEDS_RIVER_C - 2] = CRGB::Black;
  // riverC_array[NUM_LEDS_RIVER_C - 3] = CRGB::Black;
  // riverC_array[NUM_LEDS_RIVER_C - 4] = CRGB::Black;
  // riverC_array[NUM_LEDS_RIVER_C - 5] = CRGB::Black;
  // riverC_array[NUM_LEDS_RIVER_C - 7] = CRGB::Black;
  // riverC_array[NUM_LEDS_RIVER_C - 8] = CRGB::Black;
  // riverC_array[NUM_LEDS_RIVER_C - 9] = CRGB::Black;
  // riverC_array[NUM_LEDS_RIVER_C - 10] = CHSV(0, 255, 30);
  // riverC_array[NUM_LEDS_RIVER_C - 11] = CHSV(0, 255, 50);
  // riverC_array[NUM_LEDS_RIVER_C - 12] = CHSV(0, 255, 100);
  // riverC_array[NUM_LEDS_RIVER_C - 13] = CHSV(0, 255, 150);
  // riverC_array[NUM_LEDS_RIVER_C - 14] = CHSV(0, 255, 175);
  // riverC_array[NUM_LEDS_RIVER_C - 15] = CHSV(0, 255, 200);
  // riverC_array[NUM_LEDS_RIVER_C - 16] = CHSV(0, 255, 225);
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