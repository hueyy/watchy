#include "../../Watchy_Custom.h"

#include "../../assets/cowsay.h"
#include "../../assets/fonts/iosevka_heavy8pt7b.h"

// 2 lines of 19 chars each
const uint8_t FORTUNE_SIZE = 12;
const String fortunes[FORTUNE_SIZE][2] = {
    {"A bird in hand is",
     "worth 2 in the bush"},
    {"A bird in the bush",
     "might have a friend"},
    {"The only constant",
     "is change."},
    {"He who hesitates",
     "is last."},
    {"All true wisdom is",
     "found on T-shirts."},
    {"Wherever you go...",
     "There you are."}, 
    {"Use the Force,",
     "Luke"},
    {"Success can cover",
     "many blunders"},
    {"Time is an illusion",
     "Lunchtime doubly so"},
    {"Nonsense wakes up",
     "the brain cells."},
    {"Fantasy is a necessary",
     "ingredient in living"},
    {"Even the very wise",
     "cannot see all ends"}};

void WatchyCustom::cowsayDrawWatchFace()
{
  display.fillScreen(FOREGROUND_COLOUR);

  display.drawBitmap(
      0,
      0,
      cowsay,
      DISPLAY_WIDTH,
      DISPLAY_HEIGHT,
      BACKGROUND_COLOUR);

  display.setTextColor(FOREGROUND_COLOUR);
  display.setFont(&iosevka_heavy8pt7b);
  display.setTextWrap(false);
  display.setCursor(23, 38);

  uint8_t normalised_hour = currentTime.Hour % 12;
  bool is_am = currentTime.Hour < 12;

  display.print(
      String(zeroPad(normalised_hour)) + ":" +
      String(zeroPad(currentTime.Minute)) +
      (is_am ? " AM" : " PM") + " " +
      dayShortStr(currentTime.Wday) + " " +
      zeroPad(currentTime.Day) + " " +
      monthShortStr(currentTime.Month));

  uint8_t fortune_index = random(0, FORTUNE_SIZE);

  for (uint8_t i = 0; i < 2; i++)
  {
    display.setCursor(23, 58 + i * 18);
    display.print(fortunes[fortune_index][i]);
  }
}