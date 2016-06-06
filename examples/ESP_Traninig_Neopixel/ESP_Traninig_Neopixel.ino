#include <NeoPixelBus.h> 
NeoPixelBus strip = NeoPixelBus(1, D7);
RgbColor red =    RgbColor(255, 0, 0);
RgbColor pink =   RgbColor(255, 0, 128);
RgbColor lila =   RgbColor(255, 0, 255);
RgbColor violet = RgbColor(128, 0, 255);
RgbColor blue =   RgbColor(0, 0, 255);
RgbColor mblue =  RgbColor(0, 128, 255);
RgbColor cyan =   RgbColor(0, 255, 255);
RgbColor green =  RgbColor(0, 255, 0);
RgbColor yellow = RgbColor(255, 255, 0);
RgbColor orange = RgbColor(255, 100, 0);
RgbColor white = RgbColor(255,255,255);
RgbColor black = RgbColor(0);
RgbColor colors[] = {red, pink, lila, violet, blue,
                     mblue, cyan, green, yellow, orange,
                     white,black};
void setup() {
  strip.Begin();
  for (uint8_t i=0; true; i++) {
    strip.SetPixelColor(0,colors[i%10]);
    strip.Show();
    delay(500);
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
