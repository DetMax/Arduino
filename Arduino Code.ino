/*
 * 
 * Code State:
 * Creation (26/1, 4:00 pm)
 * Serial: Initialised
 * LCD: Initialised
 * SDModule: Initialised
 * 
 */

#include <dht.h>
#include <LiquidCrystal.h>
#include <SD.h>

dht DHT;

String request;
String response;
float sValue, sVolt, voMeasured, calcVoltage, dustDensity;

LiquidCrystal lcd(7,6,5,4,3,2);   // (rs, en, d4, d5, d6, d7)
File myFile;
String espIP;
void setup() {
  pinMode(30,INPUT);
  digitalWrite(30,LOW);
  Serial.begin(9600);
  lcd.begin(16,2);
  while(!Serial){
    ;
  }
  lcd.clear();
  lcd.print("Beginning");
  lcd.setCursor(0,1);
  lcd.print("Setup");
  delay(1000);
  lcd.clear();
  lcd.print("SD Module:");
  if(!SD.begin(53)){             // cs pin
    printErrorCode(10);
  }
  lcd.setCursor(0,1);
  lcd.print("Initialised");
  delay(1000);
  lcd.clear();
  lcd.print("Waiting for");
  lcd.setCursor(0,1);
  lcd.print("ESP");
  delay(1000);
  Serial3.begin(9600);
  while(!Serial3){
    delay(1);
  }
  while(!Serial3.available()){
    delay(1);
  }
  char temp = Serial3.read();
  while(temp != 'R'){
    temp = Serial3.read();
  }
  lcd.clear();
  lcd.print("ESP Ready");
  delay(1000);
  Serial3.print('R');
  lcd.clear();
  lcd.print("Waiting for IP");
  delay(1000);
  temp = Serial3.read();
  while(temp != 'S'){
    temp = Serial3.read();
  }
  espIP = Serial3.readStringUntil('\r');
  lcd.clear();
  lcd.print("ESP comm est");
  lcd.setCursor(0,1);
  lcd.print(espIP);
  delay(1000);
}

void loop() {
  int chk = DHT.read11(31);
  sValue = analogRead(A0);
  sVolt = sValue/1024*5.0;
  
  digitalWrite(24,LOW);
  delayMicroseconds(280);
  voMeasured = analogRead(A5);
  delayMicroseconds(40);
  digitalWrite(24,HIGH);
  delayMicroseconds(9680);
  calcVoltage = voMeasured * (5.0/1024);
  dustDensity = 0.17 * calcVoltage -0.1;

  if(digitalRead(30) == HIGH){
    cleardisp();
    lcd.print("Temp : " + String(int(DHT.temperature))+ "."+String(getDecimal(DHT.temperature)));
    delay(2000);
    cleardisp();
    lcd.print("Hum : " + String(int(DHT.humidity))+ "."+String(getDecimal(DHT.humidity)));
    delay(2000);
    cleardisp();
    lcd.print("Poll : " + String(int(sValue))+ "."+String(getDecimal(sValue)));
    delay(2000);
    cleardisp();
    lcd.print("Dust : " + String(int(dustDensity))+ "."+String(getDecimal(dustDensity)));
    delay(2000);
    lcd.print("Idle...");
    myFile = SD.open("data.txt",FILE_WRITE);
    if(myFile){
      myFile.println(String(int(DHT.temperature))+ "."+String(getDecimal(DHT.temperature)) + "$" + String(int(DHT.humidity))+ "."+String(getDecimal(DHT.humidity)) + "$" + String(int(sValue))+ "."+String(getDecimal(sValue)) + "$" + String(int(dustDensity))+ "."+String(getDecimal(dustDensity)) + "^");
    }
    myFile.close();
  }
  
  if(Serial3.available()){
    delay(1000);
    while(Serial3.available()){
      request = Serial3.readString();
      Serial.print(request);
    }
    if(request.indexOf("getdata")){
      response = String(int(DHT.temperature))+ "."+String(getDecimal(DHT.temperature)) + "$" + String(int(DHT.humidity))+ "."+String(getDecimal(DHT.humidity)) + "$" + String(int(sValue))+ "."+String(getDecimal(sValue)) + "$" + String(int(dustDensity))+ "."+String(getDecimal(dustDensity)) + "^";
      Serial3.print(response);
    }
    else Serial3.print("Error!");
  }
  cleardisp();
  lcd.print("Idle...");
}

void printErrorCode(int errorCode){
  while(1>0){
    lcd.clear();
    lcd.print("Error ");
    lcd.print(errorCode);
    for(int i=0;i<3;i++){
      lcd.print(".");
      delay(1000);
    }
  }
}

void cleardisp(){
  lcd.clear();
  lcd.setCursor(0,1);
  lcd.print(espIP);
  lcd.setCursor(0,0);
}

long getDecimal(float val)
{
  int intPart = int(val);
  long decPart = 1000*(val-intPart); //I am multiplying by 1000 assuming that the foat values will have a maximum of 3 decimal places. 
                                    //Change to match the number of decimal places you need
  if(decPart>0)return(decPart);           //return the decimal part of float number if it is available 
  else if(decPart<0)return((-1)*decPart); //if negative, multiply by -1
  else if(decPart=0)return(00);           //return 0 if decimal part of float number is not available
}

