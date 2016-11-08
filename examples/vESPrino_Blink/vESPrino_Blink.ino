#include <NeoPixelBus.h> 
#include <Streaming.h>
#include <ESP8266WiFi.h>

const RgbColor red   = RgbColor(50, 0, 0);
const RgbColor blue  = RgbColor(0, 0, 200);
const RgbColor green = RgbColor(0, 64, 0);
const RgbColor black = RgbColor(0);

void setup() {  
}

void loop() {
  setLedColor(red);
  delay(500);
  setLedColor(green);
  delay(500);
  setLedColor(blue);
  delay(500);
}

void setLedColor(const RgbColor &color) {
  NeoPixelBus<NeoGrbFeature, NeoEsp8266Uart800KbpsMethod> strip(1, 2);
  strip.Begin();
  strip.SetPixelColor(0, color);
  strip.Show();   
  delay(1);
  Serial1.end();
}

