#include<reg51.h>
sbit scl=P3^2;
sbit sda=P3^3;
void i2c_start();
void i2c_stop();
void i2c_ack();
void i2c_write(unsigned char,unsigned char,unsigned char);
void i2c_write_byte(unsigned char);
unsigned char i2c_read(unsigned char,unsigned char);
unsigned char i2c_read_byte();
void i2c_start(){
	scl = 1;
	sda = 1;
	sda = 0;
}
void i2c_stop(){
	sda = 0;
	scl = 1;
	sda = 1;
}
void i2c_ack(){
	scl = 0;
	sda = 1;
	scl = 1;
	//while(sda == 1);
	scl = 0;
}
/*
void i2c_write(unsigned char sa,unsigned char ra,unsigned char da){
	i2c_start();
	i2c_write_byte(sa);
	i2c_ack();
	i2c_write_byte(ra);
	i2c_ack();
	i2c_write_byte(da);
	i2c_ack();
	i2c_stop();
	delay(10);
}*/
void i2c_write_byte(unsigned char c){
	unsigned char i;
	for(i=0;i<8;i++){
		scl = 0;
		sda = c&(0x80>>i)?1:0;
		scl = 1;
	}
}

unsigned char i2c_read(unsigned char sa,unsigned char ra){
	unsigned char d;
	i2c_start();
	i2c_write_byte(0xD0);
	i2c_ack();
	i2c_write_byte(ra);
	i2c_ack();
	i2c_start();
	i2c_write_byte(sa);
	i2c_ack();
	d = i2c_read_byte();
	i2c_ack();
	i2c_stop();
	return d;
}

unsigned char i2c_read_byte(){
	unsigned char i,t = 0;
	for(i=0;i<8;i++){
		scl = 0;
		if(sda)
		t |= (0x80>>i);
		
		scl = 1;
	}
	return t;
}