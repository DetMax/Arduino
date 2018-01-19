#include <dht.h>
#include <LiquidCrystal.h>
#include <SPI.h>
#include <SD.h>
dht DHT;
const int rs = 1, en = 2, d4 = 5, d5 = 6, d6 = 7, d7 = 8;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
File myFile;

void setup() 
{
  Serial.begin(9600);
  lcd.begin(16, 2);
  while (!Serial){
      ;    
  }

  Serial.println("Initializing SD card...");

 if (!SD.begin(4)){
    Serial.println("Initialization failed!");
    return;
  }
 
}
 
void loop() 
{
  float sValue;
  float sVolt; 
  int chk = DHT.read11(22);
  sValue = analogRead(A0);
  sVolt = sValue/1024*5.0;

  Serial.print("Humidity: " );
  Serial.print(DHT.humidity, 1);
  Serial.print("  Temparature: ");
  Serial.print(DHT.temperature, 1);
  Serial.print("  Air Quality: ");
  Serial.print(sValue);
  Serial.print("  Dust: ");
  Serial.println("Senosr not available.");
  lcd.setCursor(0, 0);
  lcd.print("IP Address");              //add ip address string
  myFile = SD.open("data_log.txt", FILE_WRITE);

  if(myFile){
    Serial.print("Writing to data_log.txt...");
    myFile.println("Humidity: ");
    myFile.print(DHT.humidity);
    myFile.print("Temperature: ");
    myFile.print(DHT.temperature);
    myFile.print("Air Quality: ");
    myFile.print(sValue);
    myFile.print("Dust: ");
    myFile.print("Sensor Not Available");                   //Add Variable for Dust Sensor  
  }
  else{
    Serial.println("SD card error! Cannot Write to SD card.");    
  }
  delay(2000);

}


