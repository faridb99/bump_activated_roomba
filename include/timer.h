// timer.h
#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

void timer1_init(void); // Initialize timer1
void start_timer(void); // Start the software timer
uint8_t check_timer(uint32_t duration_ms); // Check if 3 seconds have elapsed

#endif // TIMER_H