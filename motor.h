#ifndef MOTOR_H
#define MOTOR_H

#include "main.h"

void move_forward(void);
void turn_left(void);
void turn_right(void);
void set_motor_pwm(uint16_t left_pwm, uint16_t right_pwm);

#endif
