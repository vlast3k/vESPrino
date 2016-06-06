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

const RgbColor *allColors[] = {&red, &pink, &lila, &violet, &blue, &mblue, &cyan, &green, &yellow, &orange};
#define TOTAL_COLORS 10
byte colorIdx = 0;
int BTTN_PIN = 0;
//int LED_PIN = D6;
void ex2_attachInterrupt(void (*)());
//NeoPixelBus strip = NeoPixelBus(1, D4);
//NeoPixelBus<NeoGrbFeature, NeoEsp8266Uart800KbpsMethod> strip(1, 2);
void setup() {  
 // delay(4000);
//  uint32_t status = 0;
//  ex0_serialDumps();
//  ESP.rtcUserMemoryRead(0, &status, sizeof(int));
//  Serial << "status=" << status << endl;
//  Serial <<"AsdsadsaD" << endl;
//  delay(500);
//  if (status != 1) {
//    status =1;
//    ESP.rtcUserMemoryWrite(0, &status, sizeof(int));
//    ESP.deepSleep(100, WAKE_RF_DISABLED);
//    delay(1000);
//  }
 //   WiFi.mode(WIFI_STA);
 // WiFi.begin("vladiHome", "0888414447");
  //strip.Begin();
//  strip.SetPixelColor(0, RgbColor(100, 0,100));
//  strip.Show();  
  //digitalWrite(D4, 0);
  /*
   * Exercise 0: Serial port communication
   */
   ex0_serialDumps();
   
  /*
   * Exercise 1: Blink LED
   */
   //ex1_blink_led();
 
  /*
   * Exercise 2a: press button, display textD
   */
   //ex2_attachInterrupt(ex2a_onBttnChange_text);

  /*
   * Exercise 2b: press button, change led
   */
   ex2_attachInterrupt(ex2b_onBttnChange_led);
}
//
//void oledON() {
//  NeoPixelBus<NeoGrbFeature, NeoEsp8266Uart800KbpsMethod> strip(1, 2);
//  strip.Begin();
//  strip.SetPixelColor(0, RgbColor(20, 0,20));
//  strip.Show(); 
//}
//RgbColor black(0, 0, 0);
//RgbColor lila(20, 0, 20);
void oledOFF() {
  
  setLedColor(black);
}
void oledON() {
  RgbColor c = RgbColor::LinearBlend(*allColors[colorIdx++ % TOTAL_COLORS], black, 0.7f);
//  RgbColor c = RgbColor(20,20,20);//::LinearBlend(lila, black, 0.2f);
  //RgbColor c = white;
  //Serial << c.R << " " << c.G << " " << c.B << endl;
  setLedColor(c);
}
//void oledOFF() {
//  NeoPixelBus<NeoGrbFeature, NeoEsp8266Uart800KbpsMethod> strip(1, 2);
//  strip.Begin();
//  strip.SetPixelColor(0, RgbColor(0, 0, 0));
//  strip.Show();   
//}

void setLedColor(const RgbColor &color) {
  NeoPixelBus<NeoGrbFeature, NeoEsp8266Uart800KbpsMethod> strip(1, 2);
  strip.Begin();
  strip.SetPixelColor(0, color);
  strip.Show();   
  delay(1);
  Serial1.end();
}

boolean changeColor = false;
void loop() {
    if (changeColor) {
      oledON();
      changeColor = false;
    }
    delay(10);

  /*
   * Exercise 3: blink in loop
   */
  // oledON();

  // delay(300);
  // oledOFF();
 
  // delay(300);
  // Serial << millis() << endl;

//   pinMode(LED_PIN, OUTPUT);
//   digitalWrite(LED_PIN, HIGH);   // turn the LED on (HIGH is the voltage level)
//   delay(300);              // wait for a second
//   digitalWrite(LED_PIN, LOW);    // turn the LED off by making the voltage LOW
//   delay(300);  
}

void ex0_serialDumps() {
  Serial.begin(115200L);
  Serial.println("ESP8266 101 Training");
}

void ex1_blink_led() {
   for (int i=0; i < 10; i++) {
//     digitalWrite(LED_PIN, HIGH);   // turn the LED on (HIGH is the voltage level)
//     delay(600);              // wait for a second
//     digitalWrite(LED_PIN, LOW);    // turn the LED off by making the voltage LOW
//     delay(600);  
       oledON();
       delay(600);
       oledOFF();
       delay(600);
   }  
}

void ex2_attachInterrupt(void (*func)()) {
  pinMode(BTTN_PIN, INPUT_PULLUP);
  attachInterrupt(BTTN_PIN, func, CHANGE);
}

void ex2a_onBttnChange_text() {
  Serial.println(String("Button state: ") + digitalRead(BTTN_PIN));
}

void ex2b_onBttnChange_led() {
  Serial.println(String("Button state: ") + digitalRead(BTTN_PIN));
  if (digitalRead(BTTN_PIN)) changeColor = true;//  oledON();
  //digitalWrite(LED_PIN, digitalRead(BTTN_PIN));
}
