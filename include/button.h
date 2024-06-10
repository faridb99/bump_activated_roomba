// button.h
#ifndef BUTTON_H
#define BUTTON_H

#include <avr/io.h>
#include <avr/interrupt.h>

// Function prototypes
void init_buttons(void);

// External variable declarations
extern volatile uint8_t buttonPressed;

#endif // BUTTON_H
