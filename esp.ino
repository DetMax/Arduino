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
   
  WiFi.begin(ssid, password);
   
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  // Start the server
  server.begin();
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
}
 
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
  int value = digitalRead(ledPin);
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
   
  client.print("Led pin is now: ");
   
  if(value == HIGH) {
    client.print("On");  
  } else {
    client.print("Off");
  }
  client.println("<br><br>");
  client.println("Click <a href=\"/LED=ON\">here</a> turn the LED on pin 2 ON<br>");
  client.println("Click <a href=\"/LED=OFF\">here turn the LED on pin 2 OFF<br>");
  client.println("</html>");
  // Wait until the client sends some data
  String response = Serial.readString();
  client.println(response);
  client.flush();
  while(!client.available()){
    delay(1);
  }


  
 
  // Read the first line of the request
  String request = client.readString();
  Serial.println(request);

  
 
  
  if (request.indexOf("/LED=ON") != -1) {
    digitalWrite(ledPin, HIGH);
    value = HIGH;
  } 
  if (request.indexOf("/LED=OFF") != -1){
    digitalWrite(ledPin, LOW);
    value = LOW;
  }
  delay(1);
}