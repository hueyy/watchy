#include "../Watchy_Custom.h"
#include "../assets/cluckent_fanart.h"

void WatchyCustom::cluckentDrawWatchFace()
{
  display.fillScreen(GxEPD_BLACK);
  display.drawBitmap(0, 0, cluckent_fanart, DISPLAY_WIDTH, DISPLAY_HEIGHT, GxEPD_WHITE);
  display.setTextColor(GxEPD_BLACK);
  display.setFont(&FreeMonoBold9pt7b);
  display.setCursor(10, 170);
  if (currentTime.Hour < 10)
  {
    display.print('0');
  }
  display.print(currentTime.Hour);
  display.print(':');
  if (currentTime.Minute < 10)
  {
    display.print('0');
  }
  display.print(currentTime.Minute);
}