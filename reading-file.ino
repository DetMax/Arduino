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
File  dataFile = SD.open("data.txt",FILE_READ);
  if(dataFile){
    Serial.println("Data file found and opened.");
    Serial.println("Its contents are :");
    while(dataFile.available()){
      Serial.write(dataFile.read());
    }
    dataFile.close();
    Serial.println("Reading finished.");
  }
  else {
    Serial.println("Data file does not exist.");
  }
}

void loop() {
}
