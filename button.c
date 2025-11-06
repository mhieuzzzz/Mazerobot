#include "button.h"
#include "main.h"

/* Assumes PA10 configured as input with pull-up (pressed = 0) */
void wait_button(void)
{
    // simple debounce
    while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10) == GPIO_PIN_SET) {
        HAL_Delay(10);
    }
    // wait for release
    HAL_Delay(50);
    while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10) == GPIO_PIN_RESET) {
        HAL_Delay(10);
    }
    HAL_Delay(50);
}
