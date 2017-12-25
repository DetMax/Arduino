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
  Serial.println("SD card initialised.");
}

void loop() 
{
float sValue;
float sVolt;
sValue = analogRead(A0);
sVolt = sValue/1024*5.0;
Serial.print("sensor voltage = ");
Serial.print(sVolt);
Serial.print("V ");
Serial.println(sValue);
int chk = DHT.read11(3);
Serial.print("Humidity: " );
Serial.println(DHT.humidity, 1);
Serial.print("Temparature: ");
Serial.println(DHT.temperature, 1);
int temp = DHT.temperature;
int humidity = DHT.humidity;
File dataFile = SD.open("data.txt",FILE_WRITE);
  if(dataFile){
    dataFile.print("Temperature : ");
    dataFile.print(temp);
    dataFile.print(" Humidity : ");
    dataFile.print(humidity);
    dataFile.print(" Pollution level : ");
    dataFile.println(sValue);
    Serial.println("File updated.");
    dataFile.close();
  }
  else {
    Serial.println("Error opening data file.");
  }
  delay(2000);
}

