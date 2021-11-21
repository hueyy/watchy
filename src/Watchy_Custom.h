#ifndef WATCHY_CUSTOM_H
#define WATCHY_CUSTOM_H

#include <Watchy.h>
#include <WiFiManager.h>

#include "./custom_config.h"

#include "./apps/SGWeather/SGWeather.h"

#include "./assets/icons.h"
#include "./assets/zzz.h"

#include "./assets/fonts/Helvetica14pt7b.h"

// persistent data
extern RTC_DATA_ATTR bool dark_mode;

#define BATTERY_OFFSET 0.105
#define STEP_LENGTH 45 // cm
#define MSS_24H_API_URL "http://www.weather.gov.sg/mobile/json/rest-get-24-hour-forecast.json"

// button definitions
#define IS_BTN_RIGHT_UP (wakeupBit & UP_BTN_MASK)
#define IS_BTN_LEFT_UP (wakeupBit & BACK_BTN_MASK)
#define IS_BTN_RIGHT_DOWN (wakeupBit & DOWN_BTN_MASK)
#define IS_BTN_LEFT_DOWN (wakeupBit & MENU_BTN_MASK)

#define FOREGROUND_COLOUR (dark_mode ? GxEPD_WHITE : GxEPD_BLACK)
#define BACKGROUND_COLOUR (dark_mode ? GxEPD_BLACK : GxEPD_WHITE)

// additional guiState definitions
#define CUSTOM_APP_STATE 20

class WatchyCustom : public Watchy
{
public:
  WatchyCustom();

  void bumpWatchFaceIndex();
  void init(String datetime = "");

  void drawHelperGrid();
  void printCentered(uint16_t y, String text);
  void printRight(uint16_t y, String text);
  String zeroPad(uint8_t inputNum);
  String getValue(String data, char separator, int index);

  void drawSleepScreen();
  void drawWatchFace();

  // menu
  void showMenu(byte menuIndex, bool partialRefresh);
  void toggleDarkMode();

  // default apps
  void showBattery();
  void showBuzz();
  void setTime();

  // BigTime
  void bigTimeDrawWatchFace();
  void bigTimeDrawTime();
  void bigTimeDrawBattery();

  // Prose
  void proseDrawWatchFace();
  void proseDrawTime();
  void proseDrawDate();
  void proseDrawBattery();
  void proseDrawSteps();

  // Cluckent
  void cluckentDrawWatchFace();

  // Cowsay
  void cowsayDrawWatchFace();

  // apps
  // weather
  void getSGWeather();
  void showSGWeather();
  WeatherType getWeatherType(String weatherString);
  const unsigned char *getWeatherIcon(WeatherType weatherType);

  void disableWatchFace();
  bool getSleepMode();

  uint8_t getBattery();
  uint8_t getBatteryLevel();
  uint32_t getDistanceWalked();

  void vibrate(uint8_t times, uint32_t delay);
  void vibrateTime();

  void showWiFiConnectingScreen();
  bool connectToWiFi();

  void syncTime();
  void doWiFiUpdate();

  void handleButtonPress();

  void _rtcConfig(String datetime);
  void _bmaConfig();
  static uint16_t _readRegister(uint8_t address, uint8_t reg, uint8_t *data, uint16_t len);
  static uint16_t _writeRegister(uint8_t address, uint8_t reg, uint8_t *data, uint16_t len);
};

#endif