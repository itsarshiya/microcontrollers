
#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int counter;

const unsigned char Numbers [10] = {
	0b01011111, // 0
	0b00000110, // 1
	0b00111011, // 2
	0b00101111, // 3
	0b01100110, // 4
	0b01101101, // 5
	0b01111101, // 6
	0b00000111, // 7
	0b01111111, // 8
	0b01101111, // 9
};

ISR( INT0_vect ) {					//down one
	counter--;
	if(counter < 0){
		counter=0;
	}
	PORTA = Numbers[counter];
}

ISR( INT1_vect ) {					//up by one
	counter++;
	if(counter >= 9){
		counter=9;
	}
	PORTA = Numbers[counter];
}



int main( void ) {
	DDRD = 0xF0;					//init interrupt bit lines
	DDRA = 0b11111111;				//init 7seg

	EICRA |= 0x0B;					//init interrupts
	EIMSK |= 0x03;		
	sei();
	
	PORTA = Numbers[0];				//set 7seg 0
	counter = 0
		while (1==1) {
	}

	return 1;
}
