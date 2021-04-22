# AtmelProgramming_digital_input_and_interrupt
Digital input practice and interrupt, including external interrupt and pin change interrupt

From the information provided in the datasheet of ATmega328P, I created a small project on reading digital input and turn on LED when push button is pressed. 
The main loop has one LED toggling state the whole time. So reading push button state and take action is done through interrupt. 
ATmega328P has two external interrupts (INT0 and INT1), but any PCINT pin can be configured as pin change interrupt.
Simulated in Proteus
