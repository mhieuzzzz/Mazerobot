#include "ir_sensor.h"
#include "main.h"

/* ADC handle defined in main.c (CubeMX) */
extern ADC_HandleTypeDef hadc1;

/* ir_values: index mapping you can adapt to wiring:
   0 -> front, 1 -> right, 2 -> left, 3 -> back
*/
uint16_t ir_values[IR_SENSOR_COUNT] = {0};

void read_IR_sensors(void)
{
    // This is a simple polling sequence reading 4 ADC channels sequentially.
    // CubeMX must configure ADC to scan channels PA4,PA5,PA6,PA7 in this order
    // or you can configure and use HAL_ADC_GetValue per channel with channel config.

    HAL_ADC_Start(&hadc1);
    for(int i=0;i<IR_SENSOR_COUNT;i++)
    {
        if(HAL_ADC_PollForConversion(&hadc1, 10) == HAL_OK)
        {
            ir_values[i] = HAL_ADC_GetValue(&hadc1);
        } else {
            ir_values[i] = 0;
        }
        // If ADC configured single-channel, you must change channel between reads.
        // TODO: if using single-channel, call HAL_ADC_ConfigChannel with corresponding ADC_Channel_X before start.
    }
    HAL_ADC_Stop(&hadc1);
}
