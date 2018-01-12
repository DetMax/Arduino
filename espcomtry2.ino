#include <ESP8266WiFi.h>
 
const char* ssid = "AndroidAP";//type your ssid
const char* password = "12345678";//type your password
 
int ledPin = 2; // GPIO2 of ESP8266
WiFiServer server(80);//Service Port
 
void setup() {
  Serial.begin(9600);
  delay(10);
 
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
   
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
   
  WiFi.begin(ssid, password);
   
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
   
  // Start the server
  server.begin();
  Serial.println("Server started");
  // Print the IP address
  IPAddress ourlocalIPa = WiFi.localIP();
  String ourlocalIP = ourlocalIPa.toString();
  int temp = ourlocalIP.indexOf('.');
  String first = ourlocalIP.substring(0,temp);
  int temp2 = ourlocalIP.indexOf('.', temp+1); 
  String second = ourlocalIP.substring(temp+1, temp2);
  int temp3 = ourlocalIP.indexOf('.', temp2+1);
  String third = ourlocalIP.substring(temp2+1, temp3);
  // config static IP
  IPAddress ip(first.toInt(), second.toInt(), third.toInt(), 69); // where xx is the desired IP Address
  IPAddress gateway(first.toInt(), second.toInt(), third.toInt(), 1); // set gateway to match your network
  IPAddress subnet(255, 255, 255, 0); // set subnet mask to match your network
  WiFi.config(ip, gateway, subnet);
  Serial.println("IP changed!\nNew IP: ");
  Serial.println(WiFi.localIP());
}
 
void loop() {
  int value = LOW;

  
  // Read the first line of the request
//  String request = client.readStringUntil('\r');
  String request = Serial.readString();
//  Serial.println(request);
//  client.flush();
  
  // Match the request
 
  
  if (request.indexOf("/LED=ON") != -1) {
    digitalWrite(ledPin, HIGH);
    value = HIGH;
  } 
  if (request.indexOf("/LED=OFF") != -1){
    digitalWrite(ledPin, LOW);
    value = LOW;
  }
 
  //Set ledPin according to the request
  //digitalWrite(ledPin, value);
   
  
 
  delay(1);
}
