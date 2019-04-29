// Arduion Library for Omron D6T
// 2019/1/16: akita11 (akita@ifdl.jp)

#ifndef OmronD6T_h
#define OmronD6T_h
#include <Wire.h>
#include <Arduino.h>
/*
class OmronD6T
{
 private:
  
 public:
  OmronD6T();
  float temp[4][4]; //[degC]
  void scanTemp();
};
*/

bool  D6T_checkPEC( const unsigned char* buf , int pPEC );
template<int width,int height>
class T_OmronD6T
{
 private:
  const static byte I2C_ADDR_D6T=0x0a;
  const static byte CMD=0x4c;
 public:
  T_OmronD6T(){
    //Wrie.begin(); //if you need
  }
  float temp[height][width]; //[degC]
  bool scanTemp() {
    const int bufLen=3+width*height*2;
    uint8_t buf[bufLen];
    int value;

    Wire.beginTransmission(I2C_ADDR_D6T);
    Wire.write(CMD);
    Wire.endTransmission();

    int i = 0;
    Wire.requestFrom(I2C_ADDR_D6T, bufLen);
    while (Wire.available() && i < bufLen){
      buf[i++] = Wire.read();
    }
    Wire.endTransmission();
    for (int y = 0; y < height; y++) {
      for (int x = 0; x < width; x++) {
        i = x + (y * width);
        value = buf[(i * 2 + 2)] + (buf[(i * 2 + 3)] << 8);
        temp[y][x] = value * 0.1;
      }
    }
    return D6T_checkPEC(buf, bufLen-1 );
  }

};

typedef T_OmronD6T<4,4> OmronD6T;
typedef T_OmronD6T<1,1> OmronD6T_1x1;

#endif

