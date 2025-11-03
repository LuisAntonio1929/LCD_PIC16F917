#include <16F917.h>
#device *=16
#device adc = 8

#fuses MCLR
#fuses NOWDT
#fuses INTRC_IO
#fuses NOPUT
#fuses NOPROTECT
#fuses NOCPD
#fuses NOBROWNOUT
#fuses IESO
#fuses FCMEN
#fuses NODEBUG

#use delay(clock=8M)

#byte PORTB = 0x06
#byte TRISB = 0x86
#byte PORTC = 0x07
#byte TRISC = 0x87

#byte OPTION_REG = 0x181
#byte INTCON = 0x8B
#byte PIE1 = 0x8C
#byte PIR1 = 0x0C
#byte T1CON = 0x10
#byte TMR1L = 0x0E
#byte TMR1H = 0x0F

#byte OSCCON = 0x8F
