#include "button.h"
#include <util/delay.h>
#include <avr/interrupt.h>

volatile uint8_t buttonPressed = 0;  // Flag for button press on pin 2 (INT0)

// Initialize button-related hardware and interrupts
void init_buttons(void)
{
    // Initialize the button pin 2 as input and enable internal pull-up resistor
    DDRD &= ~(1 << PD2); // Set PD2 as input (INT0)
    PORTD |= (1 << PD2); // Enable pull-up resistor

    // Set INT0 to trigger on falling edge (button press, assuming pull-up configuration)
    EICRA |= (1 << ISC01);
    EICRA &= ~(1 << ISC00);

    // Enable external interrupt INT0
    EIMSK |= (1 << INT0);

    // Initialize the button pin 10 as input and enable internal pull-up resistor
    DDRB &= ~(1 << PB2); // Set PB2 (Digital Pin 10) as input
    PORTB |= (1 << PB2); // Enable pull-up resistor

    // Enable pin change interrupt for PCINT2 (pin 10 belongs to PCINT2 group)
    PCICR |= (1 << PCIE0); // Enable pin change interrupts for PCIE0 (Pin Change Interrupt Enable 0)
    PCMSK0 |= (1 << PCINT2); // Enable mask for pin 10 in PCMSK0

    // Enable global interrupts
    sei();
}

// ISR for button press on pin 2
ISR(INT0_vect)
{
    _delay_ms(500); // Debounce delay
    buttonPressed = 1; // Set flag when button is pressed
}

// ISR for Pin Change Interrupt 0 (handles changes on pins 8 to 14, including pin 10)
ISR(PCINT0_vect)
{
    _delay_ms(500); // Debounce delay
    buttonPressed = 1; // Set flag when button is pressed
}
