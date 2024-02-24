#include <SPI.h>              //Library for using SPI Communication 
#include <mcp2515.h>          //Library for using CAN Communication (https://github.com/autowp/arduino-mcp2515/)
 
struct can_frame canMsg;
 
MCP2515 mcp2515(10);// SPI CS Pin 34

typedef union
{
  uint8_t tp_value;
}my_union;
 
 
void setup()
{
  Serial.begin(115200);                //Begins Serial Communication at 9600 baudrate
  SPI.begin();                       //Begins SPI communication
  
  delay(1000);
 
  mcp2515.reset();
  mcp2515.setBitrate(CAN_250KBPS, MCP_8MHZ); //Sets CAN at speed 125KBPS 
  mcp2515.setNormalMode();//Sets CAN at normal mode

  Serial.println("void setup done");
}
 
 
void loop()
{
  
  if ((mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) && (canMsg.can_id == 0x0F6))
  {
    Serial.println("messages from id(0x0F6) as byte0//byte1//byte2...");
    //int son2, ilk8, deger;
    my_union t;
    //ilk8 = canMsg.data[0];
    //Serial.print(t.tp_value);
    //Serial.print("//");
    /*son2 = canMsg.data[1];
    deger = ilk8;
    deger = deger << 2;
    deger = (deger | son2);
    Serial.println(ilk8);
    Serial.println(son2);
    Serial.println(deger);*/
    int pot1;
    int pot2;
    int toplam;
    toplam = canMsg.data[0];
    pot1 = toplam & 0b00001111;
    pot2 = toplam & 0b11110000;
    pot2 = pot2 >> 4;
   
    Serial.println(pot1);
    Serial.println(pot2);
    //Serial.println(toplam);
    
    
    //Serial.print(t.tp_value);
    //Serial.print("//");
    t.tp_value = canMsg.data[2];
    //Serial.print(t.tp_value);
    //Serial.print("//");
    t.tp_value = canMsg.data[3];
    //Serial.print(t.tp_value);
    //Serial.print("//");
    t.tp_value = canMsg.data[4];
    //Serial.print(t.tp_value);
    //Serial.print("//");
    t.tp_value = canMsg.data[5];
    //Serial.print(t.tp_value);
    //Serial.print("//");
    t.tp_value = canMsg.data[6];
    //Serial.print(t.tp_value);
    //Serial.print("//");
    t.tp_value = canMsg.data[7];
    //Serial.print(t.tp_value);
    Serial.println("");
    Serial.println("");
  }
}

  /* 0b01010101   ilk8
   * 0b0101010100 deger
   * 0b0000000001 son2
   * 0b0101010101 deger
   * 
   */
