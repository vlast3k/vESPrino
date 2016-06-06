#include <Wire.h>
#include <Si7021.h>
#include <Streaming.h>

SI7021 si7021;
void setup() {
Serial.begin(115200);
  si7021.begin(D1, D6); // Runs : Wire.begin() + reset()
  si7021.setHumidityRes(12); // Humidity = 12-bit / Temperature = 14-bit
}

void loop() {
  Serial << "Humidity : " << si7021.readHumidity() << " %\t";
  Serial << "Temp : "     << si7021.readTemp()     << " C";
  Serial << endl;
  delay(10000);
}
