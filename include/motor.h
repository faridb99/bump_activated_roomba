#ifndef MOTOR_H
#define MOTOR_H

#include <avr/io.h>
#define MAX_PWM_VALUE 255 // Maximum PWM value for 8-bit resolution

/*

Pin 0 : Used for Left Motor A direction control (IN1)
Pin 1 : Used for Left Motor A direction control (IN2)

Pin 2 : Switch Grey wire (Second wire (black) : Ground)

Pin 3: PWM output for Left Motor B speed control (ENA2) / PWM output for Left Motor A speed control (ENA1)
Pin 4: Used for Left Motor B direction control (IN3)
Pin 7: Used for Left Motor B direction control (IN4)

Pin 5: PWM output for Right Motor A speed control (ENA1)
Pin 8: Used for Right Motor A direction control (IN1)
Pin 9: Used for Right Motor A direction control (IN2)


Pin 6: PWM output for Right Motor A speed control (ENA2)
Pin 11: Used for Right Motor A direction control (IN3)
Pin 12: Used for Right Motor A direction control (IN4)

*/


// Function prototypes for motor control
void init_motor_control_pins(void);
void init_pwm_timer(void);
void right_motors_forward(void);
void right_motors_reverse(void);
void right_motors_stop(void);
void set_right_motor_speed(uint8_t speed);
void left_motors_forward(void);
void left_motors_reverse(void);
void left_motors_stop(void);
void set_left_motor_speed(uint8_t speed);
void toggle_all_motors_direction(void);
#endif // MOTOR_H