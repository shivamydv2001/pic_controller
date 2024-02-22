
// PIC16F877A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>


#define _XTAL_FREQ 6000000

void init(void);
void Lcd_Command(unsigned char);
void Lcd_Data(unsigned char);
void LcdOutput(unsigned int);
void delay(unsigned int);
unsigned char n,j;
unsigned char k[10];
unsigned int lovalue,hivalue,m,delaycount;
unsigned int value,voltage;

void main(){
    init();
    while(1){
    ADCON0 =0x81;
    ADCON0|=0x04;
    while(ADCON0&0x04);
    lovalue=ADRESL;
    hivalue=ADRESH;
    value=((unsigned int)hivalue<<8)+(unsigned int)lovalue;
    voltage=value*48/1023;
    Lcd_Command(0x80);
    LcdOutput(voltage);
    delay(1000);
    }
}
void init(void){
    TRISA=0x01;
    TRISC=0x00;
    TRISD=0x00;
    ADCON0=0x81;
    ADCON1=0x8E;
    Lcd_Command(0x38);
    __delay_ms(100);
    Lcd_Command(0x38);
    __delay_ms(100);
    Lcd_Command(0x38);
    __delay_ms(100);
    Lcd_Command(0x38);
    __delay_ms(100);
    Lcd_Command(0x06);
    __delay_ms(100);
    Lcd_Command(0x0C);
    __delay_ms(100);
    Lcd_Command(0x01);
    __delay_ms(100);
}

void LcdOutput(unsigned int i){
    unsigned char s;
    j = 1;
    m = i;
    while(m !=0){
        s=m-(m/10)*10;
        k[j]=s;
        j++;
        m=m/10;
    }
    k[j]='\0';
    j=j-1;
    if (k[2]>0){
        n=0x30+k[2];
        Lcd_Data(n);
    }
    else{
        Lcd_Data(0x20);
}
       n=0x30+k[1];
       Lcd_Data(n);
       n=0x56;
       Lcd_Data(n);
}
void Lcd_Command(unsigned char i){
PORTC&=~0x08;
PORTD=i;
PORTC|=0x01;
PORTC&=~0x01;
delay(100);
}
void Lcd_Data(unsigned char i){
PORTC|=0x08;
PORTD=i;
PORTC|=0x01;
PORTC&=~0x01;
delay(100);
}

void delay(unsigned int delaycount){
    while(--delaycount);
}
