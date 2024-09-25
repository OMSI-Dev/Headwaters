#include <Arduino.h>
#include <FastLED.h>
#include <Timer.h>
#include <Adafruit_Thermal.h>
#include <testTube.h>
#include <Bounce2.h>
#include <OMSI_QR.h>

//uint16_t btnLockTime = 250; 

// setup print to hardware serial
// RX0 TX1
Adafruit_Thermal printer(&Serial2);

#define BTN_PIN1 0
Bounce2::Button button1 = Bounce2::Button();
//MoToTimer buttonLockoutTimer;

#define NUM_LEDS 14
#define LED_PIN1 15

// define the array of LEDs
CRGB ledStrip[NUM_LEDS];

void printerTest(){
  // just a function to print the different font and size options
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

void printCurrentSample(int location, int stream, float isoCount, float temp, float dissolvedOxy){
    printer.setFont('B');
    printer.setSize('s');

    printer.print("Sample Location: ");
    printer.print(location);
    printer.println();

    printer.print("Stream: ");
    printer.print(stream);
    printer.println();

    printer.print("Isotope count: ");
    printer.print(isoCount);
    printer.println();

    printer.print("Temperature: ");
    printer.print(temp);
    printer.println();

    printer.print("Oxygen dissolved: ");
    printer.print(dissolvedOxy);
    printer.println();
}

void printQR(){
  printer.printBitmap(QRWidth, QRHeight, OMSI_QR);
  printer.feed(4);
}

void setup() {
  FastLED.addLeds<NEOPIXEL, LED_PIN1>(ledStrip, NUM_LEDS);

  FastLED.setBrightness(255);
  FastLED.show();

  button1.attach(BTN_PIN1, INPUT_PULLUP);
  // debounce interval in milliseconds
  button1.interval(5);
  // indicate that the low state corresponds to phsyically pressing the button
  button1.setPressedState(LOW); 

  Serial.begin(115200);
  Serial2.begin(9600);

  printer.begin();
  //ONLY USED FOR DEBUGGING OR TALKING TO A COMPUTER
  //DELETE BEFORE FINAL
  while(!Serial);
}

void loop() {
  //printer.printBitmap(tubeWidth, tubeHeight, testTube);
  button1.update();

  if(button1.pressed()){
    // create a blue "stream" on the LED strip 
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

    printCurrentSample(1, 1, 20.7, 72, 7);
    printQR();
  }
}