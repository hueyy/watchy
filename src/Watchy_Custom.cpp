#include "Watchy_Custom.h"

RTC_DATA_ATTR bool dark_mode = false;
RTC_DATA_ATTR bool sleep_mode = false;
RTC_DATA_ATTR bool DEBUG_MODE = true;

RTC_DATA_ATTR int8_t watchface_index = 0;
RTC_DATA_ATTR int8_t timeSyncCounter = TIME_SYNC_INTERVAL;

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

bool WatchyCustom::isDebugMode()
{
  return DEBUG_MODE;
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

void WatchyCustom::drawWatchFace()
{
  if (sleep_mode)
  {
    display.drawBitmap(0, 0, zzz_image, DISPLAY_WIDTH, DISPLAY_HEIGHT, GxEPD_WHITE);
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

void WatchyCustom::_rtcConfig(String datetime)
{ // taken directly from Watchy library
  //https://github.com/JChristensen/DS3232RTC
  RTC.squareWave(SQWAVE_NONE); //disable square wave output
  //RTC.set(compileTime()); //set RTC time to compile time
  RTC.setAlarm(ALM2_EVERY_MINUTE, 0, 0, 0, 0); //alarm wakes up Watchy every minute
  RTC.alarmInterrupt(ALARM_2, true);           //enable alarm interrupt
  RTC.read(currentTime);
}

void WatchyCustom::_bmaConfig()
{ // taken directly from Watchy library
  if (sensor.begin(_readRegister, _writeRegister, delay) == false)
  {
    //fail to init BMA
    return;
  }

  // Accel parameter structure
  Acfg cfg;
  /*!
        Output data rate in Hz, Optional parameters:
            - BMA4_OUTPUT_DATA_RATE_0_78HZ
            - BMA4_OUTPUT_DATA_RATE_1_56HZ
            - BMA4_OUTPUT_DATA_RATE_3_12HZ
            - BMA4_OUTPUT_DATA_RATE_6_25HZ
            - BMA4_OUTPUT_DATA_RATE_12_5HZ
            - BMA4_OUTPUT_DATA_RATE_25HZ
            - BMA4_OUTPUT_DATA_RATE_50HZ
            - BMA4_OUTPUT_DATA_RATE_100HZ
            - BMA4_OUTPUT_DATA_RATE_200HZ
            - BMA4_OUTPUT_DATA_RATE_400HZ
            - BMA4_OUTPUT_DATA_RATE_800HZ
            - BMA4_OUTPUT_DATA_RATE_1600HZ
    */
  cfg.odr = BMA4_OUTPUT_DATA_RATE_100HZ;
  /*!
        G-range, Optional parameters:
            - BMA4_ACCEL_RANGE_2G
            - BMA4_ACCEL_RANGE_4G
            - BMA4_ACCEL_RANGE_8G
            - BMA4_ACCEL_RANGE_16G
    */
  cfg.range = BMA4_ACCEL_RANGE_2G;
  /*!
        Bandwidth parameter, determines filter configuration, Optional parameters:
            - BMA4_ACCEL_OSR4_AVG1
            - BMA4_ACCEL_OSR2_AVG2
            - BMA4_ACCEL_NORMAL_AVG4
            - BMA4_ACCEL_CIC_AVG8
            - BMA4_ACCEL_RES_AVG16
            - BMA4_ACCEL_RES_AVG32
            - BMA4_ACCEL_RES_AVG64
            - BMA4_ACCEL_RES_AVG128
    */
  cfg.bandwidth = BMA4_ACCEL_NORMAL_AVG4;

  /*! Filter performance mode , Optional parameters:
        - BMA4_CIC_AVG_MODE
        - BMA4_CONTINUOUS_MODE
    */
  cfg.perf_mode = BMA4_CONTINUOUS_MODE;

  // Configure the BMA423 accelerometer
  sensor.setAccelConfig(cfg);

  // Enable BMA423 accelerometer
  // Warning : Need to use feature, you must first enable the accelerometer
  // Warning : Need to use feature, you must first enable the accelerometer
  sensor.enableAccel();

  struct bma4_int_pin_config config;
  config.edge_ctrl = BMA4_LEVEL_TRIGGER;
  config.lvl = BMA4_ACTIVE_HIGH;
  config.od = BMA4_PUSH_PULL;
  config.output_en = BMA4_OUTPUT_ENABLE;
  config.input_en = BMA4_INPUT_DISABLE;
  // The correct trigger interrupt needs to be configured as needed
  sensor.setINTPinConfig(config, BMA4_INTR1_MAP);

  struct bma423_axes_remap remap_data;
  remap_data.x_axis = 1;
  remap_data.x_axis_sign = 0xFF;
  remap_data.y_axis = 0;
  remap_data.y_axis_sign = 0xFF;
  remap_data.z_axis = 2;
  remap_data.z_axis_sign = 0xFF;
  // Need to raise the wrist function, need to set the correct axis
  sensor.setRemapAxes(&remap_data);

  // Enable BMA423 isStepCounter feature
  sensor.enableFeature(BMA423_STEP_CNTR, true);
  // Enable BMA423 isTilt feature
  sensor.enableFeature(BMA423_TILT, true);
  // Enable BMA423 isDoubleClick feature
  sensor.enableFeature(BMA423_WAKEUP, true);

  // Reset steps
  sensor.resetStepCounter();

  // Turn on feature interrupt
  sensor.enableStepCountInterrupt();
  sensor.enableTiltInterrupt();
  // It corresponds to isDoubleClick interrupt
  sensor.enableWakeupInterrupt();
}

uint16_t WatchyCustom::_readRegister(uint8_t address, uint8_t reg, uint8_t *data, uint16_t len)
{ // taken directly from Watchy library
  Wire.beginTransmission(address);
  Wire.write(reg);
  Wire.endTransmission();
  Wire.requestFrom((uint8_t)address, (uint8_t)len);
  uint8_t i = 0;
  while (Wire.available())
  {
    data[i++] = Wire.read();
  }
  return 0;
}

uint16_t WatchyCustom::_writeRegister(uint8_t address, uint8_t reg, uint8_t *data, uint16_t len)
{ // taken directly from Watchy library
  Wire.beginTransmission(address);
  Wire.write(reg);
  Wire.write(data, len);
  return (0 != Wire.endTransmission());
}

void WatchyCustom::drawHelperGrid()
{
  for (int i = 0; i <= 200; i += 20)
  {
    display.drawLine(i, 0, i, 200, GxEPD_BLACK);
    display.drawLine(0, i, 200, i, GxEPD_BLACK);
  }
}

// text-align: center
void WatchyCustom::printCentered(uint16_t y, String text)
{
  int16_t x1, y1;
  uint16_t w, h;

  display.getTextBounds(text, 100, 100, &x1, &y1, &w, &h);
  display.setCursor((200 - w) / 2, y);
  display.println(text);
}

// text-align: right
void WatchyCustom::printRight(uint16_t y, String text)
{
  int16_t x1, y1;
  uint16_t w, h;

  display.getTextBounds(text, 100, 100, &x1, &y1, &w, &h);
  display.setCursor(200 - w, y);
  display.println(text);
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

bool WatchyCustom::connectToWiFi(){
  int remaining_tries = 3;
  WIFI_CONFIGURED = false;

  while (remaining_tries > 0)
  {
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    Serial.println("Attempt to connect to WiFi: " + String(WIFI_SSID) + " | " + String(WIFI_PASS));

    WIFI_CONFIGURED = (WiFi.waitForConnectResult() == WL_CONNECTED);

    if (WIFI_CONFIGURED)
    {
      break;
    }
    remaining_tries--;
  }

  Serial.println("WIFI_CONFIGURED: " + WIFI_CONFIGURED);
  return WIFI_CONFIGURED;
}

void WatchyCustom::syncTime(){
  Serial.println("Syncing time...");

  struct tm timeinfo;

  //get NTP Time
  configTime(GMT_OFFSET_SEC, DAYLIGHT_OFFSET_SEC, NTP_SERVER);
  delay(4000); //delay 4 secods so configTime can finish recieving the time from the internet
  getLocalTime(&timeinfo);

  // convert NTP time into proper format
  tmElements_t tm;
  tm.Month = timeinfo.tm_mon + 1;// 0-11 based month so we have to add 1
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

void WatchyCustom::doWiFiUpdate(){
  // update all the things that should be updated via WiFi
  bool shouldSyncTime = timeSyncCounter >= TIME_SYNC_INTERVAL && TIME_SYNC_INTERVAL != 0;
  bool wifiNeeded = shouldSyncTime;

  if(wifiNeeded){
    connectToWiFi();
  }

  if(!WIFI_CONFIGURED){
    Serial.println("Failed to connect to WiFi");
    return;
  }

  if(shouldSyncTime){
    syncTime();
    timeSyncCounter = 0;
  }

  WIFI_CONFIGURED = false;
  WiFi.disconnect();
  WiFi.mode(WIFI_OFF);
}

bool WatchyCustom::connectWiFi()
{
  int remaining_tries = 3;
  while (remaining_tries > 0)
  {

    WIFI_CONFIGURED = false;
    WiFi.begin(WIFI_SSID, WIFI_PASS);
    WIFI_CONFIGURED = (WiFi.waitForConnectResult() == WL_CONNECTED);

    if (!WIFI_CONFIGURED)
    {
      WiFi.begin();
      WIFI_CONFIGURED = (WiFi.waitForConnectResult() == WL_CONNECTED);
    }

    if (WIFI_CONFIGURED)
    {
      break;
    }
    remaining_tries--;
  }

  return WIFI_CONFIGURED;
}

void WatchyCustom::disconnectWiFi()
{
  WIFI_CONFIGURED = false;
  WiFi.disconnect();
  WiFi.mode(WIFI_OFF);
  btStop();
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
      Serial.println("WatchyCustom RIGHT DOWN Button");
      bumpWatchFaceIndex();
      Serial.println("WatchFace Index: " + String(watchface_index));
      RTC.alarm(ALARM_2);
      RTC.read(currentTime);
      showWatchFace(false);
      return;
    } else if (IS_BTN_LEFT_UP) {
      showSGWeather();
      return;
    }
  }
  else if (guiState == CUSTOM_APP_STATE)
  {
    if (wakeupBit & BACK_BTN_MASK)
    { // return to watch face
      RTC.read(currentTime);
      showWatchFace(false);
      return;
    }
  }
  Watchy::handleButtonPress();
}

String WatchyCustom::zeroPad(uint8_t inputNum)
{
  if (inputNum < 10)
  {
    return "0" + String(inputNum);
  }
  return String(inputNum);
}