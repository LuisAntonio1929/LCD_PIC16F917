#include "source.h"

#define LCD_ENABLE_PIN  PIN_B2                                    ////
#define LCD_RS_PIN      PIN_B1                                    ////
#define LCD_RW_PIN      PIN_E2                                    ////
#define LCD_DATA4       PIN_B4                                    ////
#define LCD_DATA5       PIN_B5                                    ////
#define LCD_DATA6       PIN_B6                                    ////
#define LCD_DATA7       PIN_B7 

#include <lcd.c>


int valorl, valorh, x=0;

#int_EXT
void interrupcion_externa(){
   delay_ms(20);	//antirrebote
   if(bit_test(PORTB,0)==0){
      PORTC=x;
      lcd_gotoxy(1, 2);		//Posicionamiento en la segunda fila
      printf(lcd_putc, "        %d        ", x);
   }
   bit_clear(INTCON,1);		//Limpiar flag
}

#int_TIMER1
void interrupcion_TMR1(){
   x++;
   x %= 4;
   TMR1H = valorh;
   TMR1L = valorl;
   bit_clear(PIR1,0);		//Limpiar flag
}

void configuraciones(){
   //Configuracion del oscilador
   bit_set(OSCCON,6);bit_set(OSCCON,5);bit_set(OSCCON,4);	//8 MHz
   bit_clear(OSCCON,3);		//Device is running from the internal system clock
   bit_set(OSCCON,2);		//HFINTOSC is stable
   bit_set(OSCCON,0);		//Internal oscillator is used for system clock
   //Configuracion de los pines
   TRISB |= 0b00000001;		//Pin RB0 como entrada
   TRISB &= 0b00000001;		//Pines RB1 al RB7 como salidas
   TRISC &= 0b00;		//Pines RC0 y RC1 como salidas
   PORTB &= 0b00000001;		//Pines RB1 al RB7 en 0
   PORTC &= 0b00;		//Pines RC0 y RC1 en 0
   //Configuracion de las interrupciones
   bit_clear(OPTION_REG,6);	//Interrupt on falling edge of RB0/INT/SEG0 pin
   
   bit_set(INTCON,7);		//Enables all unmasked interrupts
   bit_set(INTCON,6);		//Enables all unmasked peripheral interrupts
   bit_set(INTCON,5);		//Enables the TMR0 interrupt
   bit_set(INTCON,4);		//Enables the RB0/INT/SEG0 external interrupt
   
   bit_set(PIE1,0);		//TMR1 Overflow Interrupt Enable
   //1:4 Prescale Value
   bit_set(T1CON,5);bit_clear(T1CON,4);
   bit_clear(T1CON,1);		//Internal clock (F OSC/4)
   //Para alcanzar una interrupcion cada 100ms = 4*4*(65535-TMR1)/(8MHz)
   //Se llega a que el valor de TMR1 = 15535
   valorh = 15535 >> 8;
   valorl = 15535 & 0xFF;
   TMR1H = valorh;
   TMR1L = valorl;
   bit_set(T1CON,0);		//Timer1 On
   
   lcd_init();			//Inicializacion de la LCD
   delay_ms(10);
   lcd_gotoxy(1, 1);		//Posicionamiento en la primera fila
   lcd_putc("El valor de x es");//Mensaje principal
}