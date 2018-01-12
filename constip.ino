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
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
  Serial.println("Now changing the IP...");
  IPAddress ourlocalIPa = WiFi.localIP();
  String ourlocalIP = ourlocalIPa.toString();
  int temp = ourlocalIP.indexOf('.');
  String first = ourlocalIP.substring(0,temp);
  int temp2 = ourlocalIP.indexOf('.', temp+1); 
  String second = ourlocalIP.substring(temp+1, temp2);
  int temp3 = ourlocalIP.indexOf('.', temp2+1);
  String third = ourlocalIP.substring(temp2+1, temp3);
  Serial.print(first);
  Serial.print('.');
  Serial.print(second);
  Serial.print('.');
  Serial.print(third);
  Serial.println(".69");
  // config static IP
  IPAddress ip(first.toInt(), second.toInt(), third.toInt(), 69); // where xx is the desired IP Address
  IPAddress gateway(first, second, third, 1); // set gateway to match your network
  IPAddress subnet(255, 255, 255, 0); // set subnet mask to match your network
  WiFi.config(ip, gateway, subnet);
  Serial.println("IP changed!\nNew IP: ");
  Serial.println(WiFi.localIP());
}
 
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
   
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
  int value = LOW;
  // Return the response
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
  
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
   
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
  Serial.println("Client disconnected");
  Serial.println("");
}
