#ifndef WATCHY_BASE_H
#define WATCHY_BASE_H

#include <Watchy.h>

#define BATTERY_OFFSET 0.105

class WatchyCustom : public Watchy
{
public:
  WatchyCustom();
  void drawHelperGrid();
  void printCentered(uint16_t y, String text);
  void printRight(uint16_t y, String text);
  uint8_t getBattery();
};

#endif