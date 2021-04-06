#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int lights;

//sets PD0 to start shifting LEDS using interrupts
ISR( INT0_vect ) {
    lights = (lights<<1);
	if(lights == 0b100000000){
		lights = 0b0000010;
	}
	PORTD = lights;
}

ISR( INT1_vect ) {
  
}

int main( void ) {
	DDRD = 0b111111111;
	lights = 0b00000001;
	PORTD = lights;
	EICRA |= 0x0B;		
	sei();				

	while (1) {							
	}

	return 1;
}
