#include "BigTime.h"

BigTime::BigTime() {}

String zeroPad(uint8_t inputNum)
{
  if (inputNum < 10)
  {
    return "0" + String(inputNum);
  }
  return String(inputNum);
}

void BigTime::drawWatchFace()
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

  display.setCursor(25, 125 + bigfont_height);
  String dayString = zeroPad(currentTime.Day);
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
