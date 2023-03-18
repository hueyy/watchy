#include "../../Watchy_Custom.h"
#include "./SGWeather.h"
#include "../../assets/fonts/iosevka_medium8pt7b.h"

SGWeather defaultWeather = {
    .north = Weather_Sunny,
    .south = Weather_Sunny,
    .east = Weather_Sunny,
    .west = Weather_Sunny,
    .central = Weather_Sunny,
    .humidity = {
        .low = 80,
        .high = 90},
    .wind = {.low = 10, .high = 20},
    .temperature = {
        .low = 25,
        .high = 33,
    },
    .timestamp = "NOT SET"};

RTC_DATA_ATTR SGWeather currentSGWeather = defaultWeather;

const unsigned char *WatchyCustom::getWeatherIcon(WeatherType weatherType)
{
  switch (weatherType)
  {
  case Weather_Sunny:
    return sunny;
  case Weather_Cloudy:
    return cloudy;
  case Weather_Rain:
    return rain;
  case Weather_PartlyCloudy:
    return cloudsun;
  default:
    return rain;
  }
}

WeatherType WatchyCustom::getWeatherType(String weatherString)
{
  const bool isRain = (weatherString == "Light Rain" || weatherString == "Showers" ||
                       weatherString == "Heavy Thundery Showers with Gusty Winds" ||
                       weatherString == "Moderate Rain" || weatherString == "Heavy Rain" ||
                       weatherString == "Thundery Showers");
  const bool isCloudy = weatherString == "Cloudy" || weatherString == "Hazy";
  const bool isPartlyCloudy = weatherString == "Partly Cloudy (Day)" || weatherString == "Partly Cloudy (Night)";
  const bool isSunny = (weatherString == "Fair (Day)" ||
                        weatherString == "Fair (Night)" ||
                        weatherString == "Fair & Warm" ||
                        weatherString == "Sunny");

  if (isRain)
  {
    return Weather_Rain;
  }
  else if (isCloudy)
  {
    return Weather_Cloudy;
  }
  else if (isPartlyCloudy)
  {
    return Weather_PartlyCloudy;
  }
  else if (isSunny)
  {
    return Weather_Sunny;
  }

  Serial.println("weatherString: " + weatherString);
  return Weather_Rain;
}

void WatchyCustom::getSGWeather()
{
  Serial.println("Syncing weather");

  HTTPClient http;
  http.setConnectTimeout(5000);
  http.begin("https://api.data.gov.sg/v1/environment/24-hour-weather-forecast");
  int httpResponseCode = http.GET();

  if (httpResponseCode == 200)
  {
    String payload = http.getString();
    JSONVar response = JSON.parse(payload);

    uint8_t period = currentTime.Hour > 16   ? 2
                     : currentTime.Hour > 10 ? 1
                                             : 0;

    JSONVar data = response["items"][0];

    ValueRange humidity = {
        .low = int8_t(int(data["general"]["relative_humidity"]["low"])),
        .high = int8_t(int(data["general"]["relative_humidity"]["high"]))};

    ValueRange wind = {
        .low = int8_t(int(data["general"]["wind"]["speed"]["low"])),
        .high = int8_t(int(data["general"]["wind"]["speed"]["high"])),
    };

    ValueRange temperature = {
        .low = int8_t(int(data["general"]["temperature"]["low"])),
        .high = int8_t(int(data["general"]["temperature"]["high"])),
    };

    String timestampRaw = String((const char *)data["timestamp"]);
    String timestamp = timestampRaw.substring(8, 10) + "/" + timestampRaw.substring(5, 7) + " " + timestampRaw.substring(11, 16);

    currentSGWeather = {
        .north = getWeatherType(String((const char *)data["periods"][period]["regions"]["north"])),
        .south = getWeatherType(String((const char *)data["periods"][period]["regions"]["south"])),
        .east = getWeatherType(String((const char *)data["periods"][period]["regions"]["east"])),
        .west = getWeatherType(String((const char *)data["periods"][period]["regions"]["west"])),
        .central = getWeatherType(String((const char *)data["periods"][period]["regions"]["central"])),
        .humidity = humidity,
        .wind = wind,
        .temperature = temperature,
        .timestamp = timestamp};
  }
  // Serial.println("currentSGWeather: " + currentSGWeather);

  http.end();
}

void WatchyCustom::showSGWeather()
{
  doWiFiUpdate();

  display.init(0, false); //_initial_refresh to false to prevent full update on init
  display.setFullWindow();
  display.fillScreen(GxEPD_WHITE);
  display.setTextColor(GxEPD_BLACK);
  display.setFont(&iosevka_medium8pt7b);

  display.setCursor(36, 30);
  display.println("NORTH");
  // display.drawBitmap(80, 12, sunny, 48, 32, GxEPD_BLACK);
  display.drawBitmap(80, 12, getWeatherIcon(currentSGWeather.north), 48, 32, GxEPD_BLACK);

  display.setCursor(15, 112);
  display.println("WEST");
  display.drawBitmap(6, 60, getWeatherIcon(currentSGWeather.west), 48, 32, GxEPD_BLACK);

  display.setCursor(159, 43);
  display.println("EAST");
  display.drawBitmap(152, 54, getWeatherIcon(currentSGWeather.east), 48, 32, GxEPD_BLACK);

  display.setCursor(128, 117);
  display.println("SOUTH");
  display.drawBitmap(80, 96, getWeatherIcon(currentSGWeather.south), 48, 32, GxEPD_BLACK);

  // central
  display.drawBitmap(80, 55, getWeatherIcon(currentSGWeather.central), 48, 32, GxEPD_BLACK);

  display.setCursor(15, 157);
  display.println(
      zeroPad(currentSGWeather.humidity.low) + String("-") + zeroPad(currentSGWeather.humidity.high) + String("%"));

  display.setCursor(110, 157);
  display.println(
      zeroPad(currentSGWeather.wind.low) + String("-") + zeroPad(currentSGWeather.wind.high) + String("km/h"));

  display.setCursor(15, 182);
  display.println(currentSGWeather.timestamp);

  display.setCursor(125, 182);
  display.println(
      zeroPad(currentSGWeather.temperature.low) + String("-") + zeroPad(currentSGWeather.temperature.high) + String(" C"));
  display.drawCircle(169, 173, 2, GxEPD_BLACK);

  customDisplay(false);
  display.hibernate();

  guiState = CUSTOM_APP_STATE;
}