/*
 * 
 * Code State:
 * Creation (26/1, 4:00 pm)
 * Serial: Initialised
 * LCD: Initialised
 * SDModule: Initialised
 * 
 */

#include<LiquidCrystal.h>
#include<SD.h>

LiquidCrystal lcd(7,6,5,4,3,2);   // (rs, en, d4, d5, d6, d7)
File myFile;
String espIP;
void setup() {
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
  
  cleardisp();
  lcd.print("Project idle");
  delay(2000);
  for(int i=0;i<3;i++){
    lcd.print(".");
    delay(2000);
  }
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

