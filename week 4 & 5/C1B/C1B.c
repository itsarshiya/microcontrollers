void writeLedDisplay( int value ){ //ADDED
	
	
	char a = 0;
	char b = 0;
	char c = 0;
	char d = 0;
	
	if(value<0){
		value = value * -1;
		d = 10;
	}
	
	
	a = value % 10;
	if(value > 10){
		b = ((value % 100) - a)/10;
		if(value > 100){
			c = ((value % 1000)- (a+b))/100;
			if(value > 1000){
				d = ((value % 10000) - (a+b+c))/1000;
			}
		}
	}
	
		spi_slaveSelect(0); // Select display chip
		spi_write(1); // digit adress: (digit place)
		spi_write(a); // digit value: i (= digit place)
		spi_slaveDeSelect(0); // Deselect display chip
		wait(50);
		spi_slaveSelect(0); // Select display chip
		spi_write(2); // digit adress: (digit place)
		spi_write(b); // digit value: i (= digit place)
		spi_slaveDeSelect(0); // Deselect display chip
		wait(50);
		spi_slaveSelect(0); // Select display chip
		spi_write(3); // digit adress: (digit place)
		spi_write(c); // digit value: i (= digit place)
		spi_slaveDeSelect(0); // Deselect display chip
		wait(50);
		spi_slaveSelect(0); // Select display chip
		spi_write(4); // digit adress: (digit place)
		spi_write(d); // digit value: i (= digit place)
		spi_slaveDeSelect(0); // Deselect display chip
}
