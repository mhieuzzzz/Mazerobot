#include "main.h"
#include "maze.h"
#include "ir_sensor.h"
#include "motor.h"
#include "encoder.h"
#include "fast_run.h"
#include "flash.h"
#include "button.h"
#include "buzzer_led.h"

ADC_HandleTypeDef hadc1;
TIM_HandleTypeDef htim2;
TIM_HandleTypeDef htim3;

int main(void)
{
    HAL_Init();
    SystemClock_Config();

    MX_GPIO_Init();
    MX_ADC1_Init();
    MX_TIM2_Init();
    MX_TIM3_Init();

    /* Start PWM timers if needed */
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1); // Depending on Cube config
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);

    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1); // motor left
    HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2); // motor right

    // Optional: init encoder interrupts or timers (encoder.c handles)
    encoder_init();

    // Chờ người dùng ấn nút PA10 để bắt đầu
    wait_button();

    // Lần 1: học map
    learn_maze();
    save_maze_to_flash();

    // Lần 2: chạy nhanh
    load_maze_from_flash();
    fast_run();

    while (1)
    {
        HAL_Delay(1000);
    }
}
