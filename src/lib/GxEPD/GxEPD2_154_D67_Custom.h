#ifndef _GxEPD2_154_D67_Custom_H_
#define _GxEPD2_154_D67_Custom_H_

#include "GxEPD2_EPD.h"

class GxEPD2_154_D67_Custom : public GxEPD2_154_D67
{
public:
  uint8_t borderColour = 0; //0 = black, 1 = white

  GxEPD2_154_D67(int8_t cs, int8_t dc, int8_t rst, int8_t busy);
};

#endif