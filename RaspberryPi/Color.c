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

    void color()
    {
        int shift;
        int colorselect;
        int rate;
        int colorshift;
        int colorrepeat;

        uint16_t color = 0x0000;

        for (colorshift = 0; colorshift < 13; colorshift++)
        {
            color = color | (0x01 << colorshift);

            for (colorrepeat = 0; colorrepeat < 30; colorrepeat++)
            {
                for (rate = 0; rate < 4; rate++)
                {
                    for (colorselect = 0; colorselect < 3; colorselect++)
                    {
                        for (shift = 0; shift < 8; shift++)
                        {
                            data[RED_DATA] = (colorselect == 0 && ((color >> rate) & 0x0001)) ? 0x00 : 0xFF;
                            data[BLUE_DATA] = (colorselect == 1 && ((color >> 4 + rate) & 0x0001)) ? 0x00 : 0xFF;
                            data[GREEN_DATA] = (colorselect == 2 && ((color >> 8 + rate) & 0x0001)) ? 0x00 : 0xFF;
                            data[3] = 0x01 << shift;
                            wiringPiSPIDataRW(0, data, sizeof(data));
                        }
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

        matrixoff();
        delay(1000);
        color();
    }
}