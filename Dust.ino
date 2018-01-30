float voMeasured = 0;
float calcVoltage = 0;
float dustDensity = 0;
 
void setup(){
  Serial.begin(9600);
  pinMode(12,OUTPUT);
}
 
void loop(){
  digitalWrite(12,LOW); 
  delayMicroseconds(280);
 
  voMeasured = analogRead(A5); 
 
  delayMicroseconds(40);
  digitalWrite(12,HIGH); 
  delayMicroseconds(9680);
 
  
  calcVoltage = voMeasured * (5.0 / 1024);
 
  dustDensity = 0.17 * calcVoltage - 0.1;
 
  Serial.print("Raw Signal Value (0-1023): ");
  Serial.print(voMeasured);
 
  Serial.print(" - Voltage: ");
  Serial.print(calcVoltage);
 
  Serial.print(" - Dust Density: ");
  Serial.println(dustDensity);
 
  delay(1000);
}
