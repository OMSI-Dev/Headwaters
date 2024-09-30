#include <Arduino.h>
#include <FastLED.h>

// Calico September 26th, 2024
// Header file to keep the code to change the
// LED ring based on which climate condition
// mode it is in.
// Normal conditions has soft, breathing earth colors blue and green.
// Snowpack conditions have a snowflake.
// Drought condition has just red fill now.
// Want to make the drought condition breathe softly,
// like a heat mirage

#define NUM_LEDS_RING 31

// Add one layer of waves into the led array
void pacifica_one_layer( CRGBPalette16& p, uint16_t cistart, uint16_t wavescale, uint8_t bri, uint16_t ioff, CRGB *ledRing)
{
  uint16_t ci = cistart;
  uint16_t waveangle = ioff;
  uint16_t wavescale_half = (wavescale / 2) + 20;
  for( uint16_t i = 0; i < NUM_LEDS_RING; i++) {
    waveangle += 250;
    uint16_t s16 = sin16( waveangle ) + 32768;
    uint16_t cs = scale16( s16 , wavescale_half ) + wavescale_half;
    ci += cs;
    uint16_t sindex16 = sin16( ci) + 32768;
    uint8_t sindex8 = scale16( sindex16, 240);
    CRGB c = ColorFromPalette( p, sindex8, bri, LINEARBLEND);
    ledRing[i] += c;
  }
}

// Add extra 'white' to areas where the four layers of light have lined up brightly
void pacifica_add_whitecaps(CRGB *ledRing)
{
  uint8_t basethreshold = beatsin8( 9, 55, 65);
  uint8_t wave = beat8( 7 );
  
  for( uint16_t i = 0; i < NUM_LEDS_RING; i++) {
    uint8_t threshold = scale8( sin8( wave), 20) + basethreshold;
    wave += 7;
    uint8_t l = ledRing[i].getAverageLight();
    if( l > threshold) {
      uint8_t overage = l - threshold;
      uint8_t overage2 = qadd8( overage, overage);
      ledRing[i] += CRGB( overage, overage2, qadd8( overage2, overage2));
    }
  }
}

