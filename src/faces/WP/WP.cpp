#include "../../Watchy_Custom.h"
#include "./wp_bg.h"
#include "../../assets/fonts/FiraSans_Black30pt7b.h"

void WatchyCustom::WPDrawWatchFace()
{
  display.fillScreen(BACKGROUND_COLOUR);
  display.drawBitmap(10, 10, wp_bg, 180, 129, FOREGROUND_COLOUR);

  display.setTextColor(FOREGROUND_COLOUR);
  display.setTextWrap(false);
  display.setFont(&FiraSans_Black30pt7b);

  String hourString = String(currentTime.Hour);
  String minuteString = zeroPad(currentTime.Minute);
  printCentered(190, hourString + ":" + minuteString);
}