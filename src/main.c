#define F_CPU 16000000
#define REVERSE_DELAY_MS 2000

#include <avr/io.h>
#include "button.h"
#include "motor.h"
#include "timer.h"

int main(void)
{
    init_motor_control_pins(); // Initialize motor control pins
    init_pwm_timer(); // Initialize PWM for motor speed control
    init_buttons(); // Initialize button
    timer1_init(); // Initialize Timer1 for non-blocking delays
    set_right_motor_speed(70); // Set initial speed for right motors
    set_left_motor_speed(70); // Set initial speed for left motors

    // Initially set motors to move forward
    right_motors_forward();
    left_motors_forward();

    uint8_t waiting_for_delay = 0; // Flag to indicate if we are waiting for delay to complete
    uint8_t waiting_for_delay_turning = 0;
    while(1)
    {
        if (buttonPressed && !waiting_for_delay) // Check if the button has been pressed and we're not already waiting
        {
            // Reverse motors
            right_motors_reverse();
            left_motors_reverse();

            start_timer(); // Start the non-blocking timer
            waiting_for_delay = 1; // We are now waiting for the delay to pass
            buttonPressed = 0; // Reset the button press flag
        }

        if (waiting_for_delay && check_timer(REVERSE_DELAY_MS * 0.4)) // Check if the timer has reached the desired delay
        {
            // Delay has passed, set motors to move forward again
            set_right_motor_speed(80); // Set initial speed for right motors
            set_left_motor_speed(30); // Set initial speed for left motors
            right_motors_reverse();
            right_motors_forward();
            waiting_for_delay = 0;
            waiting_for_delay_turning = 1; // We are no longer waiting for the delay
        }

        if (waiting_for_delay_turning && check_timer(REVERSE_DELAY_MS)) // Check if the timer has reached the desired delay
        {
            set_right_motor_speed(70); // Set initial speed for right motors
            set_left_motor_speed(70); // Set initial speed for left motors
            // Delay has passed, set motors to move forward again
            right_motors_forward();
            left_motors_forward();
            waiting_for_delay_turning = 0; // We are no longer waiting for the delay
        }
        // Other tasks can be performed here
    }
}