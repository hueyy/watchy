#include "Watchy_Custom.h"

GxEPD2_BW<GxEPD2_154_D67_Custom, GxEPD2_154_D67_Custom::HEIGHT> Watchy::display(GxEPD2_154_D67_Custom(CS, DC, RESET, BUSY));

RTC_DATA_ATTR bool dark_mode = false;
RTC_DATA_ATTR bool sleep_mode = false;
RTC_DATA_ATTR bool DEBUG_MODE = true;

RTC_DATA_ATTR int8_t watchface_index = 0;
RTC_DATA_ATTR int8_t timeSyncCounter = TIME_SYNC_INTERVAL;
RTC_DATA_ATTR int8_t sgWeatherCounter = SG_WEATHER_SYNC_INTERVAL;

int8_t max_watchfaces_count = 3;

WatchyCustom::WatchyCustom() {}

void WatchyCustom::init(String datetime)
{
  Serial.begin(115200);

  esp_sleep_wakeup_cause_t wakeup_reason;
  wakeup_reason = esp_sleep_get_wakeup_cause(); //get wake up reason
  Wire.begin(SDA, SCL);                         //init i2c

  switch (wakeup_reason)
  {
  case ESP_SLEEP_WAKEUP_TIMER: //ESP Internal RTC
    if (guiState == WATCHFACE_STATE)
    {
      RTC.read(currentTime);
      currentTime.Minute++;
      tmElements_t tm;
      tm.Month = currentTime.Month;
      tm.Day = currentTime.Day;
      tm.Year = currentTime.Year;
      tm.Hour = currentTime.Hour;
      tm.Minute = currentTime.Minute;
      tm.Second = 0;
      time_t t = makeTime(tm);
      RTC.set(t);
      RTC.read(currentTime);
      showWatchFace(true); //partial updates on tick
    }
    timeSyncCounter++;
    sgWeatherCounter++;
    doWiFiUpdate();
    break;
  case ESP_SLEEP_WAKEUP_EXT0: //RTC Alarm
    RTC.alarm(ALARM_2);
    if (guiState == WATCHFACE_STATE)
    {
      RTC.read(currentTime);
      if (currentTime.Hour == SLEEP_HOUR_START && currentTime.Minute == SLEEP_MINUTE_START)
      {
        sleep_mode = true;
        RTC.alarmInterrupt(ALARM_2, false);
      }
      showWatchFace(true); //partial updates on tick
    }
    break;
  case ESP_SLEEP_WAKEUP_EXT1:
    if (sleep_mode)
    {
      sleep_mode = false;
      RTC.alarmInterrupt(ALARM_2, true);
      showWatchFace(false);
    }
    else
    {
      handleButtonPress();
    }
    break;
  default:
    _rtcConfig(datetime);
    _bmaConfig();
    showWatchFace(false); //full update on reset
    break;
  }
  deepSleep();
}

void WatchyCustom::bumpWatchFaceIndex()
{
  if (watchface_index == max_watchfaces_count)
  {
    watchface_index = 0;
  }
  else
  {
    watchface_index++;
  }
}

void WatchyCustom::disableWatchFace()
{
  RTC.alarmInterrupt(ALARM_2, false);
}

bool WatchyCustom::getSleepMode()
{
  return sleep_mode;
}

void WatchyCustom::drawSleepScreen()
{
  display.drawBitmap(0, 0, zzz_image, DISPLAY_WIDTH, DISPLAY_HEIGHT, GxEPD_WHITE);
}

void WatchyCustom::drawWatchFace()
{
  if (sleep_mode)
  {
    drawSleepScreen();
    return;
  }

  switch (watchface_index)
  {
  case 0:
    bigTimeDrawWatchFace();
    break;
  case 1:
    proseDrawWatchFace();

    break;
  case 2:
    cluckentDrawWatchFace();
    break;
  case 3:
    cowsayDrawWatchFace();
    break;
  default:
    Watchy::drawWatchFace();
    break;
  }
}

// taken from https://github.com/peerdavid/Watchy/blob/3a32880b93c926f6ac5d996ee8d7ebffbdfe0136/examples/WatchFaces/David/Watchy_Base.cpp#L447
uint8_t WatchyCustom::getBattery()
{
  float voltage = getBatteryVoltage() + BATTERY_OFFSET;

  uint8_t percentage = 2808.3808 * pow(voltage, 4) - 43560.9157 * pow(voltage, 3) + 252848.5888 * pow(voltage, 2) - 650767.4615 * voltage + 626532.5703;
  percentage = min((uint8_t)100, percentage);
  percentage = max((uint8_t)0, percentage);
  return percentage;
}

