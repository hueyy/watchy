#ifndef WATCHY_BASE_H
#define WATCHY_BASE_H

#include <Watchy.h>
#include <WiFiManager.h>

#include "./custom_config.h"

#include "./assets/icons.h"
#include "./assets/logo_mss.h"
#include "./assets/zzz.h"

#include "./assets/fonts/Helvetica_Bold25pt7b.h"
#include "./assets/fonts/Helvetica25pt7b.h"
#include "./assets/fonts/Helvetica20pt7b.h"
#include "./assets/fonts/Helvetica18pt7b.h"
#include "./assets/fonts/Helvetica14pt7b.h"

#define BATTERY_OFFSET 0.105
#define STEP_LENGTH 45 // cm
#define MSS_24H_API_URL "http://www.weather.gov.sg/mobile/json/rest-get-24-hour-forecast.json"

// button definitions
#define IS_BTN_RIGHT_UP (wakeupBit & UP_BTN_MASK && guiState == WATCHFACE_STATE)
#define IS_BTN_LEFT_UP (wakeupBit & BACK_BTN_MASK && guiState == WATCHFACE_STATE)
#define IS_BTN_RIGHT_DOWN (wakeupBit & DOWN_BTN_MASK && guiState == WATCHFACE_STATE)

// additional guiState definitions
#define CUSTOM_APP_STATE 20

typedef struct MSSSubPeriod
{
  String time;
  String east;
  String west;
  String north;
  String south;
  String central;
} MSSSubPeriod;

typedef struct MSSPeriod
{
  String order;
  MSSSubPeriod morn;
  MSSSubPeriod afternoon;
  MSSSubPeriod night;
} MSSPeriod;

typedef struct MSSWeatherData
{
  String lastFetched;
  String forecast;
  String main;
  int8_t highestTemp;
  int8_t lowestTemp;
  int8_t main_humidity_high;
  int8_t main_humidity_low;
  String main_wind_direction;
  String main_wind_speed_range;
  String weather_name;
  MSSPeriod period;
} MSSWeatherData;

class WatchyCustom : public Watchy
{
public:
  WatchyCustom();

  void init(String datetime = "");

  void drawHelperGrid();
  void printCentered(uint16_t y, String text);
  void printRight(uint16_t y, String text);

  void showWatchFace(bool partialRefresh);
  void drawWatchFace();
  bool disableWatchFace();

  uint8_t getBattery();
  uint8_t getBatteryLevel();
  uint32_t getDistanceWalked();

  void vibrate(uint8_t times, uint32_t delay);
  void vibrateTime();
  bool connectWiFi();
  void disconnectWiFi();

  MSSWeatherData getMSSWeatherData();
  void showMSSWeather();
  void handleButtonPress();

private:
  void _rtcConfig(String datetime);
  void _bmaConfig();
  static uint16_t _readRegister(uint8_t address, uint8_t reg, uint8_t *data, uint16_t len);
  static uint16_t _writeRegister(uint8_t address, uint8_t reg, uint8_t *data, uint16_t len);
};

#endif