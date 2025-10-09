#include "led.h"

#include "driver/gpio.h"

#define LED_PIN 2

static bool ledState = false;

void initLed(void)
{
    gpio_reset_pin(LED_PIN);
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);
    gpio_set_level(LED_PIN, 0);
}

void toggleLed(void)
{
    setLedState(!ledState);
}

void setLedState(bool state)
{
    ledState = state;
    gpio_set_level(LED_PIN, state ? 1 : 0);
}

bool getLedState(void)
{
    return ledState;
}
