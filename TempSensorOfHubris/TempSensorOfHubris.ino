#include <Wire.h>
#include "SSD1306Ascii.h"
#include "SSD1306AsciiWire.h"
#include <math.h>

#define I2C_ADDRESS 0x3C
SSD1306AsciiWire oled;
#define RST_PIN -1


double Thermister(int RawADC) {
    double Temp;
    Temp = log(((10240000/RawADC) - 10000));
    Temp = 1/ (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp))* Temp);
    Temp = Temp - 273.15;
    return Temp;
  }

//char* marxistPropaganda[]={"Spectre", "is", "haunting",
//"Europe", "The Spectre of","Communism"};

void setup() {
Wire.begin();
Wire.setClock(400000L);

#if RST_PIN >= 0
  oled.begin(&Adafruit128x64, I2C_ADDRESS, RST_PIN);
#else // RST_PIN >= 0
  oled.begin(&Adafruit128x64, I2C_ADDRESS);

#endif // RST_PIN >= 0
}

void loop() {
int sensor = Thermister(analogRead(0));
Serial.print(sensor);
oled.println(sensor);
}
