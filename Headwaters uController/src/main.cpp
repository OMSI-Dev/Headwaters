#include <Arduino.h>
#include <FastLED.h>
#include <Timer.h>
#include <Adafruit_Thermal.h>
#include <testTube.h>
#include <Bounce2.h>
#include <OMSI_QR.h>

// #include <SoftwareSerial.h>
// #define TX_PIN 8
// #define RX_PIN 7
// SoftwareSerial mySerial(RX_PIN, TX_PIN);
// Adafruit_Thermal printer(&mySerial);

//uint16_t btnLockTime = 250; 

//setup print to hardware serial
//RX0 TX1
Adafruit_Thermal printer(&Serial2);

#define BTN_PIN1 0
Bounce2::Button button1 = Bounce2::Button();
//MoToTimer buttonLockoutTimer;

#define NUM_LEDS 14

// change to proper pin number
#define LED_PIN1 15

// Define the array of LEDs
CRGB ledStrip[NUM_LEDS];

void printerTest(){
    printer.setFont('A');
    printer.setSize('S');
    printer.println("This is font A in size S");
    printer.setSize('M');
    printer.println("This is font A in size M");
    printer.setSize('L');
    printer.println("This is font A in size L");

    printer.setFont('B');
    printer.setSize('S');
    printer.println("This is font B in size S");
    printer.setSize('M');
    printer.println("This is font B in size M");
    printer.setSize('L');
    printer.println("This is font B in size L");
    printer.feed(3);
}

void setup() {
  FastLED.addLeds<NEOPIXEL, LED_PIN1>(ledStrip, NUM_LEDS);

  FastLED.setBrightness(255);
  FastLED.show();

  button1.attach(BTN_PIN1, INPUT_PULLUP);
  // DEBOUNCE INTERVAL IN MILLISECONDS
  button1.interval(5);
  // INDICATE THAT THE LOW STATE CORRESPONDS TO PHYSICALLY PRESSING THE BUTTON
  button1.setPressedState(LOW); 

  Serial.begin(115200);
  Serial2.begin(9600);
  //mySerial.begin(9600);

  printer.begin();
  //ONLY used for debugging or talking to a computer
  //DELETE after completed
  while(!Serial);
}

void loop() {
  //printer.printBitmap(tubeWidth, tubeHeight, testTube);
  // must update button every loop
  button1.update();

  if(button1.pressed()){
    Serial.println("Button was pressed!");

    for(int i = 0; i < NUM_LEDS + 1; i++){
      fill_solid(ledStrip, i, CRGB::Blue);
      FastLED.show();
      delay(100);
    }
    for(int i = 0; i < NUM_LEDS + 1; i++){
      fill_solid(ledStrip, i, CRGB::Black);
      FastLED.show();
      delay(100);
    }

    printer.setSize('M');
    printer.println("Sampling Location 1");
    printer.println("Data at outlet of Stream 1");
    printer.setSize('S');
    printer.println("O numbers: is this supposed to be oxygen?");
    printer.println("Isotope count: like so many");

    //printer.printBitmap(QRWidth, QRHeight, OMSI_QR);
    printer.feed(5);
    }
}
