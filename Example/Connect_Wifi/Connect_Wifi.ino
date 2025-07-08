// การใช้งาน "Wifi"
#include <WiFi.h>
#include <PubSubClient.h>

const char *ssid = "WIFI_NAME";       //WiFi network name
const char *password = "PASSWORD";  //WiFi network password

void setup() {
  Serial.begin(115200);
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  digitalWrite(WIFI_LED, LOW);
}

void loop() {
  
}
