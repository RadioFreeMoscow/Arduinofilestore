#include <math.h>
#include <SPI.h>
#include <SD.h>

  double Thermister(int RawADC) {
    double Temp;
    Temp = log(((10240000/RawADC) - 10000));
    Temp = 1/ (0.001129148 + (0.000234125 + (0.0000000876741 * Temp * Temp))* Temp);
    Temp = Temp - 273.15;
    return Temp;
  }
const int chipSelect = 4;
const int theSwitch = 7;

//Switch Variable
int switchRead = 0;


void setup() {
  pinMode(theSwitch,INPUT);
  Serial.begin(9600);  
  if (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("Successfully Initialised");
}


void loop() {
//making an empty string to log in the file being created
switchRead = digitalRead(theSwitch);
Serial.println(switchRead);

String dataString = "";

//Read the Temperature Sensor:
    if (switchRead == HIGH) {
    int sensor = Thermister(analogRead(0)); // Run the input through thermistor function
    dataString += String(sensor);
    //Serial.println(sensor);
    File datafile = SD.open("temp.txt",FILE_WRITE);
    //if file is available
    if(datafile)  {
      datafile.println("Begin Logging");
      datafile.println(dataString + "degrees Celsius");
      datafile.close();
      Serial.println(dataString);
      Serial.println("OK");
    }
    else {
      Serial.println("Go for a Smoke");
    }
    delay (1000);
      
      
    }
}
    

