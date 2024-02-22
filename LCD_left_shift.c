// PIC16F877A Configuration Bit Settings

// 'C' source line config statements

// CONFIGURATION BITS
#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// Note: #pragma config statements should come before project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>


#define _XTAL_FREQ 6000000 // Define crystal frequency for delay functions
void init();
void Lcd_Command(unsigned char);
void Lcd_Data(unsigned char);
unsigned char m, x,i;
unsigned char array[18] = {"SHIVAM YADAV"}; // Array holding the characters to display

void main(){
    init(); // Initialize ports and LCD
    Lcd_Command(0x06);
    Lcd_Command(0x82); // Initialize LCD from position 82
    for(x = 0; x < 12; x++){
        Lcd_Data(array[x]); // Display characters 0 to 11 left to right
    }
    Lcd_Command(0x04);
    Lcd_Command(0xCD);// Initialize LCD from position CD
    for(x = 0; x< 12; x++){
      
        Lcd_Data(array[x]); // Display characters 12 to 1 right to left 
    }
    while(1); // Endless loop to prevent the program from exiting
}

void init(){
    TRISC = 0x00; // Set PortC as output
    TRISD = 0x00; // Set PortD as output
    Lcd_Command(0x38); // Function Set: 2 lines, 5x7 matrix
    __delay_ms(100);
    Lcd_Command(0x38); // Repeat initialization commands for stability
    __delay_ms(100);
    Lcd_Command(0x38);
    __delay_ms(100);
    Lcd_Command(0x38);
    __delay_ms(100);
    //Lcd_Command(0x06); // Entry Mode Set: Shift display left
    //__delay_ms(100);
//    Lcd_Command(0x04); // Entry Mode Set: Shift display right
//    __delay_ms(100);
    Lcd_Command(0x0C); // Display ON, cursor OFF
    __delay_ms(100);
    Lcd_Command(0x01); // Clear display
    __delay_ms(100);
}

void Lcd_Data(unsigned char i){
    RC3 = 1; // Set data mode
    PORTD = i; // Send data to PORTD
    RC0 = 1; // Enable signal
    RC0 = 0;
    __delay_ms(100); // Delay for proper data transmission
}

void Lcd_Command(unsigned char i){
    RC3 = 0; // Set command mode
    PORTD = i; // Send command to PORTD
    RC0 = 1; // Enable signal
    RC0 = 0;
    __delay_ms(100); // Delay for proper command transmission
}
