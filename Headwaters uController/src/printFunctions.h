#include <Arduino.h>
#include <Adafruit_Thermal.h>
#include <cmath>
#include <OMSI_QR.h>
#include <testTube.h>
#include <calicoTestTube.h>
#include <deltaBMP.h>

// Calico created September 25th, 2024
// Store the print functions for the thermal
// printer. Includes a test, WR codes, and 
// print functions for the rivers, streams, and precipitations. 

// Multidimensional arrays to hold the data for streams, rivers, and precipitations

// Streams: 
// Row 1 is Stream 1, 2, and 3 under normal conditions (0)
// Row 2 is Stream 1, 2, and 3 under snowpack conditions (1)
// Row 3 is Stream 1, 2, and 3 under drought conditions (2)
// {climate condition, mean watershed elevation, isotope oxygen_18 levels}
uint16_t streams[9][3] = {
    {0, 1200, 1}, {0, 950, 4}, {0, 700, 6},
    {1, 1200, 1}, {1, 950, 3}, {1, 700, 5},
    {2, 1200, 3}, {2, 950, 6}, {2, 700, 9}
};

// Rivers: 
// Row 1 is River A, B, and C under normal conditions (0)
// Row 2 is River A, B, and C under snowpack conditions (1)
// Row 3 is River A, B, and C under drought conditions (2)
// {climate condition, mean watershed elevation, isotope oxygen_18 levels}
uint8_t rivers[9][3] = {
    {0, 1050, 2}, {0, 900, 3}, {0, 750, 5},
    {1, 1050, 1}, {1, 900, 3}, {1, 750, 4},
    {2, 1050, 3}, {2, 900, 5}, {2, 750, 8}
};

// Precipitation: 
// Row 1 is Precipitation 1, 2, and 3 under normal conditions (0)
// Row 2 is Precipitation 1, 2, and 3 under snowpack conditions (1)
// Row 3 is Precipitation 1, 2, and 3 under drought conditions (2)
// {climate condition, mean watershed elevation, isotope oxygen_18 levels}
uint16_t precipitations[9][3] = {
    {0, 400, 10}, {0, 800, 5}, {0, 1200, 2},
    {1, 400, 9}, {1, 800, 4}, {1, 1200, 1},
    {2, 400, 12}, {2, 800, 7}, {2, 1200, 4}
};

// Print different font and size options
void printerTest(Adafruit_Thermal &printer){
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

// Print sample with elevation and isotope levels
void printCurrentSample(Adafruit_Thermal &printer, uint16_t elv, uint8_t oxy){
    printer.setFont('B');
    printer.setSize('S');

    printer.print("Mean Watershed Elevation: ");
    printer.print(elv);
    printer.print('M');
    printer.println();
 
    printer.println("Isotope Count: ");
    printer.print("O_18: ");
    printer.print(oxy);
    printer.println();
}

// Print OMSI QR code
void printQR(Adafruit_Thermal &printer){
  printer.printBitmap(QRWidth, QRHeight, OMSI_QR);
  printer.feed(4);
}

// Print a specific precipitation site under current climate condition
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

// Print a specific stream under current climate condition
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

// Print a specific river under current climate condition
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

    printCurrentSample(printer, rivers[(climate*2 + climate) + (river-1)][1], rivers[(climate*2 + climate) + (river-1)][2]);
}

// Functions for testing, print to Serial instead of Thermal Printer

// Output to Serial sample with elevation and isotope levels
void printCurrentSampleSerial(uint16_t elv, uint8_t oxy){
    Serial.print("Mean Watershed Elevation: ");
    Serial.print(elv);
    Serial.print('M');
    Serial.println();
 
    Serial.println("Isotope Count: ");
    Serial.print("O_18: ");
    Serial.print(oxy);
    Serial.println();
}

// Output to Serial a specific precipitation site under current climate condition
void printPrecipitationSerial(uint8_t climate, uint8_t precip){
    Serial.print("Precipitation Sample Site ");
    Serial.print(precip);
    Serial.println();

    switch(climate){
        case 0:
            Serial.println("Climate Condition: Normal");
            break;
        case 1:
            Serial.println("Climate Condition: High Snowpack");
            break;
        case 2:
            Serial.println("Climate Condition: Drought");
            break;
    }

    printCurrentSampleSerial(precipitations[(climate*2 + climate) + (precip-1)][1], precipitations[(climate*2 + climate) + (precip-1)][2]);
}

// Output to Serial a specific stream under current climate condition
void printStreamSerial(Adafruit_Thermal &printer, uint8_t climate, uint8_t strm){
    Serial.print("Stream Sample Site ");
    Serial.print(strm);
    Serial.println();

    switch(climate){
        case 0:
            Serial.println("Climate Condition: Normal");
            break;
        case 1:
            Serial.println("Climate Condition: High Snowpack");
            break;
        case 2:
            Serial.println("Climate Condition: Drought");
            break;
    }

    switch(strm){
        case 1: 
            Serial.println("Landscape: Lava Flows");
            break;
        case 2:
            Serial.println("Landscape: Earthflows");
            break;
        case 3:
            Serial.println("Landscape: Weathered Bedrock");
            break;
    }

    printCurrentSampleSerial(streams[(climate*2 + climate) + (strm-1)][1], streams[(climate*2 + climate) + (strm-1)][2]);
}

// Output to Serial a specific river under current climate condition
void printRiver(uint8_t climate, char rvr){
    Serial.print("River Sample Site ");
    Serial.print(rvr);
    Serial.println();

    switch(climate){
        case 0:
            Serial.println("Climate Condition: Normal");
            break;
        case 1:
            Serial.println("Climate Condition: High Snowpack");
            break;
        case 2:
            Serial.println("Climate Condition: Drought");
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

    printCurrentSampleSerial(rivers[(climate*2 + climate) + (river-1)][1], rivers[(climate*2 + climate) + (river-1)][2]);
}
