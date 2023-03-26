#include "../../Watchy_Custom.h"
#include "../../assets/fonts/Orbitron_Black60pt7b.h"

void WatchyCustom::veryBigTimeDrawWatchFace()
{
  display.fillScreen(BACKGROUND_COLOUR);
  display.setTextColor(FOREGROUND_COLOUR);
  display.setFont(&Orbitron_Black60pt7b);
  display.setTextWrap(false);

  printRight(90, 10, String(currentTime.Hour));

  String minuteString = zeroPad(currentTime.Minute);
  printRight(190, 10, minuteString);
}