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

  wiringPiSetup();
  wiringPiSPISetup(0, 1000000);

  void paint(int waittime)
  {
    int shift;
    int picrepeat;

    for (picrepeat = 20; picrepeat > 0; picrepeat--)
    {
      for (shift = 0; shift < 8; shift++)
      {
        data[RED_DATA] = 0x00;
        data[BLUE_DATA] = 0xFF;
        data[GREEN_DATA] = 0xFF;
        data[3] = 0x01 << shift;

        wiringPiSPIDataRW(0, data, sizeof(data));
        delay(waittime);
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
    int waittime = 0;
    for (waittime = 0; waittime < 50; waittime++)
    {
      paint(waittime);
    };
    matrixoff();
    delay(1000);
  }
}
