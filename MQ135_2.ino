void setup() 
{
  Serial.begin(9600);
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
  delay(1000);
}
