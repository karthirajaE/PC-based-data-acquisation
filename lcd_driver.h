#include <reg51.h>
#define data_pin P2 
sbit rs= P1^0;
sbit rw= P1^1;
sbit e= P1^2;

void wr_data(unsigned char);
void delay(int);
void initial(void);
void wr_command(unsigned char);
void string(unsigned char*);
void wr_int(int);
void wr_float(float);
void wr_hex(int);
void wr_int(int c){
	signed char t[8];
	char i;
	if(c==0){
		wr_data('0');
		wr_data('0');
	}
	else if(c<10){
		wr_data('0');
	}
	for(i=0;c!=0;i++){
		t[i] = (c%10)+48;
		c/=10;		
	}
	for(i-=1;i>=0;i--){
		wr_data(t[i]);
	}
}
void wr_hex(int c){
	signed char t[8];
	char i;
	if(c==0){
		wr_data('0');
		wr_data('0');
	}
	else if(c<10){
		wr_data('0');
	}
	for(i=0;c!=0;i++){
		t[i] = (c%16)+48;
		c/=16;		
	}
	for(i-=1;i>=0;i--){
		wr_data(t[i]);
	}
}

void wr_float(float f){
	int t;
	//f*=50;
	t= f;
	wr_int(t);
	wr_data('.');
	t = (f-t)*100;
	wr_int(t);
}
void initial(){
	wr_command(0x01);
	wr_command(0x02);
	wr_command(0x0C);
	wr_command(0x38);
	wr_command(0x80);
}

void wr_command(unsigned char cmd){
	data_pin = cmd;
	rs = 0;
	rw = 0;
	e = 1;
	delay(2);
	e = 0;
}

void wr_data(unsigned char d){
	data_pin = d;
	rs = 1;
	rw = 0;
	e = 1;
	delay(2);
	e = 0;
}

void wr_string(unsigned char *s){
	unsigned char i;
	for(i=0;s[i];i++){
		wr_data(s[i]);
		if(i==16)
			wr_command(0xC0);
	}
	
}

void delay(int n){
	unsigned char i;
	while(n--){
		for(i=0;i<250;i++);
		for(i=0;i<249;i++);
	}
}
