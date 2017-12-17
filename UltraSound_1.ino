long ping, dist;


void setup() 
{
  pinMode(11,OUTPUT);
  pinMode(12,INPUT);
  pinMode(3,OUTPUT);
  Serial.begin(9600);
}


void loop() 
{
  digitalWrite(11, LOW);
  delayMicroseconds(5);
  digitalWrite(11, HIGH);
 
  pinMode(12,INPUT);

  ping  = pulseIn(12, HIGH);
  
  dist = 0.017 * ping;

  Serial.print(dist);
  Serial.println("cm");
  delay(500);

  if(dist < 7)
  {
    for(int i = 0;i < 100; i++)
  {
    analogWrite(3,i);
    delay(5);
  }
  for(int i = 100;i > 0; i--)
  {
    analogWrite(3,i);
    delay(5);
  }
  }
  else if(dist > 0)
  {
    int i = 0;
    analogWrite(3,i);
  }
}



