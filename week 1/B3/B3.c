#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int main(void)
{
	DDRD = 0b11111111;
	PINC = 0x00;

	while (1 == 1)
	{
		if (PINC == 1)
		{
			PORTD = 0x40;
			wait(500);
			PORTD = 0x00;
			wait(500);
		}
	}
	return 0;
}