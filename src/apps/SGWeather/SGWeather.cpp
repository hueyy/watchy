#include "../../Watchy_Custom.h"
#include "./SGWeather.h"
#include "../../assets/fonts/iosevka_medium8pt7b.h"

const unsigned char* WatchyCustom::getWeatherIcon(WeatherType weatherType){
  switch(weatherType){
    case Weather_Sunny:
      return sunny;
    case Weather_Cloudy:
      return cloudy;
    case Weather_Rain:
      return rain;
    case Weather_PartlyCloudy:
      return cloudsun;
  }
}

void WatchyCustom::showSGWeather()
{
  display.init(0, false); //_initial_refresh to false to prevent full update on init
  display.setFullWindow();
  display.fillScreen(GxEPD_WHITE);
  display.setTextColor(GxEPD_BLACK);
  display.setFont(&iosevka_medium8pt7b);

  ValueRange humidity = {
    .low = 80,
    .high = 90
  };

  ValueRange wind = {
    .low = 10,
    .high = 20
  };

  ValueRange temperature = {
    .low = 25,
    .high = 33,
  };

  SGWeather currentWeather = {
    .north = Weather_Sunny,
    .south = Weather_Sunny,
    .east = Weather_Sunny,
    .west = Weather_Sunny,
    .humidity = humidity,
    .wind = wind,
    .temperature = temperature,
    .timestamp = "08/03 09:06"
  };

  display.setCursor(36, 30);
  display.println("NORTH");
  display.drawBitmap(80, 12, sunny, 48, 32, GxEPD_BLACK);
  // display.drawBitmap(80, 12, getWeatherIcon(currentWeather.north), 48, 32, GxEPD_BLACK);

  display.setCursor(15, 112);
  display.println("WEST");
  display.drawBitmap(6, 60, sunny, 48, 32, GxEPD_BLACK);
  // display.drawBitmap(6, 60, getWeatherIcon(currentWeather.west), 48, 32, GxEPD_BLACK);

  display.setCursor(159, 43);
  display.println("EAST");
  display.drawBitmap(152, 54, sunny, 48, 32, GxEPD_BLACK);

  display.setCursor(124, 117);
  display.println("SOUTH");
  display.drawBitmap(80, 96, sunny, 48, 32, GxEPD_BLACK);

  display.setCursor(15, 157);
  display.println(
    zeroPad(currentWeather.humidity.low)
    + String("-")
    + zeroPad(currentWeather.humidity.high)
    + String("%"));

  display.setCursor(110, 157);
  display.println(
    zeroPad(currentWeather.wind.low)
    + String("-")
    + zeroPad(currentWeather.wind.high)
    + String("km/h"));

  display.setCursor(15, 182);
  display.println(currentWeather.timestamp);

  display.setCursor(125, 182);
  display.println(
    zeroPad(currentWeather.temperature.low)
    + String("-")
    + zeroPad(currentWeather.temperature.high)
    + String(" C"));
  display.drawCircle(170, 173, 2, GxEPD_BLACK);

  display.display(false);
  display.hibernate();

  guiState = CUSTOM_APP_STATE;
}