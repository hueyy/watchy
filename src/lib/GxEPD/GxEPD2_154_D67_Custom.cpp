#include "GxEPD2_154_D67_Custom.h"

GxEPD2_154_D67_Custom::GxEPD2_154_D67_Custom(int8_t cs, int8_t dc, int8_t rst, int8_t busy) : GxEPD2_EPD(cs, dc, rst, busy, HIGH, 10000000, WIDTH, HEIGHT, panel, hasColor, hasPartialUpdate, hasFastPartialUpdate)
{
}

void GxEPD2_154_D67_Custom::refresh(int16_t x, int16_t y, int16_t w, int16_t h)
{
  if (_initial_refresh)
    return refresh(false); // initial update needs be full update
  // intersection with screen
  int16_t w1 = x < 0 ? w + x : w;                             // reduce
  int16_t h1 = y < 0 ? h + y : h;                             // reduce
  int16_t x1 = x < 0 ? 0 : x;                                 // limit
  int16_t y1 = y < 0 ? 0 : y;                                 // limit
  w1 = x1 + w1 < int16_t(WIDTH) ? w1 : int16_t(WIDTH) - x1;   // limit
  h1 = y1 + h1 < int16_t(HEIGHT) ? h1 : int16_t(HEIGHT) - y1; // limit
  if ((w1 <= 0) || (h1 <= 0))
    return;
  // make x1, w1 multiple of 8
  w1 += x1 % 8;
  if (w1 % 8 > 0)
    w1 += 8 - w1 % 8;
  x1 -= x1 % 8;
  if (!_using_partial_mode)
    _Init_Part();
  _setPartialRamArea(x1, y1, w1, h1);
  _Update_Part();
}

void GxEPD2_154_D67_Custom::_InitDisplay()
{
  if (_hibernating)
    _reset();
  delay(10);           // 10ms according to specs
  _writeCommand(0x12); // soft reset
  delay(10);           // 10ms according to specs
  _writeCommand(0x01); // Driver output control
  _writeData(0xC7);
  _writeData(0x00);
  _writeData(0x00);
  _writeCommand(0x3C);                    // BorderWavefrom
  _writeData(borderColour ? 0x02 : 0x05); //0x05 for white or 0x02 for black border
  _writeCommand(0x18);                    // Read built-in temperature sensor
  _writeData(0x80);
  _setPartialRamArea(0, 0, WIDTH, HEIGHT);
}
