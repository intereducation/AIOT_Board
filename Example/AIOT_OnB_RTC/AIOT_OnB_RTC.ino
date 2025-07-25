#include "I2C_BM8563.h"
#include <WiFi.h>

// RTC BM8563 I2C port
#define BM8563_I2C_SDA 4
#define BM8563_I2C_SCL 5

const char *ssid = "IES-Internal";       //WiFi network name
const char *password = "Education1999";  //WiFi network password

I2C_BM8563 rtc(I2C_BM8563_DEFAULT_ADDRESS, Wire1);

const char* ntpServer = "time.cloudflare.com";

void setup() {
  // Init Serial
  Serial.begin(115200);
  delay(50);

  // Connect to an access point
  WiFi.begin(ssid, password);  // Or, Connect to the specified access point

  Serial.print("Connecting to Wi-Fi ");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println(" CONNECTED");

  // Set ntp time to local
  configTime(7 * 3600, 0, ntpServer);

  // Init I2C
  Wire1.begin(BM8563_I2C_SDA, BM8563_I2C_SCL);

  // Init RTC
  rtc.begin();

  // Get local time
  struct tm timeInfo;
  if (getLocalTime(&timeInfo)) {
    // Set RTC time
    I2C_BM8563_TimeTypeDef timeStruct;
    timeStruct.hours   = timeInfo.tm_hour;
    timeStruct.minutes = timeInfo.tm_min;
    timeStruct.seconds = timeInfo.tm_sec;
    rtc.setTime(&timeStruct);

    // Set RTC Date
    I2C_BM8563_DateTypeDef dateStruct;
    dateStruct.weekDay = timeInfo.tm_wday;
    dateStruct.month   = timeInfo.tm_mon + 1;
    dateStruct.date    = timeInfo.tm_mday;
    dateStruct.year    = timeInfo.tm_year + 1900;
    rtc.setDate(&dateStruct);
  }
}

void loop() {
  I2C_BM8563_DateTypeDef dateStruct;
  I2C_BM8563_TimeTypeDef timeStruct;

  // Get RTC
  rtc.getDate(&dateStruct);
  rtc.getTime(&timeStruct);

  // Print RTC
  Serial.printf("%04d/%02d/%02d %02d:%02d:%02d\n",
                dateStruct.year,
                dateStruct.month,
                dateStruct.date,
                timeStruct.hours,
                timeStruct.minutes,
                timeStruct.seconds
               );

  // Wait
  delay(1000);
}