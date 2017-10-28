/***************************
 ESP8266 DoorBird Chime
 ----------------------
 Created by: John Marzella
 Created on: 29/09/2017
***************************/

#include <ESP8266WiFi.h>
 
const char* ssid = "";// type your SSID
const char* password = "";// type your WPA(2) passphrase
const char* netname = "ESP8266-DoorBird-Chime";// type your network hostname
 
int ledPin = 2; // GPIO2 of ESP8266 - onboard LED
int buzzPin = 5; // GPIO2 of ESP8266 - NodeMCU pin D1

WiFiServer server(80); //Service Port
 
void setup() {
  Serial.begin(115200);
  delay(10);
 
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH); // LED off on startup
   
  // Connect to WiFi network
  Serial.println();

  Serial.println("Set WiFi to STAtion mode");
  WiFi.mode(WIFI_STA);

  Serial.print("Set hostname to: ");
  Serial.println(netname);
  WiFi.hostname(netname);

  Serial.print("Connecting to SSID: ");
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
}
 
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
   
  // Wait until the client sends some data
  Serial.print("New client connected: ");
  Serial.println(client.remoteIP().toString().c_str());
  while(!client.available()){
    delay(1);
  }
   
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
   
  // Match the request
  if (request.indexOf("/chime=dingDong/") != -1) { // Ding Dong chime + LED
    digitalWrite(ledPin, LOW);
    tone(buzzPin,370);//370Hz aka F#4
    delay(1000);
    tone(buzzPin,294);//294Hz aka D4
    delay(2000);
    noTone(buzzPin);// stop tone
    digitalWrite(ledPin, HIGH);
    delay(1000);
    digitalWrite(ledPin, LOW);
    tone(buzzPin,370);//370Hz aka F#4
    delay(1000);
    tone(buzzPin,294);//294Hz aka D4
    delay(2000);
    noTone(buzzPin);// stop tone
    digitalWrite(ledPin, HIGH);
    delay(100);
  }
  if (request.indexOf("/chime=silent/") != -1){ // Flashing LED - 20 times
    for (int counter=1; counter<=20; counter = counter+1) {
      digitalWrite(ledPin, LOW);
      delay(500);// delay 500ms
      digitalWrite(ledPin, HIGH);
      delay(500);// delay 500ms
    }
  }
 
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<h1>ESP8266 DoorBird Chime</h1>");
  client.println("<h3>Options:</h3>");
  client.println("<a href=\"/chime=dingDong/\">dingDong</a> Ding Dong tone + LED<br>");
  client.println("<a href=\"/chime=silent/\">silent</a> 20 LED flashes over 10 seconds<br>");
  client.println("</html>");

  // Close the client connection
  delay(1);
  client.stop();
  Serial.println("Client disconnected");
  Serial.println("");
}
