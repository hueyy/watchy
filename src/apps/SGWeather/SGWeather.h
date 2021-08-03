#ifndef SG_WEATHER
#define SG_WEATHER

enum WeatherType {
  Weather_Sunny,
  Weather_Cloudy,
  Weather_Rain,
  Weather_PartlyCloudy
};

typedef struct ValueRange {
  int8_t low;
  int8_t high;
} ValueRange;

typedef struct SGWeather {
  WeatherType north;
  WeatherType south;
  WeatherType east;
  WeatherType west;
  WeatherType central;
  ValueRange humidity;
  ValueRange wind;
  ValueRange temperature;
  String timestamp;
} SGWeather;

#endif