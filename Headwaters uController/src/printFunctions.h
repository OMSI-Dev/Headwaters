#include <Arduino.h>
#include <Adafruit_Thermal.h>
#include <cmath>
#include <OMSI_QR.h>
#include <testTube.h>
#include <calicoTestTube.h>

// Calico September 25th, 2024
// Header file to store the print functions for
// the thermal printer. Includes a test, WR codes, 
// and the different climate conditions. 

void printerTest(Adafruit_Thermal &printer){
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

void printCurrentSample(Adafruit_Thermal &printer, uint16_t elv, uint8_t oxy){
    printer.setFont('B');
    printer.setSize('S');

    printer.print("Mean Watershed Elevation: ");
    printer.print(elv);
    printer.println();

    printer.print("Oxygen-18: ");
    printer.print(oxy);
    printer.println();
}

void printQR(Adafruit_Thermal &printer){
  printer.printBitmap(QRWidth, QRHeight, OMSI_QR);
  printer.feed(4);
}

void normalConditions(Adafruit_Thermal &printer, uint8_t strm, char rvr){
    printer.setFont('B');
    printer.setSize('S');
    printer.println("Climate Condition: Normal");
    if(strm == 1){
        printer.print("Stream Location: ");
        printer.print(strm);
        printer.println();
        printer.println("Landscape: Lava Flows");
        printCurrentSample(printer, 1200, 1);
    } else if(strm == 2){
        printer.print("Stream Location: ");
        printer.print(strm);
        printer.println();
        printer.println("Landscape: Earthflows");
        printCurrentSample(printer, 950, 4);
    } else if(strm == 3){
        printer.print("Stream Location: ");
        printer.print(strm);
        printer.println();
        printer.println("Landscape: Weathered Bedrock");
        printCurrentSample(printer, 700, 6);
    }

    if(rvr == 'A'){
        printer.print("River Location: ");
        printer.print(rvr);
        printer.println();
        printCurrentSample(printer, 0, 2);
    } else if(rvr == 'B'){
        printer.print("River Location: ");
        printer.print(rvr);
        printer.println();
        printCurrentSample(printer, 0, 3);
    } else if(rvr == 'C'){
        printer.print("River Location: ");
        printer.print(rvr);
        printer.println();
        printCurrentSample(printer, 0, 5);
    }
}

void snowConditions(Adafruit_Thermal &printer, uint8_t strm, char rvr){
    printer.setFont('B');
    printer.setSize('S');
    printer.println("Climate Condition: High Snowpack");
    if(strm == 1){
        printer.print("Stream Location: ");
        printer.print(strm);
        printer.println();
        printer.println("Landscape: Lava Flows");
        printCurrentSample(printer, 1200, 1);
    } else if(strm == 2){
        printer.print("Stream Location: ");
        printer.print(strm);
        printer.println();
        printer.println("Landscape: Earthflows");
        printCurrentSample(printer, 950, 3);
    } else if(strm == 3){
        printer.print("Stream Location: ");
        printer.print(strm);
        printer.println();
        printer.println("Landscape: Weathered Bedrock");
        printCurrentSample(printer, 700, 5);
    }

    if(rvr == 'A'){
        printer.print("River Location: ");
        printer.print(rvr);
        printer.println();
        printCurrentSample(printer, 0, 1);
    } else if(rvr == 'B'){
        printer.print("River Location: ");
        printer.print(rvr);
        printer.println();
        printCurrentSample(printer, 0, 3);
    } else if(rvr == 'C'){
        printer.print("River Location: ");
        printer.print(rvr);
        printer.println();
        printCurrentSample(printer, 0, 4);
    }
}

void droughtConditions(Adafruit_Thermal &printer, uint8_t strm, char rvr){
    printer.setFont('B');
    printer.setSize('S');
    printer.println("Climate Condition: Drought");
    if(strm == 1){
        printer.print("Stream Location: ");
        printer.print(strm);
        printer.println();
        printer.println("Landscape: Lava Flows");
        printCurrentSample(printer, 1200, 3);
    } else if(strm == 2){
        printer.print("Stream Location: ");
        printer.print(strm);
        printer.println();
        printer.println("Landscape: Earthflows");
        printCurrentSample(printer, 950, 6);
    } else if(strm == 3){
        printer.print("Stream Location: ");
        printer.print(strm);
        printer.println();
        printer.println("Landscape: Weathered Bedrock");
        printCurrentSample(printer, 700, 9);
    }

    if(rvr == 'A'){
        printer.print("River Location: ");
        printer.print(rvr);
        printer.println();
        printCurrentSample(printer, 0, 3);
    } else if(rvr == 'B'){
        printer.print("River Location: ");
        printer.print(rvr);
        printer.println();
        printCurrentSample(printer, 0, 5);
    } else if(rvr == 'C'){
        printer.print("River Location: ");
        printer.print(rvr);
        printer.println();
        printCurrentSample(printer, 0, 8);
    }
}