#include <ESP8266WiFi.h>
#include <Streaming.h>
#include <ESP8266HTTPClient.h>
String mmsHost = "iotmmsi024148trial.hanatrial.ondemand.com";
String deviceId = "e46304a8-a410-4979-82f6-ca3da7e43df9";
String authToken = "8f337a8e54bd352f28c2892743c94b3";
String colors[] = {"red","pink","lila","violet","blue","mblue","cyan","green","yellow","orange"};
#define COLOR_COUNT 10
void ex2_attachInterrupt(void (*)());
void   initWifi();
  void setupWebServer();
void   initLight();
void   handleSAP_IOT_PushService();
void   processCommand(String xxx);
void  attachButton();
void   handleWebServer();
void   handleSAP_IOT_PushService();
void   doSend();
void onButton();
void processMessage(String msgIn) ;
void onColor();

void setup() {
  Serial.begin(115200);
  initWifi();
  setupWebServer();
  initLight();
  handleSAP_IOT_PushService();
  processCommand(String("red"));
  delay(2000);
  processCommand(String("blue"));
  attachButton();
}

void loop() {
  handleWebServer();
  handleSAP_IOT_PushService();
  doSend();
}
