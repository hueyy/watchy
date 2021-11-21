#include "../../Watchy_Custom.h"
#include "../../assets/fonts/FiraSans_Black30pt7b.h"
#include "../../assets/fonts/FiraSans_Black14pt7b.h"
#include "../../assets/lupine_mountains.h"

void WatchyCustom::lupineDrawWatchFace()
{
  display.fillScreen(FOREGROUND_COLOUR);

  // draw mountains
  display.drawBitmap(
      0,
      0,
      lupine_mountains,
      DISPLAY_WIDTH,
      DISPLAY_HEIGHT,
      BACKGROUND_COLOUR);

  // draw time
  display.setTextColor(FOREGROUND_COLOUR);
  display.setFont(&FiraSans_Black30pt7b);
  String hourString = zeroPad(currentTime.Hour);
  String minuteString = zeroPad(currentTime.Minute);
  display.setCursor(30, 56);
  display.print(hourString + ":" + minuteString);
  // printCentered(46, hourString + ":" + minuteString);

  // draw date
  display.setTextColor(BACKGROUND_COLOUR);
  String monthStr = monthShortStr(currentTime.Month);
  String dayOfWeek = dayShortStr(currentTime.Wday);
  char *dateStr;
  asprintf(&dateStr, "%s, %d %s", dayOfWeek.c_str(), currentTime.Day, monthStr.c_str());
  display.setFont(&FiraSans_Black14pt7b);
  printCentered(185, dateStr);
  free(dateStr);
}
