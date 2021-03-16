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

int main(void)
{
    DDRD = 0b11111111;
    PINC = 0x00;

    while (1 == 1)
    {
        if (PINC == 1) {
            PORTD = 0x40;
            wait(500);
            PORTD = 0x00;
            wait(500);
        }
    }
    return 0;
}