// Deepen the blues and greens
void pacifica_deepen_colors(CRGB *ledRing)
{
  for( uint16_t i = 0; i < NUM_LEDS_RING; i++) {
    ledRing[i].blue = scale8( ledRing[i].blue,  145); 
    ledRing[i].green= scale8( ledRing[i].green, 200); 
    ledRing[i] |= CRGB( 2, 5, 7);
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


void pacifica_loop(CRGB *ledRing)
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
  fill_solid(ledRing, NUM_LEDS_RING, CRGB( 2, 6, 10));

  // Render each of four layers, with different scales and speeds, that vary over time
  pacifica_one_layer( pacifica_palette_1, sCIStart1, beatsin16( 3, 11 * 256, 14 * 256), beatsin8( 10, 70, 130), 0-beat16( 301), ledRing);
  pacifica_one_layer( pacifica_palette_2, sCIStart2, beatsin16( 4,  6 * 256,  9 * 256), beatsin8( 17, 40,  80), beat16( 401), ledRing);
  pacifica_one_layer( pacifica_palette_3, sCIStart3, 6 * 256, beatsin8( 9, 10,38), 0-beat16(503), ledRing);
  pacifica_one_layer( pacifica_palette_3, sCIStart4, 5 * 256, beatsin8( 8, 10,28), beat16(601), ledRing);

  // Add brighter 'whitecaps' where the waves lines up more
  pacifica_add_whitecaps(ledRing);

  // Deepen the blues and greens a bit
  pacifica_deepen_colors(ledRing);
  FastLED.show();
}

void snowpack(CRGB *ledRing){
    ledRing[0] = CRGB::Blue;
    ledRing[2] = CRGB::Blue;
    ledRing[4] = CRGB::Blue;
    ledRing[6] = CRGB::Blue;
    ledRing[8] = CRGB::Blue;
    ledRing[10] = CRGB::Blue;
    ledRing[12] = CRGB::Blue;
    ledRing[14] = CRGB::Blue;
    ledRing[16] = CRGB::Blue;
    ledRing[17] = CRGB::Blue;
    ledRing[19] = CRGB::Blue;
    ledRing[20] = CRGB::Blue;
    ledRing[21] = CRGB::Blue;
    ledRing[22] = CRGB::Blue;
    ledRing[23] = CRGB::Blue;
    ledRing[25] = CRGB::Blue;
    ledRing[26] = CRGB::Blue;
    ledRing[28] = CRGB::Blue;
    ledRing[30] = CRGB::Blue;
    FastLED.show();
}


// Add one layer of waves into the led array
void drought_one_layer( CRGBPalette16& p, uint16_t cistart, uint16_t wavescale, uint8_t bri, uint16_t ioff, CRGB *ledRing)
{
  uint16_t ci = cistart;
  uint16_t waveangle = ioff;
  uint16_t wavescale_half = (wavescale / 2) + 20;
  for( uint16_t i = 0; i < NUM_LEDS_RING; i++) {
    waveangle += 250;
    uint16_t s16 = sin16( waveangle ) + 32768;
    uint16_t cs = scale16( s16 , wavescale_half ) + wavescale_half;
    ci += cs;
    uint16_t sindex16 = sin16( ci) + 32768;
    uint8_t sindex8 = scale16( sindex16, 240);
    CRGB c = ColorFromPalette( p, sindex8, bri, LINEARBLEND);
    ledRing[i] += c;
  }
}

// Add extra 'white' to areas where the four layers of light have lined up brightly
void drought_add_whitecaps(CRGB *ledRing)
{
  uint8_t basethreshold = beatsin8( 9, 55, 65);
  uint8_t wave = beat8( 7 );
  
  for( uint16_t i = 0; i < NUM_LEDS_RING; i++) {
    uint8_t threshold = scale8( sin8( wave), 20) + basethreshold;
    wave += 7;
    uint8_t l = ledRing[i].getAverageLight();
    if( l > threshold) {
      uint8_t overage = l - threshold;
      uint8_t overage2 = qadd8( overage, overage);
      ledRing[i] += CRGB( overage, overage2, qadd8( overage2, overage2));
    }
  }
}

// Deepen the reds and greens
void drought_deepen_colors(CRGB *ledRing)
{
  for( uint16_t i = 0; i < NUM_LEDS_RING; i++) {
    ledRing[i].green = scale8( ledRing[i].green,  145); 
    ledRing[i].red= scale8( ledRing[i].red, 200); 
    ledRing[i] |= CRGB( 7, 1, 0);
  }
}

CRGBPalette16 drought_palette_1 = 
    { 0x000507, 0x000409, 0x00030B, 0x00030D, 0x000210, 0x000212, 0x000114, 0x000117, 
      0x000019, 0x00001C, 0x000026, 0x000031, 0x00003B, 0x000046, 0xBA0000, 0xFFBF00 };
CRGBPalette16 drought_palette_2 = 
    { 0x000507, 0x000409, 0x00030B, 0x00030D, 0x000210, 0x000212, 0x000114, 0x000117, 
      0x000019, 0x00001C, 0x000026, 0x000031, 0x00003B, 0x000046, 0x990000, 0xFF9900 };
CRGBPalette16 drought_palette_3 = 
    { 0x000208, 0x00030E, 0x000514, 0x00061A, 0x000820, 0x000927, 0x000B2D, 0x000C33, 
      0x000E39, 0x001040, 0x001450, 0x001860, 0x001C70, 0x002080, 0xFFF00, 0xFF0000 };


void drought_loop(CRGB *ledRing)
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
  fill_solid(ledRing, NUM_LEDS_RING, CRGB( 47, 13, 0));

  // Render each of four layers, with different scales and speeds, that vary over time
  drought_one_layer(drought_palette_1, sCIStart1, beatsin16( 3, 11 * 256, 14 * 256), beatsin8( 10, 70, 130), 0-beat16( 301), ledRing);
  drought_one_layer(drought_palette_2, sCIStart2, beatsin16( 4,  6 * 256,  9 * 256), beatsin8( 17, 40,  80), beat16( 401), ledRing);
  drought_one_layer(drought_palette_3, sCIStart3, 6 * 256, beatsin8( 9, 10,38), 0-beat16(503), ledRing);
  drought_one_layer(drought_palette_3, sCIStart4, 5 * 256, beatsin8( 8, 10,28), beat16(601), ledRing);

  // Add brighter 'whitecaps' where the waves lines up more
  drought_add_whitecaps(ledRing);

  // Deepen the blues and greens a bit
  drought_deepen_colors(ledRing);
  FastLED.show();
}

void drought(CRGB *ledRing){
  fill_solid(ledRing, NUM_LEDS_RING + 1, CRGB::Red);
  FastLED.show();
}
