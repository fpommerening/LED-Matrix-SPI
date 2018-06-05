#include <stdio.h>
#include <wiringPi.h>
#include <wiringPiSPI.h>
#include <stdint.h>

#define RED_DATA 0
#define BLUE_DATA 1
#define GREEN_DATA 2

int main(void)
{
  static uint8_t data[4] = {0x0, 0x0, 0x0, 0x0};
  static uint8_t i = 0;

  wiringPiSetup();
  wiringPiSPISetup(0, 1000000);

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

            data[RED_DATA] = color == 0 ? ~picture[shift] : 0xFF;
            data[BLUE_DATA] = color == 1 ? ~picture[shift] : 0xFF;
            data[GREEN_DATA] = color == 2 ? ~picture[shift] : 0xFF;

            data[3] = 0x01 << shift;
            wiringPiSPIDataRW(0, data, sizeof(data));
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
      data[RED_DATA] = 0xFF;
      data[BLUE_DATA] = 0xFF;
      data[GREEN_DATA] = 0xFF;
      data[3] = 0x01 << j;
      wiringPiSPIDataRW(0, data, sizeof(data));
      delay(x);
    }
  }

  while (1)
  {
    int colorselect = 0;
    for (colorselect = 0; colorselect < 3; colorselect++)
    {
      paint(colorselect);
      matrixoff();
      delay(1000);
    };
  }
}
