#define F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>

/*Busy wait number of millisecs*/
void wait(int ms)
{
    for (int i = 0; i < ms; i++)
    {
        _delay_ms(1); // library function (max 30 ms at 8MHz)
    }
}
void flicker(int speed)
{
    PORTD = 0x40;
    wait(speed);
    PORTD = 0x00;
    wait(speed);
}

/*
main() loop, entry point of executable
*/
int main(void)
{
    DDRD = 0b11111111;
    PINC = 0x00;
    int speed = 1000; // PORTD all output

    while (1 == 1)
    {

        if (PINC == 1)
        {
            if (speed == 1000)
            {
                speed = 250;
            }
            else
            {
                speed = 1000;
            }
        }

        flicker(speed);
    }
    return 1;
}
