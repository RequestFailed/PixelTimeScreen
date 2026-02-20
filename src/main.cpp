/** 
 * 这一版的程序将wifi的ssid和密码存储在了/lib/wifi_config.cpp中，请自行创建并修改。
 * 模板(wifi_config.cpp)
 * namespace wifi_config {
 *  const char* wifi_ssid = "你的wifi名称";
 *  const char* wifi_password = "你的wifi密码";
 *  const char* ntpServer = "你的ntp服务器(建议pool.ntp.org)";
 * }
 * 
 * 另外，此程序加入了在每分钟的开始(0s-5s)区间显示单词boom的实(zhi)用(zhang)小功能~
 * ps:其实很傻并且屁用没有
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

void setup() {
  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(64);
  matrix.setTextColor(matrix.Color(0xE0, 0x10, 0xFF)); // Purple

  WiFi.begin(wifi_ssid, wifi_password);
  while (WiFi.status() != WL_CONNECTED) delay(500);
  
  configTime(28800, 0, ntpServer); // 时区，夏令时，时间服务器
  // 28800 = 8小时 = 东8区
}

char previousTimeString[6] = { 0 };
char boom[4];

void loop() {
  tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    return;
  }

  char timeString[6];
  sprintf(timeString, "%02d:%02d", timeinfo.tm_hour, timeinfo.tm_min);
  sprintf(boom, "boom");
  if (strcmp(previousTimeString, timeString) != 0) { // 减少不必要的刷新
    matrix.fillScreen(0);    // 清屏
    matrix.setCursor(1, 1);
    if (timeinfo.tm_sec >= 0 && timeinfo.tm_sec <= 5) {
      matrix.print(boom);
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