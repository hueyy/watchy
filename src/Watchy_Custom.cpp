#include "Watchy_Custom.h"

WatchyCustom::WatchyCustom() {}

void WatchyCustom::drawHelperGrid()
{
  for (int i = 0; i <= 200; i += 20)
  {
    display.drawLine(i, 0, i, 200, GxEPD_BLACK);
    display.drawLine(0, i, 200, i, GxEPD_BLACK);
  }
}

// text-align: center
void WatchyCustom::printCentered(uint16_t y, String text)
{
  int16_t x1, y1;
  uint16_t w, h;

  display.getTextBounds(text, 100, 100, &x1, &y1, &w, &h);
  display.setCursor((200 - w) / 2, y);
  display.println(text);
}

// text-align: right
void WatchyCustom::printRight(uint16_t y, String text)
{
  int16_t x1, y1;
  uint16_t w, h;

  display.getTextBounds(text, 100, 100, &x1, &y1, &w, &h);
  display.setCursor(200 - w, y);
  display.println(text);
}

// taken from https://github.com/peerdavid/Watchy/blob/3a32880b93c926f6ac5d996ee8d7ebffbdfe0136/examples/WatchFaces/David/Watchy_Base.cpp#L447
uint8_t WatchyCustom::getBattery()
{
  float voltage = getBatteryVoltage() + BATTERY_OFFSET;

  uint8_t percentage = 2808.3808 * pow(voltage, 4) - 43560.9157 * pow(voltage, 3) + 252848.5888 * pow(voltage, 2) - 650767.4615 * voltage + 626532.5703;
  percentage = min((uint8_t)100, percentage);
  percentage = max((uint8_t)0, percentage);
  return percentage;
}