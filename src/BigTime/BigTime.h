#ifndef BIGTIME_H
#define BIGTIME_H

#include "../Watchy_Custom.h"
#include "../assets/fonts/iosevka_bold40pt7b.h"
#include "../assets/fonts/iosevka_light40pt7b.h"
#include "../assets/fonts/iosevka_medium18pt7b.h"

String zeroPad(uint8_t inputNum);

class BigTime : public WatchyCustom
{
public:
  BigTime();
  void drawWatchFace();
  void drawTime();
  void drawBattery();
};

#endif