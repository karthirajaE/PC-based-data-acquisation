/* transmit and receive data in serial using UART
@crystal frequency 11.0592 and 9600 baud rate SCON = 0x40*/
#include<reg51.h>
void start();
void tx(unsigned char);
unsigned char rx(void);
void string_tx(unsigned char *);
unsigned char* string_rx(void);
void int_tx(int);
void hex_tx(int);
void float_tx(float);
//*** function defenetion***//

void string_tx(unsigned char *c){
	while(*c != '\0')
		tx(*c++);
}
/*
unsigned char* string_rx(){
	unsigned char i=0;
	static unsigned char a[10];
	for(i=0;i<10;i++){
		a[i] = rx();
		tx(a[i]);
		if(a[i] == 13){
			break;
		}
	}
	return a;
}*/
	
void start(){
	SCON = 0x50;   //select mode 2(asynchronous standard mode)
	TMOD = 0x20;   //fixing baud rate
	TL1=TH1 = 253;
	TR1=1;   //to start timer
}

void tx(unsigned char d){
	SBUF = d;
	while(TI == 0);
	TI = 0;
}
/*
unsigned char rx(void){
	unsigned char j;
	while(RI==0);
	j = SBUF;
	RI = 0;
	return j;
}*/

void hex_tx(int c){
	signed char t[8];
	char i;
	if(c==0){
		tx('0');
		tx('0');
	}
	else if(c<10){
		tx('0');
	}
	
	for(i=0;c!=0;i++){
		t[i] = (c%16)+48;
		c/=16;		
	}
	for(i-=1;i>=0;i--){
		tx(t[i]);
	}
}

void int_tx(int c){
	signed char t[8];
	char i;
	if(c==0){
		tx('0');
		tx('0');
	}
	else if(c<10){
		tx('0');
	}
	
	for(i=0;c!=0;i++){
		t[i] = (c%10)+48;
		c/=10;		
	}
	for(i-=1;i>=0;i--){
		tx(t[i]);
	}
}

void float_tx(float f){
	int t;
	//f*=50;
	t= f;
	int_tx(t);
	tx('.');
	t = (f-t)*100;
	int_tx(t);
}