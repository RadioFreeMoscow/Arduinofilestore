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

void setup() {
  Serial.begin(9600);  
 
}


void loop() {
//making an empty string to log in the file being created
String dataString = "";

//Read the Temperature Sensor:
    
    int sensor = Thermister(analogRead(0)); // Run the input through thermistor function
    dataString += String(sensor);
    Serial.println(sensor);
    File datafile = SD.open("log.txt",FILE_WRITE);
    //if file is available
    if(datafile)  {
      datafile.println(dataString + " degrees Celsius");
      Serial.println(dataString + " degrees Celsius");
      datafile.close();
     
    }
    else {
      Serial.println("Go for a Smoke");
    }
    delay (1000);
      
      
    }

    

