#include "freertos/FreeRTOS.h"
#include "freertos/timers.h"
#include "driver/gpio.h"

static TimerHandle_t testTimer;
static bool level = false;

static void test_signal_cb(TimerHandle_t xTimer)
{
    level = !level;
    gpio_set_level(GPIO_NUM_2, level);
}

void start_test_signal(void)
{
    gpio_config_t cfg = {
        .pin_bit_mask = 1ULL << GPIO_NUM_2,
        .mode = GPIO_MODE_OUTPUT,
    };
    gpio_config(&cfg);

    testTimer = xTimerCreate(
        "test_signal",
        pdMS_TO_TICKS(50),
        pdTRUE,
        NULL,
        test_signal_cb);

    xTimerStart(testTimer, 0);
}
