#include <Arduino.h>
#include <SPI.h>                  

static uint8_t data[4] = {0x0, 0x0, 0x0, 0x0};        
const int CE = 15;                                                      // defined  the CE function pin


void matrixoff()
{
  int j;
  int x = 2;
  for ( j = 0; j < 8; j++)
  {
    data[0] = 0xFF;
    data[2] = 0xFF;
    data[1] = 0xFF;
    data[3] = 0x01 << j ;
    digitalWrite(CE, LOW);
    SPI.transfer(data[0]);
    SPI.transfer(data[2]);
    SPI.transfer(data[1]);
    SPI.transfer(data[3]);
    digitalWrite(CE, HIGH);
    delay(x);
  }
};

void setup() {


   pinMode(CE, OUTPUT);
   SPI.begin();        
}


void loop()                                                
{

  matrixoff();                                         
  
  
}
