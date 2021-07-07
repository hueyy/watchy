#ifndef CUSTOM_CONFIG_H
#define CUSTOM_CONFIG_H

#ifdef BLE_DEVICE_NAME
#undef BLE_DEVICE_NAME
#define BLE_DEVICE_NAME ""
#endif

#ifdef WIFI_AP_SSID
#undef WIFI_AP_SSID
#define WIFI_AP_SSID ""
#endif

#ifdef WIFI_SSID
#undef WIFI_SSID
#define WIFI_SSID ""
#endif

#ifdef WIFI_PASS
#undef WIFI_PASS
#define WIFI_PASS ""
#endif

#define SLEEP_HOUR_START 0
#define SLEEP_HOUR_END 6
#define SLEEP_MINUTE_START 0
#define SLEEP_MINUTE_END 0

#endif