#include "../Watchy_Custom.h"
#include "../assets/fonts/iosevka_bold40pt7b.h"
#include "../assets/fonts/iosevka_light40pt7b.h"
#include "../assets/fonts/iosevka_medium18pt7b.h"

String zeroPad(uint8_t inputNum)
{
  if (inputNum < 10)
  {
    return "0" + String(inputNum);
  }
  return String(inputNum);
}

void WatchyCustom::bigTimeDrawWatchFace()
{
  bigTimeDrawTime();
  bigTimeDrawBattery();
}

void WatchyCustom::bigTimeDrawTime()
{
  uint8_t bigfont_height = 40;
  uint8_t smallfont_height = 18;

  display.fillScreen(GxEPD_WHITE);
  display.setTextColor(GxEPD_BLACK);
  display.setFont(&iosevka_bold40pt7b);
  display.setTextWrap(false);

  String hourString = zeroPad(currentTime.Hour);
  String minuteString = zeroPad(currentTime.Minute);
  display.setCursor(0, bigfont_height + 45);
  display.print(hourString + ":" + minuteString);

  display.setCursor(30, 125 + bigfont_height);
  String dayString = zeroPad(currentTime.Day);
  display.setFont(&iosevka_light40pt7b);
  display.print(dayString);

  String dayOfWeek = dayShortStr(currentTime.Wday);
  String monthStr = monthShortStr(currentTime.Month);
  dayOfWeek.toUpperCase();
  monthStr.toUpperCase();
  display.setFont(&iosevka_medium18pt7b);

  display.setCursor(110, 117 + smallfont_height);
  display.print(monthStr);

  display.setCursor(110, 148 + smallfont_height);
  display.print(dayOfWeek);
}

void WatchyCustom::bigTimeDrawBattery()
{
  uint8_t batteryLevel = WatchyCustom::getBatteryLevel();
  uint8_t segment_height = 3;
  uint8_t segment_width = 40;
  uint8_t spacing = 10;
  for (uint8_t batterySegments = 0; batterySegments < batteryLevel; batterySegments++)
  {
    display.fillRect(
        5 + batterySegments * (segment_width + spacing),
        DISPLAY_HEIGHT - segment_height,
        segment_width,
        segment_height,
        GxEPD_BLACK);
  }
}