uint8_t WatchyCustom::getBatteryLevel()
{
  // from 1 - 4
  float voltage = getBatteryVoltage();

  if (voltage > 4.1)
  {
    return 4;
  }
  else if (voltage > 3.95)
  {
    return 3;
  }
  else if (voltage > 3.80)
  {
    return 2;
  }
  else
  {
    return 1;
  }
}

uint32_t WatchyCustom::getDistanceWalked()
{
  uint32_t stepCount = sensor.getCounter();
  return (stepCount * STEP_LENGTH);
}

void WatchyCustom::vibrate(uint8_t times, uint32_t delay_duration)
{
  sensor.enableFeature(BMA423_WAKEUP, false);

  pinMode(VIB_MOTOR_PIN, OUTPUT);
  for (uint8_t i = 0; i < times; i++)
  {
    delay(delay_duration);
    digitalWrite(VIB_MOTOR_PIN, true);
    delay(delay_duration);
    digitalWrite(VIB_MOTOR_PIN, false);
  }

  sensor.enableFeature(BMA423_WAKEUP, true);
}

void WatchyCustom::vibrateTime()
{
  uint8_t twelveHour = currentTime.Hour > 12
                           ? currentTime.Hour - 12
                           : currentTime.Hour;
  vibrate(twelveHour, 250);

  uint8_t quarterHour = currentTime.Minute / 15;
  vibrate((currentTime.Minute + 14) / 15, 500);
}

bool WatchyCustom::connectToWiFi()
{
  int remaining_tries = 3;
  WIFI_CONFIGURED = false;

  while (remaining_tries > 0)
  {
    for (unsigned int i = 0; i < 2; i++)
    {
      const char *ssid = i == 0 ? WIFI_SSID1
                                : WIFI_SSID2;
      const char *pass = i == 0 ? WIFI_PASS1
                                : WIFI_PASS2;
      Serial.println("Attempt to connect to WiFi: " + String(ssid) + " | " + String(pass));
      WiFi.begin(ssid, pass);
      Serial.println("WiFi began");
      WIFI_CONFIGURED = (WiFi.waitForConnectResult() == WL_CONNECTED);

      if (WIFI_CONFIGURED)
      {
        break;
      }
    }

    if (WIFI_CONFIGURED)
    {
      break;
    }
    remaining_tries--;
  }

  Serial.println("WIFI_CONFIGURED: " + WIFI_CONFIGURED);
  return WIFI_CONFIGURED;
}

void WatchyCustom::syncTime()
{
  Serial.println("Syncing time...");

  struct tm timeinfo;

  //get NTP Time
  configTime(GMT_OFFSET_SEC, DAYLIGHT_OFFSET_SEC, NTP_SERVER);
  delay(4000); //delay 4 secods so configTime can finish recieving the time from the internet
  getLocalTime(&timeinfo);

  // convert NTP time into proper format
  tmElements_t tm;
  tm.Month = timeinfo.tm_mon + 1; // 0-11 based month so we have to add 1
  tm.Day = timeinfo.tm_mday;
  tm.Year = timeinfo.tm_year + 1900 - YEAR_OFFSET; //offset from 1970, since year is stored in uint8_t
  tm.Hour = timeinfo.tm_hour;
  tm.Minute = timeinfo.tm_min;
  tm.Second = timeinfo.tm_sec;
  time_t t = makeTime(tm);

  //set the RTC time to the NTP time
  Serial.println("Setting time to: " + String(t));
  RTC.set(t);
}

void WatchyCustom::showWiFiConnectingScreen()
{
  display.fillScreen(FOREGROUND_COLOUR);
  display.setTextColor(FOREGROUND_COLOUR);
  display.setFont(&Helvetica14pt7b);
  printCentered(100, "Connecting to WiFi...");
}

void WatchyCustom::doWiFiUpdate()
{
  // update all the things that should be updated via WiFi
  bool shouldSyncTime = timeSyncCounter >= TIME_SYNC_INTERVAL && TIME_SYNC_INTERVAL != 0;
  bool shouldGetWeather = sgWeatherCounter >= SG_WEATHER_SYNC_INTERVAL && SG_WEATHER_SYNC_INTERVAL != 0;
  bool wifiNeeded = shouldSyncTime && shouldGetWeather;

  if (wifiNeeded)
  {
    showWiFiConnectingScreen();
    connectToWiFi();
    showWatchFace(false);
  }

  if (!WIFI_CONFIGURED)
  {
    Serial.println("Failed to connect to WiFi");
    return;
  }

  if (shouldSyncTime)
  {
    syncTime();
    timeSyncCounter = 0;
  }

  if (shouldGetWeather)
  {
    getSGWeather();
    sgWeatherCounter = 0;
  }

  WIFI_CONFIGURED = false;
  WiFi.disconnect();
  WiFi.mode(WIFI_OFF);
}

