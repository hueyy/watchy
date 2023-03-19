#include "../../Watchy_Custom.h"

int8_t timeSyncCounter = UPDATE_INTERVAL;
int8_t sgWeatherCounter = UPDATE_INTERVAL;

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
  bool shouldSyncTime = timeSyncCounter >= UPDATE_INTERVAL && UPDATE_INTERVAL != 0;
  bool shouldGetWeather = sgWeatherCounter >= UPDATE_INTERVAL && UPDATE_INTERVAL != 0;
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
    Watchy::syncNTP();
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