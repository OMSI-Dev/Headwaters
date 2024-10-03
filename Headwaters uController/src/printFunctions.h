#include <Arduino.h>
#include <Adafruit_Thermal.h>
#include <cmath>
#include <OMSI_QR.h>
#include <testTube.h>
#include <calicoTestTube.h>
#include <deltaBMP.h>

// Calico created September 25th, 2024
// Header file to store the print functions for
// the thermal printer. Includes a test, WR codes, 
// and print functions for the rivers, streams, and precipitations. 

uint16_t streams[9][3] = {
    {0, 1200, 1}, {0, 1200, 4}, {0, 1200, 6},
    {1, 950, 1}, {1, 950, 3}, {1, 950, 5},
    {2, 700, 3}, {2, 700, 6}, {2, 700, 9}
};

uint8_t rivers[9][2] = {
    {0, 2}, {0, 3}, {0, 5},
    {1, 1}, {1, 3}, {1, 4},
    {2, 3}, {2, 5}, {2, 8}
};

uint16_t precipitations[9][3] = {
    {0, 400, 10}, {0, 400, 5}, {0, 400, 2},
    {1, 800, 9}, {1, 800, 4}, {1, 800, 1},
    {2, 1200, 12}, {2, 1200, 7}, {2, 1200, 4}
};

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

    if(elv != 0){
        printer.print("Mean Watershed Elevation: ");
        printer.print(elv);
        printer.println();
    }
 
    printer.println("Isotope Count: ");
    //printer.printBitmap(deltaWidth, deltaHeight, deltaBMP);
     printer.print("O_18: ");
     printer.print(oxy);
     printer.println();
}

void printQR(Adafruit_Thermal &printer){
  printer.printBitmap(QRWidth, QRHeight, OMSI_QR);
  printer.feed(4);
}

void printPrecipitation(Adafruit_Thermal &printer, uint8_t climate, uint8_t precip){
    printer.setFont('B');
    printer.setSize('S');
    printer.print("Precipitation Sample Site ");
    printer.print(precip);
    printer.println();

    switch(climate){
        case 0:
            printer.println("Climate Condition: Normal");
            break;
        case 1:
            printer.println("Climate Condition: High Snowpack");
            break;
        case 2:
            printer.println("Climate Condition: Drought");
            break;
    }
    printCurrentSample(printer, precipitations[(climate*2 + climate) + (precip-1)][1], precipitations[(climate*2 + climate) + (precip-1)][2]);
}

void printStream(Adafruit_Thermal &printer, uint8_t climate, uint8_t strm){
    printer.setFont('B');
    printer.setSize('S');
    printer.print("Stream Sample Site ");
    printer.print(strm);
    printer.println();

    switch(climate){
        case 0:
            printer.println("Climate Condition: Normal");
            break;
        case 1:
            printer.println("Climate Condition: High Snowpack");
            break;
        case 2:
            printer.println("Climate Condition: Drought");
            break;
    }

    switch(strm){
        case 1: 
            printer.println("Landscape: Lava Flows");
            break;
        case 2:
            printer.println("Landscape: Earthflows");
            break;
        case 3:
            printer.println("Landscape: Weathered Bedrock");
            break;
    }
    printCurrentSample(printer, streams[(climate*2 + climate) + (strm-1)][1], streams[(climate*2 + climate) + (strm-1)][2]);
}

void printRiver(Adafruit_Thermal &printer, uint8_t climate, char rvr){
    printer.setFont('B');
    printer.setSize('S');
    printer.print("River Sample Site ");
    printer.print(rvr);
    printer.println();

    switch(climate){
        case 0:
            printer.println("Climate Condition: Normal");
            break;
        case 1:
            printer.println("Climate Condition: High Snowpack");
            break;
        case 2:
            printer.println("Climate Condition: Drought");
            break;
    }

    uint8_t river = 0;
    if(rvr == 'A'){
        river = 1;
    } else if (rvr == 'B'){
        river = 2;
    } else if(rvr == 'C'){
        river = 3;
    }
    printCurrentSample(printer, 0, rivers[(climate*2 + climate) + (river-1)][1]);
}