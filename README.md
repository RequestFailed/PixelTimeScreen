# PixelTimeScreen 🕒

基于ESP32的网络连接LED矩阵时钟，通过NTP自动同步显示UTC和本地时间。 ⏰

## 功能特性 ✨

- **实时显示** 📱: 在32x8 NeoPixel矩阵上显示UTC和本地时间
- **网络同步** 🌐: 自动与NTP服务器同步时间
- **双时间格式** ↔️: 每隔几秒交替显示UTC和本地时间
- **视觉反馈** 👁️: 启动时显示WiFi连接状态
- **低功耗** 🔋: 为连续运行优化

## 硬件需求 ⚙️

- ESP32开发板 📟
- 32x8 NeoPixel矩阵（WS2812B或类似） ✨
- 适合LED矩阵的电源适配器（通常为5V） ⚡

## 软件依赖 💻

- PlatformIO IDE 🛠️
- Arduino框架 🧱
- Adafruit NeoPixel库 📦
- Adafruit GFX库 📦
- Adafruit NeoMatrix库 📦

## 安装 🚀

1. 克隆此仓库：
   ```bash
   git clone <repository-url>
   cd PixelTimeScreen
   ```

2. 使用PlatformIO安装依赖：
   ```bash
   pio run
   ```

3. 更新`lib/wifi_config.cpp`中的WiFi凭据：
   ```cpp
   const char* wifi_ssid = "YOUR_SSID";
   const char* wifi_password = "YOUR_PASSWORD";
   ```

4. 上传到ESP32板：
   ```bash
   pio run --target upload
   ```

## 配置 ⚙️

### WiFi设置 📶
修改`lib/wifi_config.cpp`以设置您的网络凭据：
```cpp
namespace wifi_config {
    const char* wifi_ssid = "YourNetworkName";
    const char* wifi_password = "YourPassword";
    const char* ntpServer = "pool.ntp.org";  // 用于时间同步的NTP服务器
}
```

### 时区 🌍
当前实现使用固定的偏移量（main.cpp第65行）。根据您的时区修改此值：
- 对于UTC+0：使用0
- 对于UTC+8：使用28800（8*3600秒）
- 对于UTC-5：使用-18000（-5*3600秒）

### 矩阵亮度 💡
在`setup()`函数中调整亮度（第27行）：
```cpp
matrix.setBrightness(64);  // 0-255之间的值
```

## 工作原理 ⚙️

显示器每几秒钟循环显示四个状态：

1. **UTC标签** (0-3秒) 🌐: 显示"UTC"
2. **UTC时间** (4-8秒) 🕐: 显示协调世界时
3. **本地标签** (9-11秒) 🏠: 显示"Local"
4. **本地时间** (12-59秒) 🕐: 显示本地时间

时间每秒更新并刷新显示以确保准确性。 ⏰

## 当前版本：0.1.2 🆕

### 更新日志 📝
- 修复了UTC时间冻结的问题（之前报告为"utc卡住不动的bug"） ✅
- 添加了启动时的WiFi连接动画 📶
- 改进了与NTP服务器的时间同步 🕒

## 未来增强功能 🚀

即将发布版本的计划功能：

- [ ] 🌐 基于网页的配置界面
- [ ] 🌍 多时区支持
- [ ] 🎨 可自定义的显示模式
- [ ] 🌡️ 温度和湿度显示（需传感器）
- [ ] 🔔 闹钟和通知功能
- [ ] 🎨 可自定义的颜色方案
- [ ] 课程表显示

## 故障排除 🔧

### 设备无法连接WiFi 📶
- 验证`wifi_config.cpp`中的凭据
- 确保路由器广播正确的SSID
- 检查设备附近的信号强度

### 时间不正确 ⏰
- 验证NTP服务器是否可访问
- 检查代码中的时区偏移
- 确保互联网连接

### 显示暗淡 💡
- 在`setup()`函数中调整亮度值
- 验证LED矩阵有充足的电源供应

### 显示闪烁 💫
- 检查电源连接
- 验证稳定的WiFi连接

## 贡献 🤝

1. Fork此仓库 🍴
2. 创建功能分支（`git checkout -b feature/amazing-feature`） 🌿
3. 提交您的更改（`git commit -m 'Add amazing feature'`） 💾
4. 推送到分支（`git push origin feature/amazing-feature`） 📤
5. 打开Pull Request 🔄

## 许可证 📄

此项目根据MIT许可证开源 - 详情请见LICENSE文件。

## 致谢 🙏

- Adafruit提供的优秀NeoPixel和NeoMatrix库 💖
- NTP Pool Project提供的时间同步服务 ⏰
- ESP32社区提供的硬件支持 👨‍💻

