#ifndef WATCHY_CUSTOM_H
#define WATCHY_CUSTOM_H

// ARDUINO_WATCHY_V10
// general pins
#define ARDUINO_WATCHY_V10
#define MENU_BTN_PIN 26
#define BACK_BTN_PIN 25
#define DOWN_BTN_PIN 4
#define DISPLAY_CS 5
#define DISPLAY_RES 9
#define DISPLAY_DC 10
#define DISPLAY_BUSY 19
#define ACC_INT_1_PIN 14
#define ACC_INT_2_PIN 12
#define VIB_MOTOR_PIN 13
#define RTC_INT_PIN GPIO_NUM_27

// V10-specific pins
#define UP_BTN_PIN 32
#define BATT_ADC_PIN 33
#define UP_BTN_MASK GPIO_SEL_32
#define RTC_TYPE 1 // DS3231

// derived variables
#define MENU_BTN_MASK GPIO_SEL_26
#define BACK_BTN_MASK GPIO_SEL_25
#define DOWN_BTN_MASK GPIO_SEL_4
#define ACC_INT_MASK GPIO_SEL_14
#define BTN_PIN_MASK MENU_BTN_MASK | BACK_BTN_MASK | UP_BTN_MASK | DOWN_BTN_MASK

#include <Watchy.h>
#include <WiFiManager.h>

#include "./custom_config.h"

#include "./apps/SGWeather/SGWeather.h"

#include "./assets/icons.h"
#include "./assets/zzz.h"

#include "./assets/fonts/Helvetica14pt7b.h"

// persistent data
extern RTC_DATA_ATTR bool dark_mode;
extern RTC_DATA_ATTR tmElements_t bootTime;

#define DEBUG_MODE true

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
#define WATCHFACES_MENU_STATE 21

enum CustomBLEStatus
{
  CUSTOMBLE_CONNECTED,
  CUSTOMBLE_DISCONNECTED,
  CUSTOMBLE_UPDATING, // syncing
  CUSTOMBLE_READY,    // ready to connect
};

class WatchyCustom : public Watchy
{
public:
  using Watchy::Watchy;

  void customDisplay(bool partialUpdate);
  void interruptAlarm(bool enable);
  void bumpWatchFaceIndex();
  void init(String datetime = "");

  void drawHelperGrid();
  void printCentered(uint16_t y, String text);
  void printRight(uint16_t y, String text);
  String zeroPad(uint8_t inputNum);
  String getValue(String data, char separator, int index);

  void drawSleepScreen();
  void drawWatchFace();
  void showWatchFace(bool partialRefresh);

  // menu
  void showMenu(const char *menuItems[],
                const uint8_t menuItemsLength,
                int newGuiState,
                uint8_t menuIndex,
                bool partialRefresh);
  void showMainMenu(bool partialRefresh);
  void showWatchFacesMenu(bool partialRefresh);
  void toggleDarkMode();

  // default apps
  void showBattery();
  void showBuzz();
  void setTime();
  void showAbout();

  // WiFi
  void setupWifi();
  void showWiFiConnectingScreen();
  void showWiFiFailedScreen();
  bool connectToWiFi();
  void syncTime();
  void doWiFiUpdate();

  // BLE
  void bleConnect();
  void bleBegin();
  CustomBLEStatus bleStatus();

  // Lupine
  void lupineDrawWatchFace();

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

  // Countdown
  void countdownDrawWatchFace();
  void countdownDrawTime(const time_t remainingTime);
  void countdownDrawProgressBox(const time_t remainingTime);

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

  void handleButtonPress();

private:
  void _bmaConfig();
  static void _configModeCallback(WiFiManager *myWiFiManager);
  static uint16_t _readRegister(uint8_t address, uint8_t reg, uint8_t *data, uint16_t len);
  static uint16_t _writeRegister(uint8_t address, uint8_t reg, uint8_t *data, uint16_t len);
};

void buttonTimerStop();

#endif