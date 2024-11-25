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
  
  //FastLED.setBrightness(50);
  FastLED.setMaxPowerInVoltsAndMilliamps(5, 500);
  fill_solid(ledStrip, NUM_LEDS_TOTAL, CRGB::Black);
  FastLED.show();
}

// Create a stream effect without a for loop, recursing
// in the main loop, with the correct colors for
// normal climate conditions.
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
  // Set River C
  if(ledPixel >= NUM_LEDS_RIVER_A + NUM_LEDS_RIVER_B && ledPixel < NUM_LEDS_RIVER_A + NUM_LEDS_RIVER_B + NUM_LEDS_RIVER_C){
    ledStrip[ledPixel] = CHSV(160, 255, sinBeat);
    FastLED.show();
    return (ledPixel + 1);
  }
  // Set Stream 3 & 2
  if(ledPixel >= NUM_LEDS_RIVER_A + NUM_LEDS_RIVER_B + NUM_LEDS_RIVER_C && ledPixel < NUM_LEDS_RIVER_A + NUM_LEDS_RIVER_B + NUM_LEDS_RIVER_C + NUM_LEDS_STREAM_3 + NUM_LEDS_STREAM_2){
    if(ledPixel == 86 ||
        ledPixel == 87 ||
        ledPixel == 88 ||
        ledPixel == 89 ||
        ledPixel == 104 ||
        ledPixel == 105){
      ledStrip[ledPixel] = CRGB::Black;
      FastLED.show();
    } else {
      ledStrip[ledPixel] = CHSV(96, 255, sinBeat);
      FastLED.show();
    }
    return (ledPixel + 1);
  }
  // Set Stream 1
  if(ledPixel >= NUM_LEDS_RIVER_A + NUM_LEDS_RIVER_B + NUM_LEDS_RIVER_C + NUM_LEDS_STREAM_3 + NUM_LEDS_STREAM_2 && ledPixel < NUM_LEDS_TOTAL){
    if(ledPixel == 115 || ledPixel == 116){
      ledStrip[ledPixel] = CRGB::Black;
      FastLED.show();
    } else {
      ledStrip[ledPixel] = CHSV(160, 255, sinBeat);
      FastLED.show();
    }
    return (ledPixel + 1);
  }
  return 0;
}

// Fill the stream and river LEDs with the colors
// for normal climate conditions.
void normalConditions(){

  // // Saturation values: Blue 160, Green 96, Red 0
  // riverA_array[NUM_LEDS_RIVER_A] = CHSV(160, sinBeat, 255);
  // stream1_array[NUM_LEDS_STREAM_1] = CHSV(160, sinBeat, 255);
  // riverB_array[NUM_LEDS_RIVER_B] = CHSV(160, sinBeat, 255);
  // stream2_array[NUM_LEDS_STREAM_2] = CHSV(96, sinBeat, 255);
  // riverC_array[NUM_LEDS_RIVER_C] = CHSV(96, sinBeat, 255);
  // stream3_array[NUM_LEDS_STREAM_3] = CHSV(96, sinBeat, 255);
  
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
// for high snowpack climate conditions.
void snowConditions(){
  
  // // Saturation values: Blue 160, Green 96, Red 0
  // riverA_array[NUM_LEDS_RIVER_A] = CHSV(0, 160, sinBeat);
  // stream1_array[NUM_LEDS_STREAM_1] = CHSV(0, 160, sinBeat);
  // riverB_array[NUM_LEDS_RIVER_B] = CHSV(0, 160, sinBeat);
  // stream2_array[NUM_LEDS_STREAM_2] = CHSV(0, 160, sinBeat);
  // riverC_array[NUM_LEDS_RIVER_C] = CHSV(0, 160, sinBeat);
  // stream3_array[NUM_LEDS_STREAM_3] = CHSV(0, 96, sinBeat);

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
    if(ledPixel == 86 ||
        ledPixel == 87 ||
        ledPixel == 88 ||
        ledPixel == 89 ||
        ledPixel == 90 ||
        ledPixel == 91 ||
        ledPixel == 92 ||
        ledPixel == 93 ||
        ledPixel == 104 ||
        ledPixel == 105 ||
        ledPixel == 106 ||
        ledPixel == 107 ||
        ledPixel == 108){
      ledStrip[ledPixel] = CRGB::Black;
      FastLED.show();
    } else {
      ledStrip[ledPixel] = CHSV(0, 255, sinBeat);
      FastLED.show();
    }
    return (ledPixel + 1);
  }
  // Set Stream 1
  if(ledPixel >= NUM_LEDS_RIVER_A + NUM_LEDS_RIVER_B + NUM_LEDS_RIVER_C + NUM_LEDS_STREAM_3 + NUM_LEDS_STREAM_2 && ledPixel < NUM_LEDS_TOTAL){
    if(ledPixel == 115 ||
        ledPixel == 116 ||
        ledPixel == 117 ||
        ledPixel == 118 ||
        ledPixel == 119){
      ledStrip[ledPixel] = CRGB::Black;
      FastLED.show();
    } else {
      ledStrip[ledPixel] = CHSV(160, 255, sinBeat);
      FastLED.show();
    }
    return (ledPixel + 1);
  }
  return 0;
}

// Fill the stream and river LEDs with the colors
// for drought climate conditions.
void droughtConditions(){

  // // Saturation values: Blue 160, Green 96, Red 0
  // riverA_array[NUM_LEDS_RIVER_A] = CHSV(0, 160, sinBeat);
  // stream1_array[NUM_LEDS_STREAM_1] = CHSV(0, 160, sinBeat);
  // riverB_array[NUM_LEDS_RIVER_B] = CHSV(0, 96, sinBeat);
  // stream2_array[NUM_LEDS_STREAM_2] = CHSV(0, 0, sinBeat);
  // riverC_array[NUM_LEDS_RIVER_C] = CHSV(0, 0, sinBeat);
  // stream3_array[NUM_LEDS_STREAM_3] = CHSV(0, 0, sinBeat);

  fill_solid(stream1_array, NUM_LEDS_STREAM_1, CRGB::Blue);
  fill_solid(stream2_array, NUM_LEDS_STREAM_2, CRGB::Red);
  fill_solid(stream3_array, NUM_LEDS_STREAM_3, CRGB::Red);
  fill_solid(riverA_array, NUM_LEDS_RIVER_A, CRGB::Blue);
  fill_solid(riverB_array, NUM_LEDS_RIVER_B, CRGB::Green);
  fill_solid(riverC_array, NUM_LEDS_RIVER_C, CRGB::Red);
  // nscale8_video(stream3_array, NUM_LEDS_STREAM_3, 30);
  // nscale8_video(stream2_array, NUM_LEDS_STREAM_2, 30);
  // nscale8_video(stream1_array, NUM_LEDS_STREAM_1, 30);
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