#include "ir_sensors.h"
#include "main.h"

extern TIM_HandleTypeDef htim5;   // Sử dụng TIM5 cho PWM
extern ADC_HandleTypeDef hadc1;   // ADC để đọc cảm biến

// Các biến lưu giá trị cảm biến
uint16_t ir_right_straight = 0;
uint16_t ir_right_side = 0;
uint16_t ir_left_side = 0;
uint16_t ir_left_straight = 0;

// Cấu hình ban đầu
void IR_Init(void)
{
    HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_3);
    HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_4);
}

// Hàm bật/tắt LED phát IR
void IR_Emitters_On(void)
{
    __HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_1, 80);  // LED phát 1 (PA0)
    __HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_2, 80);  // LED phát 2 (PA1)
    __HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_3, 80);  // LED phát 3 (PA2)
    __HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_4, 80);  // LED phát 4 (PA3)
}

void IR_Emitters_Off(void)
{
    __HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_1, 0);
    __HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_2, 0);
    __HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_3, 0);
    __HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_4, 0);
}

// Đọc giá trị ADC từ các cảm biến IR
void IR_ReadSensors(void)
{
    // PA4 - Right Straight
    HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
    ir_right_straight = HAL_ADC_GetValue(&hadc1);

    // PA5 - Right Side
    HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
    ir_right_side = HAL_ADC_GetValue(&hadc1);

    // PA6 - Left Side
    HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
    ir_left_side = HAL_ADC_GetValue(&hadc1);

    // PA7 - Left Straight
    HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
    ir_left_straight = HAL_ADC_GetValue(&hadc1);
}

// Hàm kiểm tra tường
uint8_t IR_CheckWall(void)
{
    uint8_t wall_detected = 0;

    if (ir_right_straight > 1000) wall_detected |= (1 << 0);  // Tường phía trước bên phải
    if (ir_right_side > 1000)     wall_detected |= (1 << 1);  // Tường bên phải
    if (ir_left_side > 1000)      wall_detected |= (1 << 2);  // Tường bên trái
    if (ir_left_straight > 1000)  wall_detected |= (1 << 3);  // Tường phía trước bên trái

    return wall_detected;
}
