#include "../../Watchy_Custom.h"
#include "../../assets/fonts/FiraSans_Black30pt7b.h"
#include "../../assets/fonts/FiraSans_Black14pt7b.h"

const tmElements_t startElements = {
    0,
    0,
    9,
    4,
    4,
    1,
    53};
const time_t startDate = makeTime(startElements);

const tmElements_t completionElements = {
    0,
    0,
    18,
    6,
    6,
    7,
    53};
const time_t completionDate = makeTime(completionElements);
const time_t totalTime = completionDate - startDate;

void WatchyCustom::countdownDrawWatchFace()
{
  const time_t currentDate = makeTime(currentTime);
  const time_t remainingTime = completionDate - currentDate;

  countdownDrawTime(remainingTime);
  countdownDrawProgressBox(remainingTime);
}

void WatchyCustom::countdownDrawTime(const time_t remainingTime)
{
  const uint16_t remainingDays = remainingTime / (60 * 60 * 24);
  const uint32_t remainderOfDay = remainingTime % (60 * 60 * 24);
  display.fillScreen(BACKGROUND_COLOUR);
  display.setTextColor(FOREGROUND_COLOUR);

  display.setFont(&FiraSans_Black30pt7b);
  char *dayStr;
  asprintf(&dayStr, "%dd", remainingDays);
  printCentered(100, dayStr);
  free(dayStr);

  const uint8_t remainingHours = remainderOfDay / (60 * 60);
  const uint8_t remainingMinutes = (remainderOfDay % (60 * 60)) / 60;

  display.setFont(&FiraSans_Black14pt7b);
  char *timeStr;
  asprintf(&timeStr, "%dh  %dm", remainingHours, remainingMinutes);
  printCentered(150, timeStr);
  free(timeStr);
}

void WatchyCustom::countdownDrawProgressBox(const time_t remainingTime)
{
  time_t progress = ((totalTime - remainingTime) * 100 / totalTime);
  if (DEBUG_MODE)
  {
    Serial.print("progress: ");
    Serial.println(progress);
  }

  if (progress < 25)
  {
    time_t progress1 = progress * 180 / 25;
    display.fillRect(10, 10, (uint16_t)progress1, 10, FOREGROUND_COLOUR);
  }
  else if (progress >= 25 && progress < 50)
  {
    display.fillRect(10, 10, 180, 10, FOREGROUND_COLOUR);

    time_t progress2 = (progress - 25) * 170 / 25;
    display.fillRect(180, 20, 10, (uint16_t)progress2, FOREGROUND_COLOUR);
  }
  else if (progress >= 50 && progress < 75)
  {
    display.fillRect(10, 10, 180, 10, FOREGROUND_COLOUR);
    display.fillRect(180, 20, 10, 170, FOREGROUND_COLOUR);

    time_t progress3 = (progress - 50) * 180 / 25;
    display.fillRect(10 + 180 - progress3, 180, progress3, 10, FOREGROUND_COLOUR);
  }
  else if (progress >= 75 && progress < 100)
  {
    display.fillRect(10, 10, 180, 10, FOREGROUND_COLOUR);
    display.fillRect(180, 20, 10, 170, FOREGROUND_COLOUR);
    display.fillRect(10, 180, 180, 10, FOREGROUND_COLOUR);

    time_t progress4 = (progress - 75) * 170 / 25;
    display.fillRect(10, 20 + 170 - progress4, 10, progress4, FOREGROUND_COLOUR);
  }
  else
  {
    display.fillRect(10, 10, 180, 10, FOREGROUND_COLOUR);
    display.fillRect(180, 20, 10, 170, FOREGROUND_COLOUR);
    display.fillRect(10, 180, 180, 10, FOREGROUND_COLOUR);
    display.fillRect(10, 20, 10, 170, FOREGROUND_COLOUR);
  }
}