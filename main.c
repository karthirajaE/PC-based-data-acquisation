#include"lcd_driver.h"
#include"uart_driver.h"
#include"i2c_driver.h"
#include"spi_driver.h"
void main(){
	unsigned char h,m,s;
	float t;
	initial();
	start();
	while(1){
		wr_string("clk-"); //--->i2c
		s=i2c_read(0xD1,0x00);
		m=i2c_read(0xD1,0x01);
		h=i2c_read(0xD1,0x02);
		t = spi_rx(0,0);  //--->spi
		wr_hex(h);
		wr_data(':');
		wr_hex(m);
		wr_data(':');
		wr_hex(s);
		if(h&0x20)
			wr_string(" PM");
		else
			wr_string(" AM");
		wr_command(0xc0);
		wr_string("temp->");
		wr_float(t*100);
		wr_data('C');
		wr_command(0x02);
		string_tx("clock->");   //uart
		hex_tx(h);
		tx(':');
		hex_tx(m);
		tx(':');
		hex_tx(s);
		tx(13);
		string_tx("temp->");
		float_tx(t*100);
		tx('C');
		tx(13);
	}
}