#define F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>

typedef struct {
	unsigned char data;
	unsigned int delay ;
} PATTERN_STRUCT;

PATTERN_STRUCT pattern[] = {
	{0x00, 100}, {0x01, 100}, {0x02, 100}, {0x04, 100}, {0x10, 100}, {0x20, 100}, {0x40, 100}, {0x80, 100},
	{0x80, 100}, {0x40, 100}, {0x20, 100}, {0x10, 100}, {0x04, 100}, {0x02, 100}, {0x01, 100}, {0x00, 100},
	{0x03,  50}, {0x0C,  50},
	{0x30,  50}, {0xC0,  50},
	{0xC0,  50}, {0x30,  50},
	{0x0C,  50}, {0x03,  50},
};

/*Busy wait number of millisecs*/
void wait( int ms ) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}


/*
main() loop, entry point of executable
*/
int main( void )
{
	DDRD = 0b11111111;					// PORTD all output
	
	while (1==1) {
		// Set index to begin of pattern array
		int index = 0;
		// as long as delay has meaningful content
		while( pattern[index].delay != 0 ) {
			// Write data to PORTD
			PORTD = pattern[index].data;
			// wait
			wait(pattern[index].delay);
			// increment for next round
			index++;
		}
	}

	return 1;
}