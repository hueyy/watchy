// as used in https://github.com/sqfmi/Watchy/blob/master/examples/WatchFaces/7_SEG/settings.h

#ifndef SETTINGS_H
#define SETTINGS_H

// openweather stuff
#define CITY_ID ""
#define OW_API_KEY ""
#define OW_URL "http://api.openweathermap.org/data/2.5/weather?id="
#define TEMP_UNIT "metric"
#define TEMP_LANG "en"

// ntp stuff
#define GMT_OFFSET_SEC 28800 // ie UTC +8 = 8 * 60 * 60
#define DAYLIGHT_OFFSET_SEC 0
#define NTP_SERVER ""
#define TIME_SYNC_INTERVAL 30 // every half hour

watchySettings settings{
    CITY_ID,
    OW_API_KEY,
    OW_URL,
    TEMP_UNIT,
    TEMP_LANG,
    TIME_SYNC_INTERVAL,
    NTP_SERVER,
    GMT_OFFSET_SEC,
    DAYLIGHT_OFFSET_SEC};

#endif