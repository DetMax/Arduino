#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3); // RX, TX

void setup() {
  
  pinMode(13,OUTPUT);
  digitalWrite(13,LOW);
  Serial.begin(9600);
  while (!Serial) {
    ; 
  }


  Serial.println("Serial connection established.");

 
  mySerial.begin(9600);
  while(!mySerial){
    delay(1);
  }
  Serial.println("ESP comm established.");
}

void loop() { 
  if (mySerial.available()) {
    String request = mySerial.readString();
    if (request.indexOf("/LED=ON") != -1) {
      digitalWrite(13, HIGH);
      mySerial.write("LED turned on.");
    } 
    if (request.indexOf("/LED=OFF") != -1){
     digitalWrite(13, LOW);
     mySerial.write("LED turned off.");
    }
  }
  delay(1);
}
