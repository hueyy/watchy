#include "Prose.h"

Prose::Prose() {}

void Prose::drawWatchFace()
{
  const uint16_t line_height = 35;
  const uint16_t padding = 10;
  const char *hours[12] = {"twelve", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "eleven"};
  const char *minute_singles[10] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
  const char *minute_teens[10] = {"ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
  const char *minute_tens[4] = {"twenty", "thirty", "forty", "fifty"};
  uint16_t lines = 0;

  display.fillScreen(GxEPD_WHITE);
  display.setTextColor(GxEPD_BLACK);
  display.setFont(&Helvetica_Bold25pt7b);
  display.setTextWrap(false);

  uint16_t normalised_hour = currentTime.Hour % 12;
  bool is_am = currentTime.Hour < 12;

  // hour
  lines++;
  display.setCursor(padding, lines * (padding + line_height));
  display.print(hours[normalised_hour]);

  // minutes
  lines++;
  display.setFont(&Helvetica25pt7b);
  display.setCursor(padding, lines * (padding + line_height));
  if (currentTime.Minute == 0)
  {
    display.print("o'clock");
  }
  else if (currentTime.Minute < 10)
  {
    display.print("oh");
    lines++;
    display.setCursor(padding, lines * (padding + line_height));
    display.print(minute_singles[currentTime.Minute]);
  }
  else if (currentTime.Minute < 20)
  {
    display.print(minute_teens[currentTime.Minute - 10]);
  }
  else
  {
    display.print(minute_tens[(currentTime.Minute / 10) - 2]);
    lines++;
    display.setCursor(padding, lines * (padding + line_height));
    display.print(minute_singles[(currentTime.Minute % 10) - 1]);
  }

  // am / pm
  lines++;
  display.setCursor(10, lines * (padding + line_height));
  display.print(is_am ? "am" : "pm");

  // debug
  // display.setFont(&FreeMonoBold9pt7b);
  // display.setCursor(150, 170);
  // display.print(currentTime.Hour);
  // display.print(":");
  // display.print(currentTime.Minute);
}