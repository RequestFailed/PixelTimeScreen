/** 
 * 改正了0.1.3中的WL OK卡住不动的bug
 * 加入了ntp连接等待状况显示
 * 加入了status标签
*/

#include <Arduino.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#include <WiFi.h>
#include "time.h"
#include "../lib/wifi_config.cpp"

using namespace wifi_config;

#define PIN 17

// Matrix Setup: 32 wide, 8 high
// NEO_MATRIX_TOP + NEO_MATRIX_LEFT: First pixel is top left
// NEO_MATRIX_COLUMNS: Pixels are arranged in columns
// NEO_MATRIX_ZIGZAG: The wiring bounces back and forth
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(32, 8, PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_LEFT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG,
  NEO_GRB            + NEO_KHZ800);

char previousTimeString[6] = {0};
char UTCTimeString[6] = {0};
char timeString[6] = {0};
String previousStatus("NONSTR");
String status("NONSTR");
tm timeinfo;

void setup() {

  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(64);
  matrix.setTextColor(matrix.Color(0xD0, 0xD0, 0xFF)); // Light Blue

  WiFi.begin(wifi_ssid, wifi_password);

  matrix.fillScreen(0);
  matrix.setCursor(1, 1);
  matrix.print("WiFi?");
  matrix.show();
  status = "FNDNET";

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  matrix.fillScreen(0);
  matrix.setCursor(1, 1);
  matrix.setTextColor(matrix.Color(0x00, 0xFF, 0x00));
  matrix.print("WL OK");
  matrix.show();
  status = "WLCONN";
  previousStatus = "FNDNET";

  delay(2000);

  configTime(28800, 0, ntpServer); // 时区，夏令时，时间服务器
  // 28800 = 8小时 = 东8区

  matrix.setTextColor(matrix.Color(0xD0, 0xD0, 0xFF)); // Light Blue
  matrix.fillScreen(0);
  matrix.setCursor(1, 1);
  matrix.print("Wait");
  matrix.show();
  while (!getLocalTime(&timeinfo)) {
    delay(500);
  }

  sprintf(timeString, "%02d:%02d", timeinfo.tm_hour, timeinfo.tm_min);
  matrix.fillScreen(0);
  matrix.setCursor(1, 1);
  matrix.print(timeString);
  matrix.show();
  status = "LOCTME";
  previousStatus = "WLCONN";

}

void loop() {

  if(!getLocalTime(&timeinfo)){
    return;
  }
  
  sprintf(timeString, "%02d:%02d", timeinfo.tm_hour, timeinfo.tm_min);
  sprintf(UTCTimeString, "%02d:%02d", (timeinfo.tm_hour-8>=0?timeinfo.tm_hour-8:timeinfo.tm_hour+16), timeinfo.tm_min);
  // utc = (utc+8)-8 + ((utc+8-8) >= 0 ? (utc+8-8) : (utc+8+24-8))

  previousStatus = status;
  matrix.fillScreen(0);    // 清屏
  matrix.setCursor(1, 1);
  
  if (timeinfo.tm_sec >= 0 && timeinfo.tm_sec <= 3) {
    matrix.print("UTC");
    status = "UTCSTR";
  } else if (timeinfo.tm_sec >= 4 && timeinfo.tm_sec <= 8) {
    matrix.print(UTCTimeString);
    status = "UTCTME";
  } else if (timeinfo.tm_sec >= 9 && timeinfo.tm_sec <= 11) {
    matrix.print("Local");
    status = "LOCSTR";
  } else {
    matrix.print(timeString);
    status = "LOCTME";
  }
  matrix.show();
  for (int i = 0; i < 6; i++) {
    previousTimeString[i] = timeString[i];
  }

  delay(100);

}