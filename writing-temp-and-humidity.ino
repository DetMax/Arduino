#include <SPI.h>
#include <SD.h>
#include<dht.h>
dht DHT;

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
}

void loop() 
{
int chk = DHT.read11(3);
Serial.print("Humidity: " );
Serial.println(DHT.humidity, 1);
Serial.print("Temparature: ");
Serial.println(DHT.temperature, 1);
int temp = DHT.temperature;
int humidity = DHT.humidity;
File dataFile = SD.open("data.txt",FILE_WRITE);
  if(dataFile){
    Serial.println("File opened. Writing data.");
    dataFile.print("Temperature : ");
    dataFile.print(temp);
    dataFile.print(" Humidity : ");
    dataFile.println(humidity);
    Serial.println("Data written.");
    dataFile.close();
  }
  else {
    Serial.println("Error opening data file.");
  }
  delay(2000);
}
