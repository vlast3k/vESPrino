#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <NeoPixelBus.h> 
#include <Streaming.h>

const char* ssid = "InnoWi-Fi";
const char* password = "innoweek";
NeoPixelBus strip = NeoPixelBus(1, D7);
void setup() {
    Serial.begin(115200);
       strip.Begin();
  strip.SetPixelColor(0, RgbColor(10, 0,10));
  strip.Show(); 
    WiFi.begin(ssid, password);
    
    Serial.println("");
  
    // Wait for connection
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
  
    Serial << "\nConnected to " << ssid << "\nIP address: " << WiFi.localIP();
}

void httpGET(String url) {
    if(WiFi.status() == WL_CONNECTED) {
        HTTPClient http;

        Serial.print("[HTTP] begin...\n");
        http.begin(url); //HTTP

        Serial.print("[HTTP] GET...\n");
        // start connection and send HTTP header
        int httpCode = http.GET();

        // httpCode will be negative on error
        if(httpCode > 0) {
            // HTTP header has been send and Server response header has been handled
            Serial.printf("[HTTP] GET... code: %d\n", httpCode);
            String payload = http.getString();
            Serial.println(payload);          
        } else {
            Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }

        http.end();
    }  
}

void loop() {
    httpGET("http://google.com");
    delay(10000);
}

