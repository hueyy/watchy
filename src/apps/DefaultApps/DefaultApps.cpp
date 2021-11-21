#include "../../Watchy_Custom.h"

void WatchyCustom::showBattery()
{
  display.init(0, false); //_initial_refresh to false to prevent full update on init
  display.setFullWindow();
  display.fillScreen(BACKGROUND_COLOUR);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(FOREGROUND_COLOUR);
  display.setCursor(20, 30);
  display.println("Battery Voltage:");
  float voltage = getBatteryVoltage();
  display.setCursor(70, 80);
  display.print(voltage);
  display.println("V");
  display.display(true, dark_mode);
  display.hibernate();

  guiState = APP_STATE;
}

void WatchyCustom::showBuzz()
{
  display.setFullWindow();
  display.fillScreen(BACKGROUND_COLOUR);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(FOREGROUND_COLOUR);
  display.setCursor(70, 80);
  display.println("Buzz!");
  display.display(false, dark_mode);
  Watchy::vibMotor();
  showMenu(menuIndex, false);
}

void WatchyCustom::setTime()
{

  guiState = APP_STATE;

  RTC.read(currentTime);

  int8_t minute = currentTime.Minute;
  int8_t hour = currentTime.Hour;
  int8_t day = currentTime.Day;
  int8_t month = currentTime.Month;
  int8_t year = currentTime.Year + YEAR_OFFSET - 2000;

  if (year <= 20)
  { // start at 2021
    year = 21;
  }

  int8_t setIndex = SET_HOUR;

  int8_t blink = 0;

  pinMode(DOWN_BTN_PIN, INPUT);
  pinMode(UP_BTN_PIN, INPUT);
  pinMode(MENU_BTN_PIN, INPUT);
  pinMode(BACK_BTN_PIN, INPUT);

  display.setFullWindow();

  while (1)
  {

    if (digitalRead(MENU_BTN_PIN) == 1)
    {
      setIndex++;
      if (setIndex > SET_DAY)
      {
        break;
      }
    }
    if (digitalRead(BACK_BTN_PIN) == 1)
    {
      if (setIndex != SET_HOUR)
      {
        setIndex--;
      }
    }

    blink = 1 - blink;

    if (digitalRead(DOWN_BTN_PIN) == 1)
    {
      blink = 1;
      switch (setIndex)
      {
      case SET_HOUR:
        hour == 23 ? (hour = 0) : hour++;
        break;
      case SET_MINUTE:
        minute == 59 ? (minute = 0) : minute++;
        break;
      case SET_YEAR:
        year == 99 ? (year = 20) : year++;
        break;
      case SET_MONTH:
        month == 12 ? (month = 1) : month++;
        break;
      case SET_DAY:
        day == 31 ? (day = 1) : day++;
        break;
      default:
        break;
      }
    }

    if (digitalRead(UP_BTN_PIN) == 1)
    {
      blink = 1;
      switch (setIndex)
      {
      case SET_HOUR:
        hour == 0 ? (hour = 23) : hour--;
        break;
      case SET_MINUTE:
        minute == 0 ? (minute = 59) : minute--;
        break;
      case SET_YEAR:
        year == 20 ? (year = 99) : year--;
        break;
      case SET_MONTH:
        month == 1 ? (month = 12) : month--;
        break;
      case SET_DAY:
        day == 1 ? (day = 31) : day--;
        break;
      default:
        break;
      }
    }

    display.fillScreen(BACKGROUND_COLOUR);
    display.setTextColor(FOREGROUND_COLOUR);
    display.setFont(&DSEG7_Classic_Bold_53);

    display.setCursor(5, 80);
    if (setIndex == SET_HOUR)
    { //blink hour digits
      display.setTextColor(blink ? FOREGROUND_COLOUR : BACKGROUND_COLOUR);
    }
    if (hour < 10)
    {
      display.print("0");
    }
    display.print(hour);

    display.setTextColor(FOREGROUND_COLOUR);
    display.print(":");

    display.setCursor(108, 80);
    if (setIndex == SET_MINUTE)
    { //blink minute digits
      display.setTextColor(blink ? FOREGROUND_COLOUR : BACKGROUND_COLOUR);
    }
    if (minute < 10)
    {
      display.print("0");
    }
    display.print(minute);

    display.setTextColor(FOREGROUND_COLOUR);

    display.setFont(&FreeMonoBold9pt7b);
    display.setCursor(45, 150);
    if (setIndex == SET_YEAR)
    { //blink minute digits
      display.setTextColor(blink ? FOREGROUND_COLOUR : BACKGROUND_COLOUR);
    }
    display.print(2000 + year);

    display.setTextColor(FOREGROUND_COLOUR);
    display.print("/");

    if (setIndex == SET_MONTH)
    { //blink minute digits
      display.setTextColor(blink ? FOREGROUND_COLOUR : BACKGROUND_COLOUR);
    }
    if (month < 10)
    {
      display.print("0");
    }
    display.print(month);

    display.setTextColor(FOREGROUND_COLOUR);
    display.print("/");

    if (setIndex == SET_DAY)
    { //blink minute digits
      display.setTextColor(blink ? FOREGROUND_COLOUR : BACKGROUND_COLOUR);
    }
    if (day < 10)
    {
      display.print("0");
    }
    display.print(day);
    display.display(true, dark_mode); //partial refresh
  }

  const time_t FUDGE(10); //fudge factor to allow for upload time, etc. (seconds, YMMV)
  tmElements_t tm;
  tm.Month = month;
  tm.Day = day;
  tm.Year = year + 2000 - YEAR_OFFSET; //offset from 1970, since year is stored in uint8_t
  tm.Hour = hour;
  tm.Minute = minute;
  tm.Second = 0;

  time_t t = makeTime(tm) + FUDGE;
  RTC.set(t);

  showMenu(menuIndex, false);
}