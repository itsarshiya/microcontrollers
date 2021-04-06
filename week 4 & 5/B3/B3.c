#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define LCD_E 	3
#define LCD_RS	2


void lcd_strobe_lcd_e(void);
void init_4bits_mode(void);
void lcd_write_string(char *str);
void lcd_write_data(unsigned char byte);
void lcd_write_cmd(unsigned char byte);

int counter = 0;


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

ISR( INT1_vect ) {					//up by one
	counter++;
	lcd_clear();
	char snum[5];
	itoa(counter, snum,10);
	display_text(snum);
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


void init(){
	//DDRD = 0xFF;			// PORTD(7) output, PORTD(6:0) input
	init_4bits_mode();
}

void display_text(char *str){
	for(;*str; str++){
		lcd_write_data(*str);
	}
}

void set_cursor(int pos){
	lcd_write_command(0x80+pos);
}

// Initialize ADC: 10-bits (left justified), free running
void adcInit( void )
{
	ADMUX = 0b01100010;			// AREF=VCC, result left adjusted, channel1 at pin PF1
	ADCSRA = 0b11100110;		// ADC-enable, no interrupt, start, free running, division by 64
}

// wait(): busy waiting for 'ms' millisecond
// Used library: util/delay.h
void wait( int ms )
{
	for (int tms=0; tms<ms; tms++)
	{
		_delay_ms( 1 );			// library function (max 30 ms at 8MHz)
	}
}


int main( void ) {
	

	DDRD = 0xFF;			// PORTD(7) output, PORTD(6:0) input

	//DDRD = 0xF0;					//init interrupt bit lines
	EICRA |= 0x0B;					//init interrupts
	EIMSK |= 0x03;
	sei();
	
	init();

	DDRF = 0x00;				// set PORTF for input (ADC)
	DDRA = 0xFF;				// set PORTA for output
	DDRB = 0xFF;				// set PORTB for output
	PINC = 0x01;
	adcInit();					// initialize ADC
	

	while (1) {
		PORTB = ADCL;			// Show MSB/LSB (bit 10:0) of ADC
		PORTA = ADCH;			// every 100 ms (busy waiting)
		int b = PORTA;
		lcd_clear();
		set_cursor(0);
		char temp[20];
		sprintf(temp,"%d",b);
		display_text(temp);
		wait(500);
	}
	return 1;
}