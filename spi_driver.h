#include<reg51.h>
sbit cs = P1^3;
sbit mosi = P1^4;
sbit miso = P1^5;
sbit clk = P1^6;

float spi_rx(bit,bit);
int spi_read();

float spi_rx(bit d1, bit d0){
	int r;
	cs = 0;
	clk=0;mosi=1;clk=1;
	clk=0;mosi=1;clk=1;
	clk=0;clk=1;
	clk=0;mosi=d1;clk=1;
	clk=0;mosi=d0;clk=1;
	clk=0;clk=1;
	clk=0;clk=1;
	//clk=0;clk=1;
	r = spi_read();
	cs = 1;
	delay(100);
	return (r*5.0)/4096;
}

int spi_read(){
	int r=0;
	char i;
	for(i=11;i>=0;i--){
		clk = 0;
		if(miso)
			r|=(1<<i);
		clk = 1;
	}
	return r;
}