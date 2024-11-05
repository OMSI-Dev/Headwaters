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
#define NUM_LEDS_RIVER_A 22  // pixels 0-21
#define NUM_LEDS_RIVER_B 31  // pixels 22-52
#define NUM_LEDS_RIVER_C 33  // pixels 53-85
#define NUM_LEDS_TOTAL (NUM_LEDS_STREAM_1 + NUM_LEDS_STREAM_2 + NUM_LEDS_STREAM_3 + NUM_LEDS_RIVER_A + NUM_LEDS_RIVER_B + NUM_LEDS_RIVER_C)

// Create the array of LEDs for the strip.
CRGB ledStrip[NUM_LEDS_TOTAL];

// Setups the LED strip.
void setupLED(){
  FastLED.addLeds<NEOPIXEL, LED_STRIP_PIN>(ledStrip, NUM_LEDS_TOTAL);
  
  FastLED.setBrightness(255);
  FastLED.show();
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
// for each stream and river under normal climate conditions.
// Recursively, with no for loop.
void normalConditionsLEDRecursive(uint8_t i){
  if(i >= NUM_LEDS_TOTAL){
    return;
  }
  if(i < (NUM_LEDS_RIVER_A + NUM_LEDS_RIVER_B)){
    ledStrip[i] = CRGB::Blue;
    FastLED.show();
    normalConditionsLEDRecursive(i+1);
  }
  if((NUM_LEDS_RIVER_A + NUM_LEDS_RIVER_B) <= i && i < (NUM_LEDS_RIVER_A + NUM_LEDS_RIVER_B + NUM_LEDS_RIVER_C + NUM_LEDS_STREAM_3 + NUM_LEDS_STREAM_2)){
    ledStrip[i] = CRGB::Green;
    FastLED.show();
    normalConditionsLEDRecursive(i+1);
  }
  if((NUM_LEDS_RIVER_A + NUM_LEDS_RIVER_B + NUM_LEDS_RIVER_C + NUM_LEDS_STREAM_3 + NUM_LEDS_STREAM_2) <= i && i < NUM_LEDS_TOTAL){
    ledStrip[i] = CRGB::Blue;
    FastLED.show();
    normalConditionsLEDRecursive(i+1);
  }
}

// Break up the LED strip to set the required colors 
// for each stream and river under high snowpack climate conditions.
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
// for each stream and river under high snowpack climate conditions.
// Recursively, with no for loop.
void snowConditionsLEDRecursive(uint8_t i){
  if(i >= NUM_LEDS_TOTAL){
    return;
  }
  if(i < (NUM_LEDS_RIVER_A + NUM_LEDS_RIVER_B + NUM_LEDS_RIVER_C)){
    ledStrip[i] = CRGB::Blue;
    FastLED.show();
    snowConditionsLEDRecursive(i+1);
  }
  if((NUM_LEDS_RIVER_A + NUM_LEDS_RIVER_B + NUM_LEDS_RIVER_C) <= i && i < (NUM_LEDS_RIVER_A + NUM_LEDS_RIVER_B + NUM_LEDS_RIVER_C + NUM_LEDS_STREAM_3)){
    ledStrip[i] = CRGB::Green;
    FastLED.show();
    snowConditionsLEDRecursive(i+1);
  }
  if((NUM_LEDS_RIVER_A + NUM_LEDS_RIVER_B + NUM_LEDS_RIVER_C + NUM_LEDS_STREAM_3) <= i && i < NUM_LEDS_TOTAL){
    ledStrip[i] = CRGB::Blue;
    FastLED.show();
    snowConditionsLEDRecursive(i+1);
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

// Break up the LED strip to set the required colors 
// for each stream and river under drought climate conditions.
// Recursively, with no for loop.
void droughtConditionsLEDRecursive(uint8_t i){
  if(i >= NUM_LEDS_TOTAL){
    return;
  }
  if(i < NUM_LEDS_RIVER_A){
    ledStrip[i] = CRGB::Blue;
    FastLED.show();
    droughtConditionsLEDRecursive(i+1);
  }
  if(NUM_LEDS_RIVER_A <= i && i < (NUM_LEDS_RIVER_A + NUM_LEDS_RIVER_B)){
    ledStrip[i] = CRGB::Green;
    FastLED.show();
    droughtConditionsLEDRecursive(i+1);
  }
  if((NUM_LEDS_RIVER_A + NUM_LEDS_RIVER_B) <= i && i < (NUM_LEDS_RIVER_A + NUM_LEDS_RIVER_B + NUM_LEDS_RIVER_C + NUM_LEDS_STREAM_3 + NUM_LEDS_STREAM_2)){
    ledStrip[i] = CRGB::Red;
    FastLED.show();
    droughtConditionsLEDRecursive(i+1);
  }
  if((NUM_LEDS_RIVER_A + NUM_LEDS_RIVER_B + NUM_LEDS_RIVER_C + NUM_LEDS_STREAM_3 + NUM_LEDS_STREAM_2) <= i && i < NUM_LEDS_TOTAL){
    ledStrip[i] = CRGB::Blue;
    FastLED.show();
    droughtConditionsLEDRecursive(i+1);
  }
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

// Add one layer of waves into the led array
void pacifica_one_layer( CRGBPalette16& p, uint16_t cistart, uint16_t wavescale, uint8_t bri, uint16_t ioff)
{
  uint16_t ci = cistart;
  uint16_t waveangle = ioff;
  uint16_t wavescale_half = (wavescale / 2) + 20;
  for( uint16_t i = 0; i < NUM_LEDS_TOTAL; i++) {
    waveangle += 250;
    uint16_t s16 = sin16( waveangle ) + 32768;
    uint16_t cs = scale16( s16 , wavescale_half ) + wavescale_half;
    ci += cs;
    uint16_t sindex16 = sin16( ci) + 32768;
    uint8_t sindex8 = scale16( sindex16, 240);
    CRGB c = ColorFromPalette( p, sindex8, bri, LINEARBLEND);
    ledStrip[i] += c;
  }
}

// Add extra 'white' to areas where the four layers of light have lined up brightly
void pacifica_add_whitecaps()
{
  uint8_t basethreshold = beatsin8( 9, 55, 65);
  uint8_t wave = beat8( 7 );
  
  for( uint16_t i = 0; i < NUM_LEDS_TOTAL; i++) {
    uint8_t threshold = scale8( sin8( wave), 20) + basethreshold;
    wave += 7;
    uint8_t l = ledStrip[i].getAverageLight();
    if( l > threshold) {
      uint8_t overage = l - threshold;
      uint8_t overage2 = qadd8( overage, overage);
      ledStrip[i] += CRGB( overage, overage2, qadd8( overage2, overage2));
    }
  }
}

// Deepen the blues and greens
void pacifica_deepen_colors()
{
  for( uint16_t i = 0; i < NUM_LEDS_TOTAL; i++) {
    ledStrip[i].blue = scale8( ledStrip[i].blue,  145); 
    ledStrip[i].green= scale8( ledStrip[i].green, 200); 
    ledStrip[i] |= CRGB( 2, 5, 7);
  }
}

CRGBPalette16 pacifica_palette_1 = 
    { 0x000507, 0x000409, 0x00030B, 0x00030D, 0x000210, 0x000212, 0x000114, 0x000117, 
      0x000019, 0x00001C, 0x000026, 0x000031, 0x00003B, 0x000046, 0x14554B, 0x28AA50 };
CRGBPalette16 pacifica_palette_2 = 
    { 0x000507, 0x000409, 0x00030B, 0x00030D, 0x000210, 0x000212, 0x000114, 0x000117, 
      0x000019, 0x00001C, 0x000026, 0x000031, 0x00003B, 0x000046, 0x0C5F52, 0x19BE5F };
CRGBPalette16 pacifica_palette_3 = 
    { 0x000208, 0x00030E, 0x000514, 0x00061A, 0x000820, 0x000927, 0x000B2D, 0x000C33, 
      0x000E39, 0x001040, 0x001450, 0x001860, 0x001C70, 0x002080, 0x1040BF, 0x2060FF };


void pacifica_loop()
{
  // Increment the four "color index start" counters, one for each wave layer.
  // Each is incremented at a different speed, and the speeds vary over time.
  static uint16_t sCIStart1, sCIStart2, sCIStart3, sCIStart4;
  static uint32_t sLastms = 0;
  uint32_t ms = GET_MILLIS();
  uint32_t deltams = ms - sLastms;
  sLastms = ms;
  uint16_t speedfactor1 = beatsin16(3, 179, 269);
  uint16_t speedfactor2 = beatsin16(4, 179, 269);
  uint32_t deltams1 = (deltams * speedfactor1) / 256;
  uint32_t deltams2 = (deltams * speedfactor2) / 256;
  uint32_t deltams21 = (deltams1 + deltams2) / 2;
  sCIStart1 += (deltams1 * beatsin88(1011,10,13));
  sCIStart2 -= (deltams21 * beatsin88(777,8,11));
  sCIStart3 -= (deltams1 * beatsin88(501,5,7));
  sCIStart4 -= (deltams2 * beatsin88(257,4,6));

  // Clear out the LED array to a dim background blue-green
  fill_solid(ledStrip, NUM_LEDS_TOTAL, CRGB( 2, 6, 10));

  // Render each of four layers, with different scales and speeds, that vary over time
  pacifica_one_layer( pacifica_palette_1, sCIStart1, beatsin16( 3, 11 * 256, 14 * 256), beatsin8( 10, 70, 130), 0-beat16( 301));
  pacifica_one_layer( pacifica_palette_2, sCIStart2, beatsin16( 4,  6 * 256,  9 * 256), beatsin8( 17, 40,  80), beat16( 401));
  pacifica_one_layer( pacifica_palette_3, sCIStart3, 6 * 256, beatsin8( 9, 10,38), 0-beat16(503));
  pacifica_one_layer( pacifica_palette_3, sCIStart4, 5 * 256, beatsin8( 8, 10,28), beat16(601));

  // Add brighter 'whitecaps' where the waves lines up more
  pacifica_add_whitecaps();

  // Deepen the blues and greens a bit
  pacifica_deepen_colors();
  FastLED.show();
}