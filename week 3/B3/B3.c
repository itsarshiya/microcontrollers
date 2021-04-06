/*
 * Lesvoorbeeld_atmega2560.c
 *
 * Created: 10/02/2020 18:26:21
 * Author : Etienne
 */ 

#define F_CPU 16e6

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>


// Build in led Arduino on PB7 (pin 13)
void wait( int ms ) {
    for (int i=0; i<ms; i++) {
        _delay_ms( 1 );        // library function (max 30 ms at 8MHz)
    }
}

void timer1Init(){
    OCR1A = 1024;
    TIMSK |= (1 << 4);
	TCCR1A = 0;
	TCCR1B = 0b1100;
    sei();
}


ISR(TIMER1_COMPA_vect){
    PORTB ^= (1<<7);
}


int main(void) {
    DDRB = 0xFF;
    timer1Init();
    while (1)  {
        wait(50);
    }
    return 0;
}