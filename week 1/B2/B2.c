int main(void) 
{
	DDRD = 0b11111111;

	while (1==1) 
	{
		PORTD = 0x80;
		wait(500);
		PORTD = 0x40;
		wait(500);	
	}
	return 0;
}