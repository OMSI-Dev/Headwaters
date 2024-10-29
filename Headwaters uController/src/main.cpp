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
// if(!checkPrinterPaper()){
//   redStream();
// }

// Cycle through the climate conditions as mode button is pressed.
// Update LED colors based on the climate condition.
  if(modeButton.pressed()){
    if(climateCondition >= 2){
      climateCondition = 0;
      Serial.println("Climate Condition: Normal");
      //normalConditionsLED();
    }else{
      climateCondition++;
      if(climateCondition == 1){
        Serial.println("Climate Conditions: High Snowpack");
        //snowConditionsLED();
      }else if(climateCondition == 2){
        Serial.println("Climate Conditions: Dought");
        //droughtConditionsLED();
      }
    }
  }

  if(stream1Button.pressed()){
    printStream(climateCondition, 1);
    //printStreamSerial(climateCondition, 1);
  }

  if(stream2Button.pressed()){
    printStream(climateCondition, 2);
    //printStreamSerial(climateCondition, 2);
  }

  if(stream3Button.pressed()){
    printStream(climateCondition, 3);
    //printStreamSerial(climateCondition, 3);
  }

  if(river1Button.pressed()){
    printRiver(climateCondition, 'A');
    //printRiverSerial(climateCondition, 'A');
  }

  if(river2Button.pressed()){
    printRiver(climateCondition, 'B');
    //printRiverSerial(climateCondition, 'B');
  }

  if(river3Button.pressed()){
    printRiver(climateCondition, 'C');
    //printRiverSerial(climateCondition, 'C');
  }

  if(precip1Button.pressed()){
    printPrecipitation(climateCondition, 1);
    //printPrecipitationSerial(climateCondition, 1);
  }

  if(precip2Button.pressed()){
    printPrecipitation(climateCondition, 2);
    //printPrecipitationSerial(climateCondition, 2);
  }

  if(precip3Button.pressed()){
    printPrecipitation(climateCondition, 3);
    //printPrecipitationSerial(climateCondition, 3);
  }
  //printQR();
}