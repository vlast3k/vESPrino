#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <NeoPixelBus.h> 
#include <Streaming.h>

const char* ssid = "vladiHome";
const char* password = "0888414447";
NeoPixelBus strip = NeoPixelBus(1, D7);

ESP8266WebServer server(80);

void handleRoot() {
  server.send(200, "text/plain", "hello from esp8266!");
}

void handleNotFound(){
  server.send(404, "text/plain", "File Not Found\n\n");
}

void setup(void){
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial << "\nConnected to " << ssid << "\nIP address: " << WiFi.localIP();

  if (MDNS.begin("esp8266")) {
    Serial.println("MDNS responder started");
    MDNS.addService("http", "tcp", 80);
  }
    

  server.on("/", handleRoot);

  server.on("/inline", [](){
    server.send(200, "text/plain", "this works as well");
  });

  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void){
  server.handleClient();
}
