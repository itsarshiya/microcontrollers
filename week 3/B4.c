#define F_CPU 8e6

#include <avr/io.h>
#include <util/delay.h>

typedef struct { 
	unsigned char data;
	unsigned int delay ;
} PATTERN_STRUCT; 

PATTERN_STRUCT pattern[] = { 
	{0x00, 1000}, {0x01, 1000}, {0x02, 1000}, {0x04, 1000}, {0x08, 1000}, {0x16, 1000}, {0x32, 1000}, {0x64, 1000},
	{0x00, 1000}, {0x01, 1000}, {0x02, 1000}, {0x04, 1000}, {0x08, 1000}, {0x16, 1000}, {0x32, 1000}, {0x64, 1000},
	{0x00, 1000}, {0x01, 1000}, {0x02, 1000}, {0x04, 1000}, {0x08, 1000}, {0x16, 1000}, {0x32, 1000}, {0x64, 1000},
	{0x00, 1000}, {0x01, 1000}, {0x02, 1000}, {0x04, 1000}, {0x08, 1000}, {0x16, 1000}, {0x32, 1000}, {0x64, 1000},

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
	DDRA = 0b11111111;					// PORTD all output 
	
	while (1==1) {
		int index = 0;
		while( pattern[index].delay != 0 ) {
			PORTA = pattern[index].data;
			// wait
			wait(pattern[index].delay);
			index++;
		}
	}

	return 1;
}