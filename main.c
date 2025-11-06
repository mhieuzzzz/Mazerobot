#include "main.h"
#include "maze.h"
#include "ir_sensor.h"
#include "motor.h"
#include "encoder.h"
#include "fast_run.h"
#include "flash.h"
#include "button.h"
#include "buzzer_led.h"

int main(void)
{
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_ADC1_Init();
    MX_TIM2_Init(); // PWM LED IR
    MX_TIM3_Init(); // PWM Motor

    wait_button();   // Chờ nút PA10 nhấn

    // ================= Lần 1: Học map =================
    learn_maze();
    save_maze_to_flash();

    // ================= Lần 2: Chạy nhanh =================
    load_maze_from_flash();
    fast_run();

    while(1); // loop vô hạn
}
