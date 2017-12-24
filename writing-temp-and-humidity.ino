#include <SPI.h>
#include <SD.h>

void setup() {
  Serial.begin(9600);
  while(!Serial){
    ;
  }
  Serial.println("Connected to computer.");
  Serial.println("Initialising SD card.");
  if(!SD.begin(10)){
    Serial.println("SD card initialisation failed.");
  }
  Serial.println("SD card initialised.");
}

void loop() {
  //place code here for reading data
  //assuming temperature is stored in variable 'temperature' and humidity is stored in variable 'humidity'
  dataFile = SD.open("data.txt",FILE_WRITE);
  if(dataFile){
    Serial.println("File opened. Writing data.");
    dataFile.println("Temperature : "+temperature+" Humidity : "+humidity);
    Serial.println("Data written.");
    dataFile.close();
  }
  else {
    Serial.println("Error opening data file.");
  }
  //insert delay statement here accordingly
}
