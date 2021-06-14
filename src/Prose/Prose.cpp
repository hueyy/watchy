#include "Prose.h"

Prose::Prose() {}

void Prose::drawWatchFace()
{
  display.fillScreen(GxEPD_WHITE);

  drawTime();
  drawDate();
  // drawHelperGrid();
  drawBattery();
  drawSteps();
}

void Prose::drawTime()
{
  const uint8_t normal_line_height = 20;
  const uint8_t left_padding = 0;
  const uint8_t top_padding = 35;
  const uint8_t line_spacing = 18;
  const char *hours[12] = {"twelve", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "eleven"};
  const char *minute_singles[10] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
  const char *minute_teens[10] = {"ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen"};
  const char *minute_tens[4] = {"twenty", "thirty", "forty", "fifty"};
  uint8_t lines = 0;

  display.setTextColor(GxEPD_BLACK);
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
  display.setCursor(left_padding, top_padding + lines * (normal_line_height + line_spacing));
  if (currentTime.Minute == 0)
  {
    display.print("o'clock");
  }
  else if (currentTime.Minute < 10)
  {
    display.print("oh ");
    display.print(minute_singles[currentTime.Minute]);
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
      display.setCursor(left_padding, top_padding + lines * (normal_line_height + line_spacing));
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
    display.setCursor(left_padding, top_padding + lines * (normal_line_height + line_spacing));
  }
  display.print(is_am ? "am" : "pm");
}

void Prose::drawDate()
{
  display.setTextColor(GxEPD_BLACK);
  display.setFont(&Helvetica20pt7b);
  String monthStr = monthShortStr(currentTime.Month);
  String dayOfWeek = dayShortStr(currentTime.Wday);
  char *dateStr;
  asprintf(&dateStr, "%s, %d %s", dayOfWeek.c_str(), currentTime.Day, monthStr.c_str());
  display.setCursor(0, 150);
  display.print(dateStr);
  free(dateStr);
}

void Prose::drawBattery()
{
  display.setFont(&Helvetica14pt7b);
  display.setTextColor(GxEPD_BLACK);

  int8_t bat = getBattery();
  bat = bat >= 100 ? 100 : bat;
  String batStr = String(bat);
  batStr = bat < 10 ? "0" + batStr : batStr;

  uint8_t xpos = 85;

  // display.drawBitmap(xpos, 173, battery, 37, 21, GxEPD_BLACK);
  display.setCursor(xpos + 45, 190);
  display.print(batStr + "%");
}

void Prose::drawSteps()
{
  uint32_t distanceWalked = getDistanceWalked();
  display.drawBitmap(5, 169, steps, 19, 23, GxEPD_BLACK);
  display.setCursor(32, 190);

  String stepStr = distanceWalked >= 1000 ? String((float)((distanceWalked * 10) / 10000)) + "km" : String(distanceWalked) + "m";

  display.println(stepStr);
}