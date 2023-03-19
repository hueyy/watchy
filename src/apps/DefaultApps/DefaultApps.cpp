#include "../../Watchy_Custom.h"

void WatchyCustom::toggleDarkMode()
{
  dark_mode = !dark_mode;
  showMainMenu(false);
}

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
  customDisplay(true);
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
  customDisplay(false);
  Watchy::vibMotor();
  showMainMenu(false);
}

void WatchyCustom::setTime()
{

  guiState = APP_STATE;

  RTC.read(currentTime);

  int8_t minute = currentTime.Minute;
  int8_t hour = currentTime.Hour;
  int8_t day = currentTime.Day;
  int8_t month = currentTime.Month;
  int8_t year = currentTime.Year + YEAR_OFFSET_DS - 2000;

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
    { // blink hour digits
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
    { // blink minute digits
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
    { // blink minute digits
      display.setTextColor(blink ? FOREGROUND_COLOUR : BACKGROUND_COLOUR);
    }
    display.print(2000 + year);

    display.setTextColor(FOREGROUND_COLOUR);
    display.print("/");

    if (setIndex == SET_MONTH)
    { // blink minute digits
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
    { // blink minute digits
      display.setTextColor(blink ? FOREGROUND_COLOUR : BACKGROUND_COLOUR);
    }
    if (day < 10)
    {
      display.print("0");
    }
    display.print(day);
    customDisplay(true); // partial refresh
  }

  tmElements_t tm;
  tm.Month = month;
  tm.Day = day;
  tm.Year = y2kYearToTm(year);
  tm.Hour = hour;
  tm.Minute = minute;
  tm.Second = 0;

  RTC.set(tm);

  showMainMenu(false);
}

void WatchyCustom::bleConnect()
{
  display.init(0, false);
  display.setFullWindow();
  display.fillScreen(BACKGROUND_COLOUR);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(FOREGROUND_COLOUR);
  display.setCursor(20, 30);
  display.println("BLUETOOTH");

  bleBegin();

  customDisplay(true);
  display.hibernate();
  guiState = APP_STATE;

  CustomBLEStatus status = CUSTOMBLE_READY;

  while (1)
  {
    status = bleStatus();
    switch (status)
    {
    case CUSTOMBLE_READY:
      display.fillScreen(BACKGROUND_COLOUR);
      display.setFont(&FreeMonoBold9pt7b);
      display.setTextColor(FOREGROUND_COLOUR);
      display.setCursor(20, 30);
      display.println("DISCOVERABLE");
      customDisplay(true);
      delay(2000);
      break;

    case CUSTOMBLE_CONNECTED:
      display.fillScreen(BACKGROUND_COLOUR);
      display.setFont(&FreeMonoBold9pt7b);
      display.setTextColor(FOREGROUND_COLOUR);
      display.setCursor(20, 30);
      display.println("CONNECTED");
      customDisplay(true);
      break;

    case CUSTOMBLE_DISCONNECTED:
      display.fillScreen(BACKGROUND_COLOUR);
      display.setFont(&FreeMonoBold9pt7b);
      display.setTextColor(FOREGROUND_COLOUR);
      display.setCursor(20, 30);
      display.println("DISCONNECTED");
      customDisplay(true);
      break;

    case CUSTOMBLE_UPDATING:
      display.fillScreen(BACKGROUND_COLOUR);
      display.setFont(&FreeMonoBold9pt7b);
      display.setTextColor(FOREGROUND_COLOUR);
      display.setCursor(20, 30);
      display.println("SYNCING");
      customDisplay(true);
      break;
    }
    delay(100);
  }

  WiFi.mode(WIFI_OFF);
  btStop();
  showMainMenu(false);
}

void WatchyCustom::showAbout()
{
  display.setFullWindow();
  display.fillScreen(BACKGROUND_COLOUR);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(FOREGROUND_COLOUR);
  display.setCursor(0, 20);

  display.print("LibVer: ");
  display.println(WATCHY_LIB_VER);

  const char *RTC_HW[3] = {"<UNKNOWN>", "DS3231", "PCF8563"};
  display.print("RTC: ");
  display.println(RTC_HW[RTC.rtcType]); // 0 = UNKNOWN, 1 = DS3231, 2 = PCF8563

  display.print("Batt: ");
  float voltage = getBatteryVoltage();
  display.print(voltage);
  display.println("V");

  display.print("Uptime: ");
  RTC.read(currentTime);
  time_t b = makeTime(bootTime);
  time_t c = makeTime(currentTime);
  int totalSeconds = c - b;
  // int seconds = (totalSeconds % 60);
  int minutes = (totalSeconds % 3600) / 60;
  int hours = (totalSeconds % 86400) / 3600;
  int days = (totalSeconds % (86400 * 30)) / 86400;
  display.print(days);
  display.print("d");
  display.print(hours);
  display.print("h");
  display.print(minutes);
  display.print("m");
  display.display(false); // full refresh

  guiState = APP_STATE;
}