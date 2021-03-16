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
    int lights = 0b00000001;

    while (1 == 1)
    {
        PORTD = lights;
        wait(500);
        lights = (lights<<1);
        if (lights == 0b00000001) {
            lights = 0b00000001;
        }
    }
    return 0;
}
