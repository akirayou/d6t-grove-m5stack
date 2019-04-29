// Arduion Library for Omron D6T
// 2019/1/16: akita11 (akita@ifdl.jp)
// ATmega-based Arduino & ESP32-based Arduino
// Note: D6T's I2C clock maximum freq. = 100kHz

#include "OmronD6T.h"
static unsigned char  calc_crc( unsigned char  data ) {
  int  index;
  unsigned char  temp;
  for(index=0;index<8;index++){
    temp = data;
    data <<= 1;
    if(temp & 0x80) data ^= 0x07;
  }
  return data;
}
bool  D6T_checkPEC( const unsigned char  *buff , int pPEC ){
  unsigned char  crc = calc_crc( 0x15);
  for(int i=0;i<pPEC;i++){
    crc = calc_crc( buff[i] ^ crc );
  }
  return (crc == buff[pPEC]);
}
