#ifndef ENCODER_H
#define ENCODER_H
#include "main.h"

extern volatile int32_t left_encoder_count;
extern volatile int32_t right_encoder_count;

void encoder_init(void);
void encoder_update(void);

#endif // ENCODER_H
