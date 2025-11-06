#include "motor.h"
#include "main.h"
#include "encoder.h"

/* External TIM handle for PWM - ensure channels match CubeMX config */
extern TIM_HandleTypeDef htim3;

/* Example: TIM3 CH1 -> left motor PWM, CH2 -> right motor PWM
   SN754410NE direction pins must be controlled by GPIO (not shown).
   Configure direction pins in MX_GPIO_Init() in Cube.
*/

/* Direction control pin macros - adjust to your pin mapping */
#define LEFT_DIR_GPIO_PORT GPIOA
#define LEFT_DIR_PIN GPIO_PIN_8  // example, change to actual pin
#define RIGHT_DIR_GPIO_PORT GPIOA
#define RIGHT_DIR_PIN GPIO_PIN_9 // example, change to actual pin

static uint16_t left_pwm = 0;
static uint16_t right_pwm = 0;

void set_motor_pwm(uint16_t l, uint16_t r)
{
    if (l > MOTOR_PWM_MAX) l = MOTOR_PWM_MAX;
    if (r > MOTOR_PWM_MAX) r = MOTOR_PWM_MAX;
    left_pwm = l;
    right_pwm = r;

    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_1, left_pwm);
    __HAL_TIM_SET_COMPARE(&htim3, TIM_CHANNEL_2, right_pwm);
}

void stop_motors(void)
{
    set_motor_pwm(0,0);
}

void move_forward(void)
{
    // Set direction pins for forward (assumes H-bridge wiring)
    HAL_GPIO_WritePin(LEFT_DIR_GPIO_PORT, LEFT_DIR_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(RIGHT_DIR_GPIO_PORT, RIGHT_DIR_PIN, GPIO_PIN_SET);
    set_motor_pwm(600, 600); // default moderate speed, tune later
    HAL_Delay(200); // move for a small step; better use encoders for precise distance
    stop_motors();
}

void move_backward(void)
{
    HAL_GPIO_WritePin(LEFT_DIR_GPIO_PORT, LEFT_DIR_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(RIGHT_DIR_GPIO_PORT, RIGHT_DIR_PIN, GPIO_PIN_RESET);
    set_motor_pwm(500, 500);
    HAL_Delay(200);
    stop_motors();
}

void turn_left(void)
{
    // left motor backward, right motor forward (in-place turn)
    HAL_GPIO_WritePin(LEFT_DIR_GPIO_PORT, LEFT_DIR_PIN, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(RIGHT_DIR_GPIO_PORT, RIGHT_DIR_PIN, GPIO_PIN_SET);
    set_motor_pwm(500, 500);
    HAL_Delay(180); // tune to ~90deg turn
    stop_motors();
}

void turn_right(void)
{
    // left forward, right backward
    HAL_GPIO_WritePin(LEFT_DIR_GPIO_PORT, LEFT_DIR_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(RIGHT_DIR_GPIO_PORT, RIGHT_DIR_PIN, GPIO_PIN_RESET);
    set_motor_pwm(500, 500);
    HAL_Delay(180);
    stop_motors();
}

/* Simple PID placeholder (call periodically) */
void motor_pid_update(void)
{
    // TODO: implement PID using encoder counts left_encoder_count/right_encoder_count
}
