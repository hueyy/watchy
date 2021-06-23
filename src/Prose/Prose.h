#ifndef PROSE_H
#define PROSE_H

#include "../Watchy_Custom.h"

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