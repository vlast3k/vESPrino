#define VIN 3.3f
#include <NeoPixelBus.h> 
#include <Si7021.h>

#include <Streaming.h>
SI7021 *si7021;

void si7021init() {
    si7021 = new SI7021();
    si7021->begin(5, 12); // Runs : Wire.begin() + reset()
    si7021->setHumidityRes(8); // Humidity = 12-bit / Temperature = 14-bit
}
//NeoPixelBus<NeoGrbFeature, NeoEsp8266Uart800KbpsMethod> strip(1, 2);
double getTermistorC() {
  uint32_t x = 0;
  for (int i=0; i < 10; i++) {
    x += analogRead(A0);
    delay(2);
  }
  x = x/10;
  float v = ((float)x / 1024) *VIN;
  double r = (10*volts)/(VIN-volts)*1000;
  double steinhart;
  steinhart = r / 10000.0;     // (R/Ro)
  steinhart = log(steinhart);                  // ln(R/Ro)
  steinhart /= 3380;                   // 1/B * ln(R/Ro)
  steinhart += 1.0 / (25 + 273.15); // + (1/To)
  steinhart = 1.0 / steinhart;                 // Invert
  steinhart -= 273.15;                         // convert to C
  
  return steinhart;
}



void setup() {
  Serial.begin(9600);
  NeoPixelBus<NeoGrbFeature, NeoEsp8266Uart800KbpsMethod> strip(1, 2);
  strip.Begin();
  strip.SetPixelColor(0, RgbColor(0));
  strip.Show();   
   si7021init();
  float tmp = si7021->readTemp();
  float hum = si7021->readHumidity();
  Serial << F("Humidity : ") << hum << " %\t";
  Serial << F("Temp : "    ) << tmp << " C" << endl;
  
  //delay(1);
  //Serial1.end();
  // put your setup code here, to run once:
  //Serial.println("dsfdsfdsfdsfds");
  //delay(1000);
}

void loop() {
  Serial.println(analogRead(A0));
  uint32_t x = 0;
  for (int i=0; i < 10; i++) {
    x += analogRead(A0);
  }
  x = x/10;
  float v = ((float)x / 1024) *VIN;
  Serial.println(v);
  Serial.println(getTermistorC(v));

    float tmp = si7021->readTemp();
  float hum = si7021->readHumidity();
  Serial << F("Humidity : ") << hum << " %\t";
  Serial << F("Temp : "    ) << tmp << " C" << endl;
  
  ESP.deepSleep(60000000L);
  delay(1000);
  // put your main code here, to run repeatedly:

}
