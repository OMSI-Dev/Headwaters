#include <ledStreams.h>
#include <loadButtons.h>
#include <printFunctions.h>

// Main file for Headwaters.
// Once everything is hooked up and turned on,
// press the mode button once to begin the program. 

//MoToTimer buttonLockoutTimer;
//uint16_t btnLockTime = 250;

// Climate condition modes:
// 0 = Normal
// 1 = High Snowpack
// 2 = Drought
uint8_t climateCondition = 3;

void setup() {
// Call custom function to handle the LED setup
  setupLED();

// Initialize LED on Teensy
  pinMode(13, OUTPUT);

// Call custom function to handle the buttons setup
// with error check
  if(!setupButtons()){
    Serial.println("Problem with setting up buttons.");
  }

  Serial.begin(115200);
  Serial1.begin(9600);


// Call custom function to setup the Thermal Printer
  setupPrinter();

// Keep commented out unless debugging or talking to a computer
  //while(!Serial);
}

void loop() {
// Call function to update all buttons each loop
  updateButtons();

// Blink LED on Teensy every second while running
  EVERY_N_SECONDS( 1 ){
    if(digitalRead(13) == HIGH){
      digitalWrite(13, LOW);
    }else{
      digitalWrite(13, HIGH);
    }
  }

// Check if the printer has paper each loop.
// If it doesn't, make all the rivers and streams red.
// This will also be triggered if the printer is not connected.
// ****** Doesn't work? (function itself says it might not work on all printers)
// if(!checkPrinterPaper()){
//   Serial.println("Printer needs paper.");
//   redStream();
// }

// Cycle through the climate conditions as mode button is pressed.
// Update LED colors based on the climate condition.
  if(modeButton.pressed()){
    turnOnButtonLEDs();
    if(climateCondition >= 2){
      climateCondition = 0;
      Serial.println("Climate Condition: Normal");
      normalConditionsLED();
    }else{
      climateCondition++;
      if(climateCondition == 1){
        Serial.println("Climate Conditions: High Snowpack");
        snowConditionsLED();
      }else if(climateCondition == 2){
        Serial.println("Climate Conditions: Dought");
        droughtConditionsLED();
      }
    }
  }

// When a button is pressed, all the buttons' LEDs shut off until
// the function to print is completed.
  if(stream1Button.pressed()){
    turnOffButtonLEDs();
    printStream(climateCondition, 1);
    //printStreamSerial(climateCondition, 1);
    turnOnButtonLEDs();
  }

  if(stream2Button.pressed()){
    turnOffButtonLEDs();
    printStream(climateCondition, 2);
    //printStreamSerial(climateCondition, 2);
    turnOnButtonLEDs();
  }

  if(stream3Button.pressed()){
    turnOffButtonLEDs();
    printStream(climateCondition, 3);
    //printStreamSerial(climateCondition, 3);
    turnOnButtonLEDs();
  }

  if(river1Button.pressed()){
    turnOffButtonLEDs();
    printRiver(climateCondition, 'A');
    //printRiverSerial(climateCondition, 'A');
    turnOnButtonLEDs();
  }

  if(river2Button.pressed()){
    turnOffButtonLEDs();
    printRiver(climateCondition, 'B');
    //printRiverSerial(climateCondition, 'B');
    turnOnButtonLEDs();
  }

  if(river3Button.pressed()){
    turnOffButtonLEDs();
    printRiver(climateCondition, 'C');
    //printRiverSerial(climateCondition, 'C');
    turnOnButtonLEDs();
  }

  if(precip1Button.pressed()){
    turnOffButtonLEDs();
    printPrecipitation(climateCondition, 1);
    //printPrecipitationSerial(climateCondition, 1);
    turnOnButtonLEDs();
  }

  if(precip2Button.pressed()){
    turnOffButtonLEDs();
    printPrecipitation(climateCondition, 2);
    //printPrecipitationSerial(climateCondition, 2);
    turnOnButtonLEDs();
  }

  if(precip3Button.pressed()){
    turnOffButtonLEDs();
    printPrecipitation(climateCondition, 3);
    //printPrecipitationSerial(climateCondition, 3);
    turnOnButtonLEDs();
  }
  //printQR(); 
}