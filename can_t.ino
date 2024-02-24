

#include "stdio.h"
#include "stdint.h"

#include <SPI.h>          //Library for using SPI Communication 
#include <mcp2515.h>      //Library for using CAN Communication (https://github.com/autowp/arduino-mcp2515/)
 
struct can_frame canMsg1;
 
MCP2515 mcp2515(10);

typedef union
{
  uint8_t byte;
  struct {
    uint8_t bit0 : 1;
    uint8_t bit1 : 1;
    uint8_t bit2 : 1;
    uint8_t bit3 : 1;
    uint8_t bit4 : 1;
    uint8_t bit5 : 1;
    uint8_t bit6 : 1;
    uint8_t bit7 : 1;
  }Bits;
}byte_ut;

typedef union
{
  uint16_t tp_value : 10;
}my_union;
 
 
void setup()
{
  while (!Serial);
  SPI.begin();               //Begins SPI communication
 
  mcp2515.reset();
  mcp2515.setBitrate(CAN_250KBPS, MCP_8MHZ);//Sets CAN at speed 125KBPS
  mcp2515.setNormalMode();//Sets CAN at normal mode
}
 
 
void loop()
{int toplam =0b00000000;
// 11001001,
//10010000

int deger = map (analogRead(A0),0,1024,0,15);
int deger2= map (analogRead(A1),0,1024,0,15);
toplam = toplam | deger2;
toplam=toplam << 4;
toplam=toplam | deger;
  
  /* temp2 = (deger & 0b11);
  deger = deger >> 2;
 */
  canMsg1.can_id  = 0x0F6;
  canMsg1.can_dlc = 8;
  canMsg1.data[0] = toplam;
  canMsg1.data[1] = 0;
  canMsg1.data[2] = 0b00000000;
  canMsg1.data[2] = 0b00000000;
  canMsg1.data[3] = 0b00000000;
  canMsg1.data[4] = 0b00000000;
  canMsg1.data[5] = 0b00000000;
  canMsg1.data[6] = 0b00000000;
  canMsg1.data[7] = 0b11111111;


  /* 0b0101010101
   * 0b0000000011
   * 0b0000000001 temp2
   * 0b0101010101
   * 0b0001010101 temp1
   */
   
  
  mcp2515.sendMessage(&canMsg1); //Sends the CAN message
  delay(100);
}
