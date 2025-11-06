#include "ir_sensor.h"
#include "adc.h"

uint16_t ir_front, ir_left, ir_right;

void read_ir_sensors(void)
{
    HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1, 10);
    ir_front = HAL_ADC_GetValue(&hadc1);

    HAL_ADC_PollForConversion(&hadc1, 10);
    ir_right = HAL_ADC_GetValue(&hadc1);

    HAL_ADC_PollForConversion(&hadc1, 10);
    ir_left = HAL_ADC_GetValue(&hadc1);

    HAL_ADC_Stop(&hadc1);
}

uint8_t front_wall_detected(void)
{
    return (ir_front > THRESH_FRONT);
}

uint8_t left_wall_detected(void)
{
    return (ir_left > THRESH_LEFT);
}

uint8_t right_wall_detected(void)
{
    return (ir_right > THRESH_RIGHT);
}
