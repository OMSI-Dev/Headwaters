#include <Arduino.h>
#include <Adafruit_Thermal.h>
#include <OMSI_QR.h>
#include <testTube.h>
#include <calicoTestTube.h>

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

void printCurrentSample(Adafruit_Thermal &printer, int loc, int strm, float iso, float temp, float oxy){
    printer.setFont('B');
    printer.setSize('s');

    printer.print("Sample Location: ");
    printer.print(loc);
    printer.println();

    printer.print("Stream: ");
    printer.print(strm);
    printer.println();

    printer.print("Isotope count: ");
    printer.print(iso);
    printer.println();

    printer.print("Temperature: ");
    printer.print(temp);
    printer.println();

    printer.print("Oxygen dissolved: ");
    printer.print(oxy);
    printer.println();
}

void printQR(Adafruit_Thermal &printer){
  printer.printBitmap(QRWidth, QRHeight, OMSI_QR);
  printer.feed(4);
}