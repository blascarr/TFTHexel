/*
  Design and created by Blascarr

  TFTHexel
  Name    : Blascarr
  Description: TFTHexel.h
  version : 1.0

  PixelArt graphics library for TFT Displays based on Hexels format to draw with several grid frames.
  The library use different polygons in order to stablish different grids to draw in pixel format:
  
  Blascarr invests time and resources providing this open source code like some other libraries, please
  respect the job and support open-source hardware.
  
  **
  Written by Adrian for Blascarr
*/

#ifndef _TFTHexel_
#define _TFTHexel_

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <Adafruit_ST7735.h>
#include "HexelFile.h"
  
  //Load this library before
  #ifndef _ADAFRUIT_ST7735H_

  #else

  //Orientation specific for Arduino TFT Esplora (Width = 160, height =128)

  #define TFTWIDTH 160
  #define TFTHEIGHT 128


  class tfthexel : public Adafruit_ST7735 {
    struct vector3{
      float* v[3];
    };
    struct Matrix{
      float* v[3][3];
    };

    public:
      
    int column=14;

    tfthexel();
    void init();
    void drawhexel(int8_t col,int8_t row, uint16_t color = ST7735_BLACK);
    void grid_c(int8_t col, uint16_t color = ST7735_BLACK);
    void hexelgrid(int8_t col,int8_t row, uint16_t color = ST7735_BLACK);
    void setcolumn (int ncolumns);

    vector3 points [6];
    vector3 center;
    Matrix origin;
    bool border;
    int column=14;
    int rows=14;
    private:
    //uint8_t  _cs, _rs, _sid, _sclk;
  };

  #endif

#endif
