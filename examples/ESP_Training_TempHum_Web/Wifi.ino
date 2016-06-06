#include <vSAP_Auth.h>

const char* ssid = "vladiHome";
const char* password = "0888414447";
const char* sap_user = "vladiHome";
const char* sap_pass = "0888414447";

void initWifi() {
  Serial << "\nStarting Wifi to: " << WiFi.SSID() << endl;
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  if(WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("\n\nWiFi Connect Failed! Rebooting...");
    delay(1000);
    ESP.restart();
  }
  vSAP_Auth(sap_user, sap_pass);
}
