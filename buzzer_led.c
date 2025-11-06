#include "buzzer_led.h"
#include "main.h"

/* Pins from your description:
   LED PC13
   Buzzer PB4
*/
#define LED_GPIO_PORT GPIOC
#define LED_PIN GPIO_PIN_13

#define BUZZER_GPIO_PORT GPIOB
#define BUZZER_PIN GPIO_PIN_4

void led_on(void)
{
    HAL_GPIO_WritePin(LED_GPIO_PORT, LED_PIN, GPIO_PIN_RESET); // PC13 low -> LED on for many boards
}
void led_off(void)
{
    HAL_GPIO_WritePin(LED_GPIO_PORT, LED_PIN, GPIO_PIN_SET);
}
void buzzer_on(void)
{
    HAL_GPIO_WritePin(BUZZER_GPIO_PORT, BUZZER_PIN, GPIO_PIN_SET);
}
void buzzer_off(void)
{
    HAL_GPIO_WritePin(BUZZER_GPIO_PORT, BUZZER_PIN, GPIO_PIN_RESET);
}
