#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int main(void)
{
	DDRD = 0b11111111;
	int lights = 0b00000001;

	while (1 == 1)
	{
		PORTD = lights;
		wait(500);
		lights = (lights<<1);
		if (lights == 0b10000000) {
			lights = 0b00000001;
		}
	}
	return 0;
}