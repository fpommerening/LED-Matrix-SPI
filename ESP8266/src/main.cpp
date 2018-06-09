#include <Arduino.h>
#include <SPI.h>

static uint8_t data[4] = {0x0, 0x0, 0x0, 0x0};
const int CE = 15; // defined  the CE function pin

void paint(int color)
{
  int shift;
  int col;
  int row;
  int picrepeat;

  uint8_t picture[8] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

  for (row = 0; row < 8; row++)
  {
    for (col = 7; col >= 0; col--)
    {
      picture[row] = 0xFF >> col;
      for (picrepeat = 20; picrepeat > 0; picrepeat--)
      {
        for (shift = 0; shift < 8; shift++)
        {

          data[0] = color == 0 ? ~picture[shift] : 0xFF;
          data[1] = color == 1 ? ~picture[shift] : 0xFF;
          data[2] = color == 2 ? ~picture[shift] : 0xFF;

          data[3] = 0x01 << shift;
          digitalWrite(CE, LOW);
          SPI.transfer(data[0]);
          SPI.transfer(data[2]);
          SPI.transfer(data[1]);
          SPI.transfer(data[3]);
          digitalWrite(CE, HIGH);
          delay(2);
        }
      }
    }
  }
};

void matrixoff()
{
  int j;
  int x = 2;
  for (j = 0; j < 8; j++)
  {
    data[0] = 0xFF;

    data[1] = 0xFF;
    data[2] = 0xFF;
    data[3] = 0x01 << j;
    digitalWrite(CE, LOW);
    SPI.transfer(data[0]);
    SPI.transfer(data[2]);
    SPI.transfer(data[1]);
    SPI.transfer(data[3]);
    digitalWrite(CE, HIGH);
    delay(x);
  }
};

void setup()
{
  pinMode(CE, OUTPUT);
  SPI.begin();
}

void loop()
{
  int colorselect = 0;
    for (colorselect = 0; colorselect < 3; colorselect++)
    {
      paint(colorselect);
      matrixoff();
      delay(1000);
    };
}
