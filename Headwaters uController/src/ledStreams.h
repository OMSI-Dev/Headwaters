#include <Arduino.h>
#include <FastLED.h>

// Calico September 26th, 2024
// Header file to keep the code that creates the streams
// in the LED strips.

void blueStream(CRGB *ledStrip, uint8_t NUM_LEDS_STRIP){
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

void greenStream(CRGB *ledStrip, uint8_t NUM_LEDS_STRIP){
    // create a blue "stream" on the LED strip 
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

void redStream(CRGB *ledStrip, uint8_t NUM_LEDS_STRIP){
    // create a blue "stream" on the LED strip 
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