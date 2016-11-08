#include <NeoPixelBus.h> 
#include <Streaming.h>
#include <ESP8266WiFi.h>

const RgbColor red =    RgbColor(255, 0, 0);
const RgbColor pink =   RgbColor(255, 0, 128);
const RgbColor lila =   RgbColor(255, 0, 255);
const RgbColor violet = RgbColor(128, 0, 255);
const RgbColor blue =   RgbColor(0, 0, 255);
const RgbColor mblue =  RgbColor(0, 128, 255);
const RgbColor cyan =   RgbColor(0, 255, 255);
const RgbColor green =  RgbColor(0, 255, 0);
const RgbColor yellow = RgbColor(255, 255, 0);
const RgbColor orange = RgbColor(255, 100, 0);
const RgbColor white = RgbColor(255);
const RgbColor black = RgbColor(0);

const RgbColor *allColors[] = {&green, &red, &blue, &pink, &mblue, &lila, &cyan, &violet, &yellow, &orange};
#define TOTAL_COLORS 10
byte colorIdx = 0;
int BTTN_PIN = 0;
float brg = 0.7f;

boolean changeColor = false;
bool oldState;

void setup() {  
   Serial.begin(115200L);
   Serial.println("Hello vESPrino");
   pinMode(BTTN_PIN, INPUT_PULLUP);
   oledON(false);
   oldState = true;
}

void oledOFF() {
  setLedColor(black);
}

void oledON(bool advance) {
  if (advance) colorIdx ++;
  RgbColor c = RgbColor::LinearBlend(*allColors[colorIdx % TOTAL_COLORS], black, brg);
  setLedColor(c);
}

void setLedColor(const RgbColor &color) {
  NeoPixelBus<NeoGrbFeature, NeoEsp8266Uart800KbpsMethod> strip(1, 2);
  strip.Begin();
  strip.SetPixelColor(0, color);
  strip.Show();   
  delay(1);
  Serial1.end();
}

uint32_t clicked = 0;

void loop() {
    handleButton();
    if (changeColor) {
      oledON(true);
      changeColor = false;
    }
}

bool changedBrg = false;
void handleButton() {
    if (digitalRead(BTTN_PIN) == 0) {
      if (oldState == true) {
        oldState = false;
        clicked = millis();
      } else {
        if (!changedBrg) {
          if (millis() - clicked > 1000) changedBrg = true;
        } else {
          if (millis() - clicked > 30) {
            if (brg > 0.85) brg -= 0.005;
            else brg -= 0.01f;
            if (brg < 0.3) brg = 1;
            oledON(false);
            clicked = millis();
          }
        }
      }
    } else if (oldState == false) {
      oldState = true;
      if (changedBrg) changedBrg = false;
      else changeColor = true;
    }
}

