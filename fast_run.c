#include "fast_run.h"
#include "maze.h"
#include "motor.h"
#include "main.h"

void fast_run(void)
{
    load_maze_from_flash();

    // Giả lập: robot chạy nhanh qua từng ô
    for (int y = 0; y < 8; y++)
    {
        motor_forward(80);
        HAL_Delay(200);
        motor_stop();
        HAL_Delay(100);
    }

    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_SET); // Buzzer báo kết thúc
    HAL_Delay(300);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);
}
