#ifndef MOTOR_H
#define MOTOR_H
#include "main.h"

#define MOTOR_PWM_MAX 1000

void set_motor_pwm(uint16_t left_pwm, uint16_t right_pwm);
void stop_motors(void);
void move_forward(void);
void move_backward(void);
void turn_left(void);
void turn_right(void);

/* optional: PID loop update */
void motor_pid_update(void);

#endif // MOTOR_H
