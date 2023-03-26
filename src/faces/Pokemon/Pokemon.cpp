// Adapted from https://github.com/sqfmi/Watchy/tree/master/examples/WatchFaces/Pokemon

#include "../../Watchy_Custom.h"
#include "./pokemon_screen.h"

void WatchyCustom::drawPokemonWatchFace()
{
  display.fillScreen(BACKGROUND_COLOUR);
  display.drawBitmap(0, 0, pokemon,
                     DISPLAY_WIDTH, DISPLAY_HEIGHT,
                     FOREGROUND_COLOUR);
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