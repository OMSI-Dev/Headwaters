#include <Arduino.h>
#include <Bounce2.h>

// Calico created October 3, 2024
// Defines and loads all 9 buttons

#define MODE_PIN 0
#define STREAM1_PIN 1
#define STREAM2_PIN 2
#define STREAM3_PIN 3
#define RIVER1_PIN 4
#define RIVER2_PIN 5
#define RIVER3_PIN 6
#define PRECIP1_PIN 9
#define PRECIP2_PIN 10
#define PRECIP3_PIN 11
Bounce2::Button modeButton = Bounce2::Button();
Bounce2::Button stream1Button = Bounce2::Button();
Bounce2::Button stream2Button = Bounce2::Button();
Bounce2::Button stream3Button = Bounce2::Button();
Bounce2::Button river1Button = Bounce2::Button();
Bounce2::Button river2Button = Bounce2::Button();
Bounce2::Button river3Button = Bounce2::Button();
Bounce2::Button precip1Button = Bounce2::Button();
Bounce2::Button precip2Button = Bounce2::Button();
Bounce2::Button precip3Button = Bounce2::Button();

void setupButtons(){
  modeButton.attach(MODE_PIN, INPUT_PULLUP);
  stream1Button.attach(STREAM1_PIN, INPUT_PULLUP);
  stream2Button.attach(STREAM2_PIN, INPUT_PULLUP);
  stream3Button.attach(STREAM3_PIN, INPUT_PULLUP);
  river1Button.attach(RIVER1_PIN, INPUT_PULLUP);
  river2Button.attach(RIVER2_PIN, INPUT_PULLUP);
  river1Button.attach(RIVER3_PIN, INPUT_PULLUP);
  precip1Button.attach(PRECIP1_PIN, INPUT_PULLUP);
  precip2Button.attach(PRECIP2_PIN, INPUT_PULLUP);
  precip3Button.attach(PRECIP3_PIN, INPUT_PULLUP);
  // debounce interval in milliseconds
  modeButton.interval(5);
  stream1Button.interval(5);
  stream2Button.interval(5);
  stream3Button.interval(5);
  river1Button.interval(5);
  river2Button.interval(5);
  river3Button.interval(5);
  precip1Button.interval(5);
  precip2Button.interval(5);
  precip3Button.interval(5);
  // indicate that the low state corresponds to phsyically pressing the button
  modeButton.setPressedState(LOW); 
  stream1Button.setPressedState(LOW);
  stream2Button.setPressedState(LOW);
  stream3Button.setPressedState(LOW);
  river1Button.setPressedState(LOW);
  river2Button.setPressedState(LOW);
  river3Button.setPressedState(LOW);
  precip1Button.setPressedState(LOW);
  precip2Button.setPressedState(LOW);
  precip3Button.setPressedState(LOW);
}