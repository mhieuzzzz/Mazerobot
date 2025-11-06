#include "ir_sensor.h"
#include "adc.h"

uint16_t ir_values[4];

void read_IR_sensors(void)
{
    // Skeleton đọc ADC PA4-PA7
    // TODO: implement ADC read
    ir_values[0] = HAL_ADC_GetValue(&hadc1); // PA4
    ir_values[1] = HAL_ADC_GetValue(&hadc1); // PA5
    ir_values[2] = HAL_ADC_GetValue(&hadc1); // PA6
    ir_values[3] = HAL_ADC_GetValue(&hadc1); // PA7
}
