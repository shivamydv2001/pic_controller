
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
void init();
void Lcd_Command(unsigned char);
void Lcd_Data(unsigned char);
unsigned char x,i;
unsigned char array[18] = {"SHIVAM YADAV"};

void main(){
    init();
//    Lcd_Command(0x80);
    Lcd_Command(0xCD);      //initialize from CD
    for(x = 0; x<12; x++){
        Lcd_Data(array[x]);
    }
    while(1);
}
void init(){
    TRISC = 0x00;
    TRISD= 0x00;
    Lcd_Command(0x38);
    __delay_ms(100);
     Lcd_Command(0x38);
    __delay_ms(100);
     Lcd_Command(0x38);
    __delay_ms(100);
     Lcd_Command(0x38);
    __delay_ms(100);
     Lcd_Command(0x07); //shift display right
    __delay_ms(100);
     Lcd_Command(0x0C);
    __delay_ms(100);
     Lcd_Command(0x01);
    __delay_ms(100);
    
}
void Lcd_Data(unsigned char i){
     RC3=1;          //data
    PORTD=i;
    RC0=1;
    RC0=0;
    __delay_ms(100);
}
void Lcd_Command(unsigned char i){
    RC3=0;     //Command
    PORTD=i;
    RC0=1;  //enable signal
    RC0=0;
    __delay_ms(100);
}
