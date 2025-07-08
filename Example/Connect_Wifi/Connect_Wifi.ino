// การใช้งาน "Wifi"
#include <WiFi.h>
#include <PubSubClient.h>

const char *ssid = "WIFI_NAME";       //WiFi network name
const char *password = "PASSWORD";  //WiFi network password

WiFiClient espClient;
PubSubClient client(espClient);

void mqttReconnect() {
  while (!client.connected()) {
    if (client.connect(mqtt_Client, mqtt_username, mqtt_password)) {
      client.subscribe("@msg/#");
    } else
      delay(5000);
  }
}

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