---

# PixelTimeScreen 🕒

A network-connected LED matrix clock based on ESP32 that displays both UTC and local time with automatic synchronization via NTP. ⏰

## Features ✨

- **Real-time Display** 📱: Shows both UTC and local time on a 32x8 NeoPixel matrix
- **Network Synchronization** 🌐: Automatically syncs time with NTP servers
- **Dual Time Format** ↔️: Alternates between UTC and local time display every few seconds
- **Visual Feedback** 👁️: Shows WiFi connection status during boot
- **Low Power** 🔋: Optimized for continuous operation

## Hardware Requirements ⚙️

- ESP32 Development Board 📟
- 32x8 NeoPixel Matrix (WS2812B or similar) ✨
- Power supply suitable for the LED matrix (typically 5V) ⚡

## Software Dependencies 💻

- PlatformIO IDE 🛠️
- Arduino Framework 🧱
- Adafruit NeoPixel Library 📦
- Adafruit GFX Library 📦
- Adafruit NeoMatrix Library 📦

## Installation 🚀

1. Clone this repository:
   ```bash
   git clone <repository-url>
   cd PixelTimeScreen
   ```

2. Install dependencies using PlatformIO:
   ```bash
   pio run
   ```

3. Update WiFi credentials in `lib/wifi_config.cpp`:
   ```cpp
   const char* wifi_ssid = "YOUR_SSID";
   const char* wifi_password = "YOUR_PASSWORD";
   ```

4. Upload to your ESP32 board:
   ```bash
   pio run --target upload
   ```

## Configuration ⚙️

### WiFi Settings 📶
Modify `lib/wifi_config.cpp` to set your network credentials:
```cpp
namespace wifi_config {
    const char* wifi_ssid = "YourNetworkName";
    const char* wifi_password = "YourPassword";
    const char* ntpServer = "pool.ntp.org";  // NTP server for time synchronization
}
```

### Time Zone 🌍
The current implementation uses a fixed offset of +8 hours (line 65 in main.cpp). Modify this value based on your time zone:
- For UTC+0: Use 0
- For UTC+8: Use 28800 (8*3600 seconds)
- For UTC-5: Use -18000 (-5*3600 seconds)

### Matrix Brightness 💡
Adjust brightness in the `setup()` function (line 27):
```cpp
matrix.setBrightness(64);  // Value between 0-255
```

## How It Works ⚙️

The display alternates through four states every few seconds:

1. **UTC Label** (Seconds 0-3) 🌐: Shows "UTC"
2. **UTC Time** (Seconds 4-8) 🕐: Displays coordinated universal time
3. **Local Label** (Seconds 9-11) 🏠: Shows "Local"
4. **Local Time** (Seconds 12-59) 🕐: Displays local time

The time updates every second with visual refresh to ensure accuracy. ⏰

## Current Version: 0.1.2 🆕

### Changelog 📝
- Fixed bug where UTC time would freeze (previously reported as "utc卡住不动的bug") ✅
- Added WiFi connection animation during startup 📶
- Improved time synchronization with NTP server 🕒

## Future Enhancements 🚀

Planned features for upcoming releases:

- [ ] 🌐 Web-based configuration interface
- [ ] 🌍 Multiple time zone support
- [ ] 🎨 Customizable display patterns
- [ ] 🌡️ Temperature and humidity display (with sensors)
- [ ] 🔔 Alarm and notification features
- [ ] 🎨 Customizable color schemes

## Troubleshooting 🔧

### Device won't connect to WiFi 📶
- Verify credentials in `wifi_config.cpp`
- Ensure router is broadcasting the correct SSID
- Check signal strength near the device

### Time is incorrect ⏰
- Verify NTP server is accessible
- Check time zone offset in code
- Ensure internet connectivity

### Display is dim 💡
- Adjust brightness value in `setup()` function
- Verify adequate power supply for LED matrix

### Flickering display 💫
- Check power connections
- Verify stable WiFi connection

## Contributing 🤝

1. Fork the repository 🍴
2. Create a feature branch (`git checkout -b feature/amazing-feature`) 🌿
3. Commit your changes (`git commit -m 'Add amazing feature'`) 💾
4. Push to the branch (`git push origin feature/amazing-feature`) 📤
5. Open a Pull Request 🔄

## License 📄

This project is open-source under the MIT License - see the LICENSE file for details.

## Acknowledgments 🙏

- Adafruit for the excellent NeoPixel and NeoMatrix libraries 💖
- NTP Pool Project for time synchronization services ⏰
- ESP32 community for hardware support 👨‍💻