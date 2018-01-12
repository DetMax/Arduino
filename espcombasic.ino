void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()>0){
    Serial.print("We got : ");
    Serial.print(Serial.readString());
  }
  else{
    Serial.print('.');
    delay(1000);
  }
}
