#ifndef MAIN_H
#define MAIN_H

#include "stm32f4xx_hal.h"

/* HAL handles (declare extern để dùng trong modules) */
extern ADC_HandleTypeDef hadc1;
extern TIM_HandleTypeDef htim2; // PWM for IR LEDs (example)
extern TIM_HandleTypeDef htim3; // PWM for motors (example)

/* System / Init prototypes (CubeMX generated should implement) */
void SystemClock_Config(void);
void MX_GPIO_Init(void);
void MX_ADC1_Init(void);
void MX_TIM2_Init(void);
void MX_TIM3_Init(void);

#endif // MAIN_H
