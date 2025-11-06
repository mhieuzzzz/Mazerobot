#include "maze.h"
#include "fast_run.h"

int main(void)
{
    HAL_Init();
    SystemClock_Config();
    MX_GPIO_Init();
    MX_ADC1_Init();
    MX_TIM2_Init();
    MX_TIM3_Init();

    wait_button();  // nhấn PA10

    learn_maze();   // chạy lần 1, học map + lưu Flash

    wait_button();  // nhấn PA10 lần 2

    fast_run();     // chạy lần 2, đọc Flash + chạy nhanh
}
