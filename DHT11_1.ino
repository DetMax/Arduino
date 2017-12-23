#include<dht.h>
dht DHT;

void setup() {

Serial.begin(9600);

}

void loop() 

{ 

int chk = DHT.read11(3);

Serial.print("Humidity: " );

Serial.println(DHT.humidity, 1);

Serial.print("Temparature: ");

Serial.println(DHT.temperature, 1);

delay(2000);

}
