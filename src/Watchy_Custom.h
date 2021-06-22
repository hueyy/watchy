#ifndef WATCHY_BASE_H
#define WATCHY_BASE_H

#include <Watchy.h>

// include variables from config.h if it exists
#if __has_include("config.h") && __has_include(<stdint.h>)
#include "config.h"
#endif

#define BATTERY_OFFSET 0.105
#define STEP_LENGTH 45 // cm
#define MSS_24H_API_URL "http://www.weather.gov.sg/mobile/json/rest-get-24-hour-forecast.json"

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
  int8_t main_highest_temp;
  int8_t main_lowest_temp;
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
  void drawHelperGrid();
  void printCentered(uint16_t y, String text);
  void printRight(uint16_t y, String text);
  uint8_t getBattery();
  uint32_t getDistanceWalked();
  void vibrate(uint8_t times, uint32_t delay);
  MSSWeatherData getMSSWeatherData();
};

#endif