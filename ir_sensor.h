#ifndef IR_SENSOR_H
#define IR_SENSOR_H
#include "main.h"

#define IR_SENSOR_COUNT 4

extern uint16_t ir_values[IR_SENSOR_COUNT];

/* Thresholds (tune trên thực tế) */
#define IR_THRESHOLD_FRONT 2000
#define IR_THRESHOLD_SIDE  1800

void read_IR_sensors(void);

#endif // IR_SENSOR_H
