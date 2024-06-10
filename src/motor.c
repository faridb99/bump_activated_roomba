#include "../include/motor.h" // Adjust the path according to your project structure

// Initialize motor control pins as outputs
void init_motor_control_pins(void)
{
    // Right Motor A and Right Motor B pins
    DDRB |= (1 << DDB0) | (1 << DDB1) | (1 << DDB2) | (1 << DDB3) | (1 << DDB4) | (1 << DDB5);
    DDRD |= (1 << DDD5)| (1 << DDD6);

    DDRD |= (1 << DDD0) | (1 << DDD1) | (1 << DDD4) | (1 << DDD7);
    // Initialize PWM pins for left motors: pin 3 (OC2B for Timer2) and pin 10 (OC1B for Timer1)
    DDRD |= (1 << DDD3); // Pin 3 as output for left motor A

}

// Initialize PWM Timer (e.g., Timer 0 in Fast PWM mode)
void init_pwm_timer(void)
{
    // Configure Timer 0 for Fast PWM on OC0A and OC0B (e.g., PB2 and PB5 for ATmega328P)
    TCCR0A |= (1 << WGM01) | (1 << WGM00); // Set Fast PWM mode
    TCCR0A |= (1 << COM0A1) | (1 << COM0B1); // Clear OC0A/OC0B on Compare Match, set OC0A/OC0B at BOTTOM (non-inverting mode)
    TCCR0B |= (1 << CS01); // Set prescaler to 8 (assuming a 16 MHz clock, for a PWM frequency of about 7.8 kHz)

    // Setup for left and right motor A using Timer 2 (Pin 3)
    TCCR2A |= (1 << WGM21) | (1 << WGM20);
    TCCR2A |= (1 << COM2B1);
    TCCR2B |= (1 << CS21); // Prescaler set to 8 for a similar frequency as Timer 0

}

// Function to set speed of both right motors
// Speed is input as a percentage (0-100)
void set_right_motor_speed(uint8_t speed_percent)
{
    uint8_t pwm_value = (uint8_t)((speed_percent / 100.0) * MAX_PWM_VALUE);
    OCR0A = pwm_value; // Set PWM duty cycle for Right Motor A (ENA)
    OCR0B = pwm_value; // Set PWM duty cycle for Right Motor B (ENB)
}

// Function to set speed of both left motors
// Speed is input as a percentage (0-100)
void set_left_motor_speed(uint8_t speed_percent)
{
    uint8_t pwm_value = (uint8_t)((speed_percent / 100.0) * MAX_PWM_VALUE);
    OCR2B = pwm_value; // Set PWM duty cycle for Left Motor A/B (Pin 3)
}


// Function to control both right motors to move forward
void right_motors_forward(void)
{
    // Right Motor A forward
    PORTB |= (1 << PORTB0);  // IN1 = HIGH
    PORTB &= ~(1 << PORTB1); // IN2 = LOW
    //PORTB |= (1 << PORTB2);  // ENA = HIGH (enable right motor A)

    // Right Motor B forward
    PORTB |= (1 << PORTB3);  // IN3 = HIGH
    PORTB &= ~(1 << PORTB4); // IN4 = LOW
    //PORTB |= (1 << PORTB5);  // ENB = HIGH (enable right motor B)
}

void left_motors_forward(void)
{
    // Set directions for left motor A forward
    PORTD |= (1 << PORTD4);  // IN1 = HIGH
    PORTD &= ~(1 << PORTD7); // IN2 = LOW

    // Set directions for left motor B forward
    PORTD |= (1 << PORTD0);  // IN3 = HIGH
    PORTD &= ~(1 << PORTD1); // IN4 = LOW
}


// Function to control both right motors to move in reverse
void right_motors_reverse(void)
{
    // Right Motor A reverse
    PORTB &= ~(1 << PORTB0); // IN1 = LOW
    PORTB |= (1 << PORTB1);  // IN2 = HIGH
    PORTB |= (1 << PORTB2);  // ENA = HIGH (enable right motor A)

    // Right Motor B reverse
    PORTB &= ~(1 << PORTB3); // IN3 = LOW
    PORTB |= (1 << PORTB4);  // IN4 = HIGH
    PORTB |= (1 << PORTB5);  // ENB = HIGH (enable right motor B)
}

void left_motors_reverse(void)
{
    // Set directions for left motor A reverse
    PORTD &= ~(1 << PORTD4); // IN1 = LOW
    PORTD |= (1 << PORTD7);  // IN2 = HIGH

    // Set directions for left motor B reverse
    PORTD &= ~(1 << PORTD0); // IN3 = LOW
    PORTD |= (1 << PORTD1);  // IN4 = HIGH
}

void left_motors_stop(void)
{
    // Stop both left motors
    PORTD &= ~((1 << PORTD4) | (1 << PORTD7) | (1 << PORTD0) | (1 << PORTD1));
}   

// Function to stop both right motors
void right_motors_stop(void)
{
    // Right Motor A and Right Motor B stop
    PORTB &= ~((1 << PORTB0) | (1 << PORTB1) | (1 << PORTB3) | (1 << PORTB4));
    // Optionally, disable right motors A and B by making ENA and ENB = LOW
}


void toggle_all_motors_direction(void)
{
    // Toggle directions for all motors
    PORTD ^= (1 << PORTD0) | (1 << PORTD1) | (1 << PORTD4) | (1 << PORTD7); // Toggle Left Motors A and B
    PORTB ^= (1 << PORTB0) | (1 << PORTB1) | (1 << PORTB3) | (1 << PORTB4); // Toggle Right Motors A and B
}