const char *menuItems[] = {
    "Check Battery",
    "Vibrate Motor",
    "Show Accelerometer",
    "Toggle Dark Mode",
    "Set Time",
    "Setup WiFi",
    "Update Firmware"};
int16_t menuOptions = sizeof(menuItems) / sizeof(menuItems[0]);

void WatchyCustom::showMenu(byte menuIndex, bool partialRefresh)
{
  // https://gitlab.com/astory024/watchy/-/blob/master/src/Watchy.cpp
  display.init(0, false); //_initial_refresh to false to prevent full update on init
  display.setFullWindow();
  display.fillScreen(BACKGROUND_COLOUR);
  display.setFont(&FreeMonoBold9pt7b);

  int16_t x1, y1;
  uint16_t w, h;
  int16_t yPos;
  int16_t startPos = 0;

  //Code to move the menu if current selected index out of bounds
  if (menuIndex + MENU_LENGTH > menuOptions)
  {
    startPos = (menuOptions - 1) - (MENU_LENGTH - 1);
  }
  else
  {
    startPos = menuIndex;
  }
  for (int i = startPos; i < MENU_LENGTH + startPos; i++)
  {
    yPos = 30 + (MENU_HEIGHT * (i - startPos));
    display.setCursor(0, yPos);
    if (i == menuIndex)
    {
      display.getTextBounds(menuItems[i], 0, yPos, &x1, &y1, &w, &h);
      display.fillRect(x1 - 1, y1 - 10, 200, h + 15, FOREGROUND_COLOUR);
      display.setTextColor(BACKGROUND_COLOUR);
      display.println(menuItems[i]);
    }
    else
    {
      display.setTextColor(FOREGROUND_COLOUR);
      display.println(menuItems[i]);
    }
  }

  display.display(partialRefresh);

  guiState = MAIN_MENU_STATE;
}

void WatchyCustom::toggleDarkMode()
{
  dark_mode = !dark_mode;
  showMenu(menuIndex, false);
}

void WatchyCustom::handleButtonPress()
{
  uint64_t wakeupBit = esp_sleep_get_ext1_wakeup_status();

  if (guiState == WATCHFACE_STATE)
  {
    if (IS_BTN_RIGHT_UP)
    {
      RTC.read(currentTime);
      vibrateTime();
      return;
    }
    else if (IS_BTN_RIGHT_DOWN)
    {
      bumpWatchFaceIndex();
      RTC.alarm(ALARM_2);
      RTC.read(currentTime);
      showWatchFace(false);
      return;
    }
    else if (IS_BTN_LEFT_UP)
    {
      // showSGWeather();
      return;
    }
    else if (IS_BTN_LEFT_DOWN)
    {
      showMenu(menuIndex, true);
      return;
    }
  }
  else if (guiState == MAIN_MENU_STATE)
  {
    if (IS_BTN_LEFT_DOWN)
    {
      switch (menuIndex)
      {
      case 0:
        showBattery();
        break;
      case 1:
        Watchy::showBuzz();
        break;
      case 2:
        Watchy::showAccelerometer();
        break;
      case 3:
        toggleDarkMode();
        break;
      case 4:
        Watchy::setTime();
        break;
      case 5:
        Watchy::setupWifi();
        break;
      case 6:
        Watchy::showUpdateFW();
        break;
      default:
        break;
      }
      return;
    }
    else if (IS_BTN_RIGHT_UP)
    {
      menuIndex--;
      if (menuIndex < 0)
      {
        menuIndex = menuOptions - 1;
      }
      showMenu(menuIndex, true);
    }
    else if (IS_BTN_RIGHT_DOWN)
    {
      menuIndex++;
      if (menuIndex >= menuOptions)
      {
        menuIndex = 0;
      }
      showMenu(menuIndex, true);
    }
    else if (IS_BTN_LEFT_UP)
    {
      RTC.read(currentTime);
      showWatchFace(false);
    }
  }
  else if (guiState == CUSTOM_APP_STATE)
  {
    if (IS_BTN_LEFT_UP)
    { // return to watch face
      RTC.read(currentTime);
      showWatchFace(false);
      return;
    }
  }
  else if (guiState == APP_STATE)
  {
    if (IS_BTN_LEFT_UP)
    {
      showMenu(menuIndex, true);
      return;
    }
  }
  // Watchy::handleButtonPress();
}
