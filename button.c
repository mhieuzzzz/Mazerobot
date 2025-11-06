#include "button.h"
#include "gpio.h"

void wait_button(void)
{
    while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10) == GPIO_PIN_SET);
}
