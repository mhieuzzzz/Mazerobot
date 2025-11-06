#include "encoder.h"
#include "main.h"

/* Encoder counts */
volatile int32_t left_encoder_count = 0;
volatile int32_t right_encoder_count = 0;

/* Example: use EXTI interrupt lines for encoder A signals.
   You must configure NVIC/EXTI in CubeMX for the pins PB6, PB7, PB3, PA15 or use Timer Encoder mode.
   Here we present a simple EXTI callback style skeleton.
*/

void encoder_init(void)
{
    // If using TIM encoder mode, start encoder timers here:
    // HAL_TIM_Encoder_Start(&htimX, TIM_CHANNEL_ALL);
    // For EXTI method, ensure GPIO EXTI configured in MX_GPIO_Init()
}

void encoder_update(void)
{
    // Called from EXTI IRQ handlers — see stm32f4xx_it.c to call appropriate handlers
    // Example pseudo:
    // if (INT from right motor A pin) {
    //    if(GPIO_PIN_READ(B) == state) right_encoder_count++;
    // }
    // TODO: implement according to your encoder wiring
}

/* In stm32f4xx_it.c you can add:
 void EXTI9_5_IRQHandler(void) {
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_x);
 }
 and then HAL_GPIO_EXTI_Callback to increment counts.
*/
