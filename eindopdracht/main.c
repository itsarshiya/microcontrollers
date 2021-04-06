/*
 * Eindproject Microcontrollers.c
 *
 * Created: 24/03/2021 10:18:01
 * Author : Samir & Arshiya
 */ 


#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lcd.h"

void wait( int ms ) {
	for (int i=0; i<ms; i++) {
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}

#define LCD_E 	3
#define LCD_RS	2
#define LED PD4


void lcd_strobe_lcd_e(void);
void init_4bits_mode(void);
void lcd_write_string(char *str);
void lcd_write_data(unsigned char byte);
void lcd_write_cmd(unsigned char byte);


int timerTickLength = 1;	//The amount of ticks till the timer interrupt gets called again.
int counter = 0;			//Counter to keep track of amount of rotations.
int intervalValue = 1;		//Interval value to change the sound.
char freq[20];				//String for LCD.



void lcd_strobe_lcd_e(void) {
	PORTC |= (1<<LCD_E);	// E high
	_delay_ms(1);			// nodig
	PORTC &= ~(1<<LCD_E);  	// E low
	_delay_ms(1);			// nodig?
}

void lcd_write_command(unsigned char byte)

{
	// First nibble.
	PORTC = byte;
	PORTC &= ~(1<<LCD_RS);
	lcd_strobe_lcd_e();

	// Second nibble
	PORTC = (byte<<4);
	PORTC &= ~(1<<LCD_RS);
	lcd_strobe_lcd_e();
}


void lcd_clear() {
	lcd_write_command (0x01);						//Leeg display
	_delay_ms(2);
	lcd_write_command (0x80);						//Cursor terug naar start
}

void init_4bits_mode(void) {
	// PORTC output mode and all low (also E and RS pin)
	DDRC = 0xFF;
	PORTC = 0x00;

	// Step 2 (table 12)
	PORTC = 0x20;	// function set
	lcd_strobe_lcd_e();

	// Step 3 (table 12)
	PORTC = 0x20;   // function set
	lcd_strobe_lcd_e();
	PORTC = 0x80;
	lcd_strobe_lcd_e();

	// Step 4 (table 12)
	PORTC = 0x00;   // Display on/off control
	lcd_strobe_lcd_e();
	PORTC = 0xF0;
	lcd_strobe_lcd_e();

	// Step 4 (table 12)
	PORTC = 0x00;   // Entry mode set
	lcd_strobe_lcd_e();
	PORTC = 0x60;
	lcd_strobe_lcd_e();

}


void lcd_write_data(unsigned char byte) {
	// First nibble.
	PORTC = byte;
	PORTC |= (1<<LCD_RS);
	lcd_strobe_lcd_e();

	// Second nibble
	PORTC = (byte<<4);
	PORTC |= (1<<LCD_RS);
	lcd_strobe_lcd_e();
}


// Initialize ADC: 10-bits (left justified), free running
void adcInit( void )
{
	ADMUX = 0b01100010;			// Read at pin PF2
	ADCSRA = 0b11100110;		// ADC-enable, no interrupt, start, free running
	wait(75);
}

void adcInit2( void )
{
	ADMUX = 0b01100001;			// Read at pin PF1
	ADCSRA = 0b11100110;		// ADC-enable, no interrupt, start, free running
	wait(75);
}

void timerInit(){
	TCNT1 = 65534-timerTickLength;		//Set timer value
	TCCR1A = 0x00;						//Set TCCR1A register to 0
	TCCR1B = (1<<CS10) | (1<<CS12);		// Timer mode with 1024 prescaler
	TIMSK = (1 << TOIE1);				// Enable timer1 overflow interrupt(TOIE1)
	sei();								// Enable global interrupts by setting global interrupt enable bit in SREG
}

ISR (TIMER1_OVF_vect)    // Timer1 overflow interrupt
{
	//Manage interval value
	if(counter % intervalValue == 0){
		PORTA = PORTA ^ 1;
	}else {
		PORTA = 0;
	}
	counter++;
		
	//Reset timer value
	TCNT1 = 65534-timerTickLength;   
}

int main(void)
{
	DDRF = 0x00;				//set PORTF for input (ADC)
	lcd_init();					//initialize lcd
	timerInit();				//initialize timer
	
	DDRA = 1;					//PORTA as output
	
	//loop to read ADC
	while (1)
	{
		//Write value's on LCD
		sprintf(freq,"%d : %d",timerTickLength,intervalValue);
		display_text(freq);

		//initialize ADC to read PF2
		adcInit();		
		
		//Read ADC at PF2
		timerTickLength = ADCH;
		timerTickLength = ((timerTickLength * 100) / 255);		//Put the value on a scale of 0-100
		PORTB = timerTickLength;	
				
		//initialize ADC to read PF1
		adcInit2();
		
		//read ADC at PF1
		intervalValue = ADCH;
		intervalValue = ((intervalValue * 10) / 255);	//Put the value on a scale of 0-10
		
		//Make sure the interval value won't be below  1.
		if(intervalValue <= 0){
			intervalValue = 1;
		}
	}
}

//initialize lcd
void lcd_init(){
	init_4bits_mode();
}

//display text on lcd
void display_text(char *str){
	lcd_clear();
	for(;*str; str++){
		lcd_write_data(*str);
	}
}



