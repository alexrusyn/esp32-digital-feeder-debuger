#include "motor.h"
#include "driver/gpio.h"
#include "esp_rom_sys.h"

static gpio_num_t step_pin, dir_pin, en_pin;

void motor_init(gpio_num_t step, gpio_num_t dir, gpio_num_t en)
{
    step_pin = step;
    dir_pin = dir;
    en_pin = en;

    gpio_reset_pin(step_pin);
    gpio_reset_pin(dir_pin);
    gpio_reset_pin(en_pin);

    gpio_set_direction(step_pin, GPIO_MODE_OUTPUT);
    gpio_set_direction(dir_pin, GPIO_MODE_OUTPUT);
    gpio_set_direction(en_pin, GPIO_MODE_OUTPUT);

    motor_enable(false);
}

void motor_enable(bool en)
{
    gpio_set_level(en_pin, en ? 1 : 0);
}

void motor_set_dir(bool dir)
{
    gpio_set_level(dir_pin, dir ? 1 : 0);
}

void motor_step_pulse(void)
{
    gpio_set_level(step_pin, 1);
    esp_rom_delay_us(5);
    gpio_set_level(step_pin, 0);
    esp_rom_delay_us(5);
}
