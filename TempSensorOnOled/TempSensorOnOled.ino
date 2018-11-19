// Simple I2C test for ebay 128x64 oled.

#include <Wire.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"
#include <math.h>


// 0X3C+SA0 - 0x3C or 0x3D
#define I2C_ADDRESS 0x3C

// Define proper RST_PIN if required.
#define RST_PIN -1

//Shortcut
SSD1306AsciiWire oled;

double Thermister(int RawADC) {
    double Temp;
    Temp = log(((10240000/RawADC) - 10000));
    Temp = 1/ (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp))* Temp);
    Temp = Temp - 273.15;
    return Temp;
  }

long forTheWorkers;


char* marxistPropaganda[]={"Spectre", "is", "haunting",
"Europe", "The Spectre of","Communism"};


//------------------------------------------------------------------------------
void setup() {
  Wire.begin();
  Wire.setClock(400000L);

#if RST_PIN >= 0
  oled.begin(&Adafruit128x64, I2C_ADDRESS, RST_PIN);
#else // RST_PIN >= 0
  oled.begin(&Adafruit128x64, I2C_ADDRESS);
#endif // RST_PIN >= 0

  oled.setFont(Adafruit5x7);

  uint32_t m = micros();
  oled.clear();
  oled.println("Made with Love for Mum" );
  oled.println("by Geoff and Sam");
  oled.println("12/09/2018");
  delay(3000);

 
}
//------------------------------------------------------------------------------
void loop() {
  forTheWorkers = random(100001);
  oled.clear();
  oled.println();
  oled.clear();
  int sensor = Thermister(analogRead(0));
  oled.print(sensor);
  oled.println(" degrees centigrade");
  delay(10000);
  oled.clear();
  oled.println();
  oled.clear();

 for (forTheWorkers >=99000; forTheWorkers >=99000; forTheWorkers++) {
    oled.println(marxistPropaganda[5]);
    oled.println(forTheWorkers);
    delay(10000);
    forTheWorkers = random(100001);
}

  }

