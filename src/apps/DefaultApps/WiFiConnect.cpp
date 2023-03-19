#include "../../Watchy_Custom.h"

int8_t timeSyncCounter = UPDATE_INTERVAL;
int8_t sgWeatherCounter = UPDATE_INTERVAL;

void WatchyCustom::setupWifi()
{
  display.epd2.setBusyCallback(0); // temporarily disable lightsleep on busy
  WiFiManager wifiManager;
  wifiManager.resetSettings();
  wifiManager.setTimeout(WIFI_AP_TIMEOUT);
  wifiManager.setAPCallback(WatchyCustom::_configModeCallback);
  display.setFullWindow();
  display.fillScreen(BACKGROUND_COLOUR);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(FOREGROUND_COLOUR);
  if (!wifiManager.autoConnect(WIFI_AP_SSID))
  { // WiFi setup failed
    display.println("Setup failed &");
    display.println("timed out!");
  }
  else
  {
    display.println("Connected to");
    display.println(WiFi.SSID());
    display.println("Local IP:");
    display.println(WiFi.localIP());
  }
  display.display(false); // full refresh
  // turn off radios
  WiFi.mode(WIFI_OFF);
  btStop();
  display.epd2.setBusyCallback(Watchy::displayBusyCallback); // enable lightsleep on
                                                             // busy
  guiState = APP_STATE;
}

void WatchyCustom::_configModeCallback(WiFiManager *myWiFiManager)
{
  display.setFullWindow();
  display.fillScreen(BACKGROUND_COLOUR);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(FOREGROUND_COLOUR);
  display.setCursor(0, 30);
  display.println("Connect to");
  display.print("SSID: ");
  display.println(WIFI_AP_SSID);
  display.print("IP: ");
  display.println(WiFi.softAPIP());
  display.println("MAC address:");
  display.println(WiFi.softAPmacAddress().c_str());
  display.display(false); // full refresh
}

bool WatchyCustom::connectToWiFi()
{
  if (WiFi.begin() != WL_CONNECT_FAILED)
  {
    WIFI_CONFIGURED = WiFi.waitForConnectResult() == WL_CONNECTED;
    if (DEBUG_MODE)
    {
      Serial.print("WIFI_CONFIGURED: ");
      Serial.println(WIFI_CONFIGURED);
    }
    return WIFI_CONFIGURED;
  }

  int remaining_tries = 3;
  WIFI_CONFIGURED = false;

  while (remaining_tries > 0 && !WIFI_CONFIGURED)
  {
    for (unsigned int i = 0; i < 2; i++)
    {
      const char *ssid = i == 0 ? WIFI_SSID1
                                : WIFI_SSID2;
      const char *pass = i == 0 ? WIFI_PASS1
                                : WIFI_PASS2;
      if (DEBUG_MODE)
      {
        Serial.println("Attempt to connect to WiFi: " + String(ssid) + " | " + String(pass));
      }
      WiFi.begin(ssid, pass);
      if (DEBUG_MODE)
      {
        Serial.println("WiFi began");
      }
      WIFI_CONFIGURED = (WiFi.waitForConnectResult() == WL_CONNECTED);
      if (DEBUG_MODE)
      {
        Serial.print("WIFI_CONFIGURED: ");
        Serial.println(WIFI_CONFIGURED);
      }

      if (WIFI_CONFIGURED)
      {
        break;
      }
    }

    remaining_tries--;
  }
  return WIFI_CONFIGURED;
}

void WatchyCustom::showWiFiConnectingScreen()
{
  display.fillScreen(BACKGROUND_COLOUR);
  display.setTextColor(FOREGROUND_COLOUR);
  display.setFont(&Helvetica14pt7b);
  printCentered(70, "Connecting to");
  printCentered(100, "WiFi...");
  display.display(false);
}

void WatchyCustom::doWiFiUpdate()
{
  // update all the things that should be updated via WiFi
  bool shouldSyncTime = true; // timeSyncCounter >= UPDATE_INTERVAL && UPDATE_INTERVAL != 0;
  // bool shouldGetWeather = sgWeatherCounter >= UPDATE_INTERVAL && UPDATE_INTERVAL != 0;
  bool wifiNeeded = shouldSyncTime; // && shouldGetWeather;

  if (wifiNeeded)
  {
    showWiFiConnectingScreen();
    connectToWiFi();
  }

  if (!WIFI_CONFIGURED)
  {
    showWiFiFailedScreen();
    Serial.println("Failed to connect to WiFi");
    return;
  }

  if (shouldSyncTime)
  {
    display.fillScreen(BACKGROUND_COLOUR);
    display.setFont(&FreeMonoBold9pt7b);
    display.setTextColor(FOREGROUND_COLOUR);
    display.setCursor(0, 30);
    display.println("Syncing NTP...");
    display.print("GMT offset: ");
    display.println(settings.gmtOffset);
    display.display(false);

    Watchy::syncNTP();
    timeSyncCounter = 0;
  }

  // if (shouldGetWeather)
  // {
  //   getSGWeather();
  //   sgWeatherCounter = 0;
  // }

  WIFI_CONFIGURED = false;
  WiFi.disconnect();
  WiFi.mode(WIFI_OFF);

  // return to watchface
  showWatchFace(false);
  guiState = WATCHFACE_STATE;
}

void WatchyCustom::showWiFiFailedScreen()
{
  display.fillScreen(BACKGROUND_COLOUR);
  display.setFont(&FreeMonoBold9pt7b);
  display.setTextColor(FOREGROUND_COLOUR);
  display.setCursor(0, 30);
  display.println("Failed to connect to WiFi");
  display.println("WIFI_CONFIGURED = false");
  display.display(false);
}