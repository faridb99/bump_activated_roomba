#include "timer.h"

volatile uint32_t ms_ticks = 0;

void timer1_init(void) {
    TCCR1A = 0; // Clear Timer1 control register A
    TCCR1B = 0; // Clear Timer1 control register B
    TCNT1 = 0; // Initialize counter value to 0

    // Set compare match register for 1ms ticks
    OCR1A = 249; // = (16MHz / (64 prescaler * 1000)) - 1 (must be <65536)

    // Turn on CTC mode (Clear Timer on Compare Match)
    TCCR1B |= (1 << WGM12);
    // Set CS11 and CS10 bits for 64 prescaler
    TCCR1B |= (0 << CS12) | (1 << CS11) | (1 << CS10); 
    // Enable timer compare interrupt
    TIMSK1 |= (1 << OCIE1A);

    sei(); // Enable global interrupts
}

void start_timer(void) {
    ms_ticks = 0; // Reset the tick counter
}

uint8_t check_timer(uint32_t duration_ms) {
    return (ms_ticks >= duration_ms) ? 1 : 0;
}

// Timer1 ISR
ISR(TIMER1_COMPA_vect) {
    ms_ticks++; // Increment ms counter
}

uint32_t get_time_ms(void) {
    return ms_ticks; // Return the current timer value in milliseconds
}