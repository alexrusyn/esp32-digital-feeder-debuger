#pragma once
#include <stdint.h>
#include "driver/gpio.h"

void motor_init(gpio_num_t step, gpio_num_t dir, gpio_num_t en);
void motor_enable(bool en);
void motor_set_dir(bool dir);
void motor_step_pulse(void);