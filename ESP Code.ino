 #include <ESP8266WiFi.h>

const char* ssid = "Pollution";       //WiFi SSID
const char* password = "DefaultPassword";    //WiFi Password

WiFiServer server(80);                //service port

void setup() {
  delay(10000);
  Serial.begin(9600);
  while(!Serial){
    delay(1);
  }
  Serial.setTimeout(5000);
  delay(10);
  Serial.print('R');
  while(!Serial.available()){
    delay(1);
  }
  char temp = Serial.read();
  while(temp != 'R'){
    temp = Serial.read();
  }
  WiFi.begin(ssid, password);
  while(WiFi.status()!=WL_CONNECTED){
    delay(500);
  }
  Serial.print('S');
  server.begin();
  Serial.print(WiFi.localIP());
  Serial.print('\r');
}

void loop() {
  WiFiClient client = server.available();
  if(!client){
    return;
  }
  while(!client.available()){       //wait until client sends some data
    delay(1);
  }
  delay(1000);
  while(client.available()){
    Serial.write(client.read());
  }
  while(!Serial.available()){      //wait until arduino sends back response
    delay(1);
  }
  delay(1000);
  while(Serial.available()){
    client.write(Serial.read());
  }
  //String response = Serial.readStringUntil('\r');
  //client.println(response);
  client.flush();
  delay(1);
}
