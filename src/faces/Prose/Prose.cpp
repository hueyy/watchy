#include "../../Watchy_Custom.h"

#include "../../assets/fonts/Helvetica_Bold25pt7b.h"
#include "../../assets/fonts/Helvetica25pt7b.h"
#include "../../assets/fonts/Helvetica20pt7b.h"
#include "../../assets/fonts/Helvetica18pt7b.h"

void WatchyCustom::proseDrawWatchFace()
{
  display.fillScreen(BACKGROUND_COLOUR);

  proseDrawTime();
  proseDrawDate();
  proseDrawBattery();
  proseDrawSteps();
}

void WatchyCustom::proseDrawTime()
{
  const uint8_t normal_line_height = 20;
  const uint8_t left_padding = 0;
  const uint8_t top_padding = 35;
  const uint8_t line_spacing = 18;
  const uint8_t second_line_padding = 5;
  const char *hours[12] = {"twelve", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "eleven"};
  const char *minute_singles[10] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
  const char *minute_teens[10] = {"ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
  const char *minute_tens[4] = {"twenty", "thirty", "forty", "fifty"};
  uint8_t lines = 0;

  display.setTextColor(FOREGROUND_COLOUR);
  display.setFont(&Helvetica_Bold25pt7b);
  display.setTextWrap(false);

  uint8_t normalised_hour = currentTime.Hour % 12;
  bool is_am = currentTime.Hour < 12;

  // hour
  display.setCursor(left_padding, top_padding);
  display.print(hours[normalised_hour]);

  // minutes
  lines++;
  display.setFont(&Helvetica20pt7b);
  display.setCursor(
      left_padding,
      top_padding + lines * (normal_line_height + line_spacing) + second_line_padding);
  if (currentTime.Minute == 0)
  {
    display.print("o'clock");
  }
  else if (currentTime.Minute < 10)
  {
    display.print("oh ");
    display.print(minute_singles[currentTime.Minute - 1]);
  }
  else if (currentTime.Minute < 20)
  {
    display.print(minute_teens[currentTime.Minute - 10]);
  }
  else
  {
    display.print(minute_tens[(currentTime.Minute / 10) - 2]);
    if (currentTime.Minute % 10 != 0)
    {
      lines++;
      display.setCursor(
          left_padding,
          top_padding + lines * (normal_line_height + line_spacing) + second_line_padding);
      display.print(minute_singles[(currentTime.Minute % 10) - 1]);
    }
  }

  // am / pm
  if (lines == 2)
  {
    display.print(" ");
  }
  else if (lines == 1)
  {
    lines++;
    display.setCursor(
        left_padding,
        top_padding + lines * (normal_line_height + line_spacing) + second_line_padding);
  }
  display.print(is_am ? "am" : "pm");
}

void WatchyCustom::proseDrawDate()
{
  display.setTextColor(FOREGROUND_COLOUR);
  display.setFont(&Helvetica18pt7b);
  String monthStr = monthShortStr(currentTime.Month);
  String dayOfWeek = dayShortStr(currentTime.Wday);
  char *dateStr;
  asprintf(&dateStr, "%s, %d %s", dayOfWeek.c_str(), currentTime.Day, monthStr.c_str());
  display.setCursor(0, 160);
  display.print(dateStr);
  free(dateStr);
}

void WatchyCustom::proseDrawBattery()
{
  display.setFont(&Helvetica14pt7b);
  display.setTextColor(FOREGROUND_COLOUR);

  int8_t bat = getBattery();
  bat = bat >= 100 ? 100 : bat;
  String batStr = String(bat);
  batStr = bat < 10 ? "0" + batStr : batStr;

  uint8_t xpos = 85;

  display.setCursor(xpos + 45, 190);
  display.print(batStr + "%");
}

void WatchyCustom::proseDrawSteps()
{
  uint32_t distanceWalked = getDistanceWalked();
  display.setCursor(0, 190);

  String stepStr = distanceWalked >= (1000 * 100)
                       ? String((float)(distanceWalked * 100) / 10000000) + "km"
                       : String(distanceWalked / 100) + "m";

  display.println(stepStr);
}