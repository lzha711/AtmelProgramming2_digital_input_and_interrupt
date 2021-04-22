/*
 * PushButtonLED.c
 *
 * Created: 4/22/2021 11:56:46 AM
 * Author : lzha711
 */ 

#ifndef F_CPU
#define F_CPU 1000000UL
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define BIT_IS_SET(byte, bit) (byte & (1 << bit))
#define BIT_IS_CLEAR(byte, bit) (!(byte & (1 << bit))) //remember ~ and ! are different!

void PCIntSetup(void){ // Pin change interrupt register setup
	DDRD &= ~(1 << PD0); //set PD0 as input, use PD0/PCINT16 as the Pin change interrupt
	PORTD |= (1 << PD0); // enable pull up resistor for PD0, active low
	PCICR = 0b00000100; //enable pin change interrupt on pins PCINT16-23
	PCMSK2 = 0b00000001; //pin change mask register 2, enable PCINT16, PD0
	sei(); //enable interrupt
}

void ExternalIntSetup(void){ // external interrupt register setup
	DDRD &= ~(1<<PD2); //set INT0 pin as input
	PORTD |= (1<<PD2); // use internal pull-up resistor
	EICRA = 0b00000001; //INT0, any logic change detect
	EIMSK = 0b00000001; //enable INT0
	sei(); //enable interrupt
}	

int main(void)
{ 
	DDRC |= (1 << PC3) | (1 << PC0) | (1<<PC4); //set PC3 and PC0 and PC4 as output
	PORTC &= ~(1 << PC3); // set PC3 LED off as initial state
	PORTC &= ~(1 << PC4); // set PC4 LED off as initial state
	PCIntSetup();
	ExternalIntSetup();
	
    while (1) 
    {
		PORTC ^= (1 << PC0);
		_delay_ms(500); 
		//do nothing
    }
}

ISR(PCINT2_vect)
{
	// PORTC ^= (1<<PC3); // toggle LED every time push button, this also works
	if(BIT_IS_CLEAR(PIND, PD0)){
		PORTC |= (1<<PC3);
	}else if(BIT_IS_SET(PIND, PD0)){
		PORTC &= ~(1<<PC3);
	}else{
	}
}

ISR(INT0_vect){ // if INT0 triggers
	// PORTC ^= (1<<PC3); // toggle LED every time push button, this also works
	if(BIT_IS_CLEAR(PIND, PD2)){
		PORTC |= (1<<PC4);
	}else{
		PORTC &= ~(1<<PC4);
	}
}
