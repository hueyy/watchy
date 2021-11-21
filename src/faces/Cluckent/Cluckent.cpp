#include "../../Watchy_Custom.h"
#include "../../assets/cluckent_fanart.h"

void WatchyCustom::cluckentDrawWatchFace()
{
  display.fillScreen(FOREGROUND_COLOUR);
  display.drawBitmap(
      0,
      0,
      cluckent_fanart,
      DISPLAY_WIDTH,
      DISPLAY_HEIGHT,
      BACKGROUND_COLOUR);
  display.setTextColor(FOREGROUND_COLOUR);
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