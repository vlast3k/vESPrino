#include <Wire.h>
#include <Si7021.h>
#include <Streaming.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
void initWifi();
void sendTS(float temp, float hum, String tsKey);
void sendSAP(float temp, float hum, String mmsHost, String deviceId, String messageId, String authToken);
void httpGET(String url);

SI7021 si7021;
void setup() {
  Serial.begin(115200);
  initWifi();
  si7021.begin(D1, D6); // Runs : Wire.begin() + reset()
  si7021.setHumidityRes(8); // Humidity = 12-bit / Temperature = 14-bit
}

uint32_t lastTSSend = 0;
void loop() {
  float tmp = si7021.readTemp();
  float hum = si7021.readHumidity();
  Serial << "Humidity : " << hum << " %\t";
  Serial << "Temp : "     << tmp << " C";
  Serial << endl;
  delay(1500);

  if (!lastTSSend || (millis() - lastTSSend > 30000)) {
    sendTS (tmp, hum, "FMW9LS6YJ8O7QIKF");
    sendSAP(tmp, hum, "iotmmsi024148trial.hanatrial.ondemand.com", "e46304a8-a410-4979-82f6-ca3da7e43df9",
                      "e81924e1aa5afcf4ae04", "8f337a8e54bd352f28c2892743c94b3");
    lastTSSend = millis();
  }
}

void sendTS(float temp, float hum, String tsKey) {
    httpGET(String("") + "http://api.thingspeak.com/update?key=" + tsKey + "&field1=" + temp + "&field2=" + hum); 
}


void sendSAP(float temp, float hum, String mmsHost, String deviceId, String messageId, String authToken) {
  HTTPClient http;
  String rq = String("https://") + mmsHost + "/com.sap.iotservices.mms/v1/api/http/data/"
                + deviceId +"/" + messageId + "/sync?temp=" + temp + "&humidity=" + hum;
  Serial << "Sending: " << rq << endl;                
  http.begin(rq);
  http.addHeader("Content-Type",  "application/json;charset=UTF-8");
  http.addHeader("Authorization", String("Bearer ") + authToken);  
  
  int httpCode = http.POST("");
  // httpCode will be negative on error
  if(httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);
      String payload = http.getString();
      Serial.println(payload);          
  } else {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
  }
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
