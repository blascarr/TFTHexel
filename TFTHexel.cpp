/*
  Design and created by Blascarr

  TFTHexel
  Name    : Blascarr
  Description: TFTHexel.cpp
  version : 1.0

  PixelArt graphics library for TFT Displays based on Hexels format to draw with several grid frames.
  The library use different polygons in order to stablish different grids to draw in pixel format:
  
  Blascarr invests time and resources providing this open source code like some other libraries, please
  respect the job and support open-source hardware.
  
  
   *  MatrixMath.cpp Library for Matrix Math
   *
   *  Created by Charlie Matlack on 12/18/10.
   *  Modified from code by RobH45345 on Arduino Forums, algorithm from
   *  NUMERICAL RECIPES: The Art of Scientific Computing.
  

  **
  Written by Adrian for Blascarr
*/

#include <TFTHexel.h>

#define mosi 16
#define cs   7
#define rs   0
#define rst  1

/*---------------------------------------------------------------------------------------*/
/*--------------------------------- tftHexel  --------------------------------------*/
/*---------------------------------------------------------------------------------------*/
  tfthexel::tfthexel()
    : Adafruit_ST7735( cs, rs, rst) {

      /*_cs   = cs;
      _rs   = rs;
      _rst  = rst;
      hwSPI = true;
      _sid  = _sclk = 0;*/
  }

  void tfthexel::initEsplora(){
    Serial.begin(9600);
    Serial.println("TFTHexel");
    tfthexel::setRotation(1);
  }

  void tfthexel::drawhexel(int8_t col,int8_t row, uint16_t color ){
    float w = tfthexel::width()/tfthexel::column;
    float h = w*sqrt(4/3);
    //int n_rows = tfthexel::height()/h;
    //Absolut Displacement width and height
    int d_w=(col)/6;
    int d_h=(row)/6;
    float plus_w,plus_h;
    bool inv, inv_x, inv_y;

    int mode = 0;

    float x1 = 0;
    float x2 = 0;
    float y1 = 0;
    float y2 = 0;
    float x3 = 0;
    float y3 = 0;

    //Desplazamiento entre cuadriculas
    plus_w = int (col)/6*2*w;
    plus_h = int (row)/4*h;

    if ((col%6) >= 3){
      plus_w = plus_w + w;
    } 

    if (row%4 >=2){
      plus_h = plus_h + h/2;
    }

    //Identificación del modo de la cuadricula
    if ((col%6 >= 3)^(row%4 >=2)){
        inv = true;
        Serial.println("Mode 2");
        Serial.println(" Y Inverted");
        if ((2*(col%3)+row%2) <= 2){
          row++;
        }else{
          row--;
        }
    }else{
        inv = false;
        Serial.println("Mode 1");
    }

    //Identificación de la mitad a la que pertenece
    if ((2*(col%3)+row%2)>=2){
        inv_x = true;

    }else{
        inv_x = false;
    }

    //Inicializacion de la referencia
    x1 = 0;
    x2 = 0;
    //Identificacion del triangulo al que pertenece
    switch ((col%3+2*(row%2))%4){

      //Case for parameters [0,0] & [2,1]
      case 0:
        x2 = w/2;
        y2 = h/4;
        x3 = 2*w/3;
        y3 = 0;

      break;

      //Case for parameters [1,0] 
      case 1:
        x2 = w/3;
        y2 = h/2;
        x3 = w/2;
        y3 = h/4;
      break;

      //Case for parameters [0,1] & [2,0] 
      case 2:
          x2 = 0;
          y2 = h/2;
          x3 = w/3;
          y3 = h/2;
      break;

      //Case for parameters [1,1] 
      case 3:
        x1 = w;
        y1 = h/2;
        x2 = 2*w/3;
        y2 = 0;
        x3 = w/2;
        y3 = h/4;

      break;
    }


    if(inv){
      y1 = h/2 - y1;
      y2 = h/2 - y2;
      y3 = h/2 - y3;
    }  

    if(inv_x){
      x1 = w-x1;
      x2 = w-x2;
      x3 = w-x3;
      y1 = h/2-y1;
      y2 = h/2-y2;
      y3 = h/2-y3;
    }

    //Debug
    /*Serial.print("Col, Row: ");
    Serial.print(col%3);
    Serial.print(" : ");
    Serial.println(row%2);
    Serial.print("Punto 1: ");
    Serial.print(x1);
    Serial.print(" , ");
    Serial.println(y1);
    Serial.print("Punto 2: ");
    Serial.print(x2);
    Serial.print(" , ");
    Serial.println(y2);
    Serial.print("Punto 3: ");
    Serial.print(x3);
    Serial.print(" , ");
    Serial.println(y3);
    Serial.println(2*(col%3)+row%2);
    Serial.println((col%3+2*(row%2))%4);*/

    tfthexel::fillTriangle(   x1 + plus_w, y1 + plus_h, x2 + plus_w, y2 + plus_h,   x3 + plus_w, y3 + plus_h, color);
  }


  void tfthexel::grid_c(int8_t col, uint16_t color){
    float w = tfthexel::width()/col;
    float h = w*sqrt(4/3);
    int n_rows = tfthexel::height()/h;

    for (int i = 0; i <= col+1; ++i)
    {
        //hexel::drawTriangle(   w*(i-1), 0, w*i, 0 , w*(i-1), h/2, color);
      for (int j = 0; j <= n_rows+1; ++j)
      {
        //hexel::drawTriangle(   0, h/2+h*(j-1), w, h*j , 0, h/2+h*j, color);
        //hexel::drawTriangle(   w, h+h*(j-1), 2*w, h*j+h/2 , w, h+h*j, color);
        //hexel::drawTriangle(   2*w, h/2+h*(j-1), 3*w, h*j , 2*w, h/2+h*j, color);
        //------
        //hexel::drawTriangle(   w*(i-1), h/2+h*(j-1), w*i, h*j , w*(i-1), h/2+h*j, color);

        tfthexel::drawTriangle(   w*(i-1), h/2*(i%2+1)+h*(j-1), w*i, h/2*(i%2)+h*j , w*(i-1), h/2*(i%2+1)+h*j, color);

        //Border Correction
        tfthexel::drawFastHLine(-2, -1, tfthexel::width(),  color);
        tfthexel::drawFastVLine(-2, -1, tfthexel::height(),  color);
        tfthexel::drawFastVLine(-1, -1, tfthexel::height(),  color);

      }
    }
  }

  void tfthexel::hexelgrid(int8_t col, int8_t row, uint16_t color){
    float w = tfthexel::width()/col;
    float h = w*sqrt(4/3);
    int n_rows = tfthexel::height()/h;

    tfthexel::drawTriangle(   0,0 , 2*w/3,0,   w/2, h/4, color);
    tfthexel::drawTriangle(   0,0 , w/2, h/4,  w/3,h/2, color);
    tfthexel::drawTriangle(   0,0 , w/3,h/2,   0, h/2, color);

    tfthexel::drawTriangle(   2*w/3,0 , w,0,   w, h/2, color);
    tfthexel::drawTriangle(   w/2, h/4 , w,h/2,   w/3, h/2, color);
    tfthexel::drawTriangle(   w/2, h/4 , w, h/2,   w/3,h/2, color);
    /*for (int i = 0; i <= col+1; ++i)
    {
        //hexel::drawTriangle(   w*(i-1), 0, w*i, 0 , w*(i-1), h/2, color);
      for (int j = 0; j <= n_rows+1; ++j)
      {
        //hexel::drawTriangle(   0, h/2+h*(j-1), w, h*j , 0, h/2+h*j, color);
        //hexel::drawTriangle(   w, h+h*(j-1), 2*w, h*j+h/2 , w, h+h*j, color);
        //hexel::drawTriangle(   2*w, h/2+h*(j-1), 3*w, h*j , 2*w, h/2+h*j, color);
        //------
        //hexel::drawTriangle(   w*(i-1), h/2+h*(j-1), w*i, h*j , w*(i-1), h/2+h*j, color);

        tfthexel::drawTriangle(   w*(i-1), h/2*(i%2+1)+h*(j-1), w*i, h/2*(i%2)+h*j , w*(i-1), h/2*(i%2+1)+h*j, color);
        tfthexel::drawTriangle(   w*(i-1), h/2*(i%2+1)+h*(j-1), w*i, h/2*(i%2)+h*j , w*(i-1), h/2*(i%2+1)+h*j, color);
        //Border Correction
        tfthexel::drawFastHLine(-2, -1, tfthexel::width(),  color);
        tfthexel::drawFastVLine(-2, -1, tfthexel::height(),  color);
        tfthexel::drawFastVLine(-1, -1, tfthexel::height(),  color);

      }
    }
  }*/
  }