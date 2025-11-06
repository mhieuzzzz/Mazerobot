#ifndef MAIN_H
#define MAIN_H

#include "stm32f4xx_hal.h"

// Thêm các include khác nếu cần
void SystemClock_Config(void);
void MX_GPIO_Init(void);
void MX_ADC1_Init(void);
void MX_TIM2_Init(void);
void MX_TIM3_Init(void);

#endif
