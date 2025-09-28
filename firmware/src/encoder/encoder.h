#pragma once

#include <stdint.h>
#include "driver/gpio.h"
#include "driver/pcnt.h"

void encoder_init(gpio_num_t pinA, gpio_num_t pinB);
int64_t encoder_get_count(void);
void encoder_clear(void);