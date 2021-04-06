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

int intervalValue = 15;

void timerInit(){
	TCNT1 = 65534-intervalValue;		//Set timer value
	TCCR1A = 0x00;						//Set TCCR1A register to 0
	TCCR1B = (1<<CS10) | (1<<CS12);		// Timer mode with 1024 prescaler
	TIMSK = (1 << TOIE1);				// Enable timer1 overflow interrupt(TOIE1)
	sei();								// Enable global interrupts by setting global interrupt enable bit in SREG
}

ISR (TIMER1_OVF_vect)    // Timer1 overflow interrupt
{
	PORTD = PORTD ^ 1;
	if(intervalValue == 15){
		intervalValue = 25;
	}else {intervalValue = 15;}
		
	TCNT1 = 65534-intervalValue;   
}


int main(void) {
    DDRD = 1;
    timerInit();
    while (1)  {
        wait(50);
    }
    return 0;
}