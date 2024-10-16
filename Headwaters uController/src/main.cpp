#include <printFunctions.h>
#include <ledModes.h>
#include <ledStreams.h>
#include <loadButtons.h>

//MoToTimer buttonLockoutTimer;
//uint16_t btnLockTime = 250;

// Climate condition modes
// 0 = Normal
// 1 = High Snowpack
// 2 = Drought
uint8_t climateCondition = 2;

void setup() {
// Call custom function to handle the LED setup
  setupLED();

// Call custom function to handle the buttons setup
// with error check
  if(!setupButtons()){
    Serial.println("Problem with setting up buttons.");
  }

  Serial.begin(115200);
  Serial2.begin(9600);


// Call custom function to setup the Thermal Printer
// And check if it has paper
  if(!setupPrinter()){
    Serial.println("Printer has no paper.");
  }

  //ONLY USED FOR DEBUGGING OR TALKING TO A COMPUTER
  //DELETE BEFORE FINAL
  while(!Serial);
}

void loop() {
// Call function to update all buttons each loop
  updateButtons();

// Check if the printer has paper each loop.
// If it doesn't, make all the rivers and streams red.
// if(!checkPrinterPaper()){
//   redStream();
// }

// Cycle through the climate conditions
// Update LED colors based on the climate condition
  if(modeButton.pressed()){
    if(climateCondition == 2){
      climateCondition = 0;
      Serial.println("Climate Condition: Normal");
      normalConditionsLED();
      //pacifica_loop(ledRing);
    }else{
      climateCondition++;
      if(climateCondition == 1){
        Serial.println("Climate Conditions: High Snowpack");
        snowConditionsLED();
        //snowpack(ledRing);
      } else if(climateCondition == 2){
        Serial.println("Climate Conditions: Dought");
        droughtConditionsLED();
        //drought_loop(ledRing);
      }
    }
  }

  if(stream1Button.pressed()){
    //printStream(climateCondition, 1);
    printStreamSerial(climateCondition, 1);
  }

  if(stream2Button.pressed()){
    //printStream(climateCondition, 2);
    printStreamSerial(climateCondition, 2);
  }

  if(stream3Button.pressed()){
    //printStream(climateCondition, 3);
    printStreamSerial(climateCondition, 3);
  }

  if(river1Button.pressed()){
    //printRiver(climateCondition, 'A');
    printRiverSerial(climateCondition, 'A');
  }

  if(river2Button.pressed()){
    //printRiver(climateCondition, 'B');
    printRiverSerial(climateCondition, 'B');
  }

  if(river3Button.pressed()){
    //printRiver(climateCondition, 'C');
    printRiverSerial(climateCondition, 'C');
  }

  if(precip1Button.pressed()){
    //printPrecipitation(climateCondition, 1);
    printPrecipitationSerial(climateCondition, 1);
  }

  if(precip2Button.pressed()){
    //printPrecipitation(climateCondition, 2);
    printPrecipitationSerial(climateCondition, 2);
  }

  if(precip3Button.pressed()){
    //printPrecipitation(climateCondition, 3);
    printPrecipitationSerial(climateCondition, 3);
  }
  // printQR();
}