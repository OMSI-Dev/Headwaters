#include <Arduino.h>
#include <Bounce2.h>

// Calico created October 3, 2024
// Defines and loads all ten buttons, plus the trigger.

uint8_t howLongToWait = 250;
uint16_t lastTimeItHappened = 0;
uint8_t howLongItsBeen;

// Define all pins (change where needed).
#define MODE_PIN 2
#define STREAM1_PIN 4
#define STREAM2_PIN 6
#define STREAM3_PIN 8
#define RIVER1_PIN 10
#define RIVER2_PIN 12
#define RIVER3_PIN 16
#define PRECIP1_PIN 17
#define PRECIP2_PIN 19
#define PRECIP3_PIN 21
#define FACILITATOR_PIN 14

// Define all pins for the LED rings on the buttons.
#define MODE_LED 3
#define STREAM_1_LED 5
#define STREAM_2_LED 7
#define STREAM_3_LED 9
#define RIVER_A_LED 11
#define RIVER_B_LED 13
#define RIVER_C_LED 15
#define PRECIP_1_LED 18
#define PRECIP_2_LED 20
#define PRECIP_3_LED 22

// Create all button objects.
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
Bounce2::Button facilitatorButton = Bounce2::Button();

bool setupButtons(){
// Attach each button object to it's correct pin.
  modeButton.attach(MODE_PIN, INPUT_PULLUP);
  stream1Button.attach(STREAM1_PIN, INPUT_PULLUP);
  stream2Button.attach(STREAM2_PIN, INPUT_PULLUP);
  stream3Button.attach(STREAM3_PIN, INPUT_PULLUP);
  river1Button.attach(RIVER1_PIN, INPUT_PULLUP);
  river2Button.attach(RIVER2_PIN, INPUT_PULLUP);
  river3Button.attach(RIVER3_PIN, INPUT_PULLUP);
  precip1Button.attach(PRECIP1_PIN, INPUT_PULLUP);
  precip2Button.attach(PRECIP2_PIN, INPUT_PULLUP);
  precip3Button.attach(PRECIP3_PIN, INPUT_PULLUP);
  facilitatorButton.attach(FACILITATOR_PIN, INPUT_PULLUP);

// Debounce interval in milliseconds.
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
  facilitatorButton.interval(5);

// Indicate that the low state corresponds to phsyically pressing the button.
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
  facilitatorButton.setPressedState(LOW);

// Setting the digital pins for the LED rings on the buttons
  pinMode(MODE_LED, OUTPUT);
  pinMode(STREAM_1_LED, OUTPUT);
  pinMode(STREAM_2_LED, OUTPUT);
  pinMode(STREAM_3_LED, OUTPUT);
  pinMode(RIVER_A_LED, OUTPUT);
  pinMode(RIVER_B_LED, OUTPUT);
  pinMode(RIVER_C_LED, OUTPUT);
  pinMode(PRECIP_1_LED, OUTPUT);
  pinMode(PRECIP_2_LED, OUTPUT);
  pinMode(PRECIP_3_LED, OUTPUT);

// Check that pins got correctly attached.
  if(modeButton.getPin() == MODE_PIN &&
    stream1Button.getPin() == STREAM1_PIN &&
    stream2Button.getPin() == STREAM2_PIN &&
    stream3Button.getPin() == STREAM3_PIN &&
    river1Button.getPin() == RIVER1_PIN &&
    river2Button.getPin() == RIVER2_PIN &&
    river3Button.getPin() == RIVER3_PIN &&
    precip1Button.getPin() == PRECIP1_PIN &&
    precip2Button.getPin() == PRECIP2_PIN &&
    precip3Button.getPin() == PRECIP3_PIN &&
    facilitatorButton.getPin() == FACILITATOR_PIN)
  {
    return true;
  }
  return false;
}

// Function to update the buttons.
// Should be called at the beginning of each loop.
void updateButtons(){
  modeButton.update();
  stream1Button.update();
  stream2Button.update();
  stream3Button.update();
  river1Button.update();
  river2Button.update();
  river3Button.update();
  precip1Button.update();
  precip2Button.update();
  precip3Button.update();
  facilitatorButton.update();
}

void turnOnButtonLEDs(){
  digitalWrite(MODE_LED, HIGH);
  digitalWrite(STREAM_1_LED, HIGH);
  digitalWrite(STREAM_2_LED, HIGH);
  digitalWrite(STREAM_3_LED, HIGH);
  digitalWrite(RIVER_A_LED, HIGH);
  digitalWrite(RIVER_B_LED, HIGH);
  digitalWrite(RIVER_C_LED, HIGH);
  digitalWrite(PRECIP_1_LED, HIGH);
  digitalWrite(PRECIP_2_LED, HIGH);
  digitalWrite(PRECIP_3_LED, HIGH);
}

void turnOffButtonLEDs(){
  digitalWrite(MODE_LED, LOW);
  digitalWrite(STREAM_1_LED, LOW);
  digitalWrite(STREAM_2_LED, LOW);
  digitalWrite(STREAM_3_LED, LOW);
  digitalWrite(RIVER_A_LED, LOW);
  digitalWrite(RIVER_B_LED, LOW);
  digitalWrite(RIVER_C_LED, LOW);
  digitalWrite(PRECIP_1_LED, LOW);
  digitalWrite(PRECIP_2_LED, LOW);
  digitalWrite(PRECIP_3_LED, LOW);
}

void fadeButtons(){
  howLongItsBeen = millis() - lastTimeItHappened;
  if( howLongItsBeen >= howLongToWait){
    // Fade buttons
    lastTimeItHappened = millis();
  }
}