#ifndef PROSE_H
#define PROSE_H

#include "../Watchy_Custom.h"
#include "../assets/fonts/Helvetica_Bold25pt7b.h"
#include "../assets/fonts/Helvetica25pt7b.h"
#include "../assets/fonts/Helvetica20pt7b.h"
#include "../assets/fonts/Helvetica14pt7b.h"
// #include "../assets/icons.h"

class Prose : public WatchyCustom
{
public:
  Prose();
  void drawWatchFace();
  void drawTime();
  void drawDate();
  void drawBattery();
  void drawSteps();
};

#endif