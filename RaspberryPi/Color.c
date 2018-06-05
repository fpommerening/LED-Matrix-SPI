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
    wiringPiSPISetup(0, 500000);

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

        matrixoff();
        delay(100);
    }
}