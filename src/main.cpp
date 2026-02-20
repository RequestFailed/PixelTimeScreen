/** 
 * 删除了boom
 * 加入了UTC时间显示功能
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
char boom[4] = {0};
char UTC[3] = {0};
char TIME[4] = {0};
char UTCTimeString[6] = {0};

void setup() {
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(64);
  matrix.setTextColor(matrix.Color(0xE0, 0x10, 0xFF)); // Purple

  WiFi.begin(wifi_ssid, wifi_password);
  while (WiFi.status() != WL_CONNECTED) delay(500);
  
  configTime(28800, 0, ntpServer); // 时区，夏令时，时间服务器
  // 28800 = 8小时 = 东8区

  sprintf(boom, "boom");
  sprintf(UTC, "UTC");
  sprintf(TIME, "TIME");

}

void loop() {
  tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    return;
  }

  char timeString[6];
  sprintf(timeString, "%02d:%02d", timeinfo.tm_hour, timeinfo.tm_min);
  sprintf(UTCTimeString, "%02d:%02d", (timeinfo.tm_hour-8>=0?timeinfo.tm_hour-8:timeinfo.tm_hour+16), timeinfo.tm_min);

  if (strcmp(previousTimeString, timeString) != 0) { // 减少不必要的刷新
    matrix.fillScreen(0);    // 清屏
    matrix.setCursor(1, 1);
    if (timeinfo.tm_sec >= 0 && timeinfo.tm_sec <= 5) {
      matrix.print(UTC);
    } else if (timeinfo.tm_sec >= 6 && timeinfo.tm_sec <= 10) {
      matrix.print(UTCTimeString);
    } else {
      matrix.print(timeString);
    }
    matrix.show();
    for (int i = 0; i < 6; i++) {
      previousTimeString[i] = timeString[i];
    }
  }

  delay(1000); 
}