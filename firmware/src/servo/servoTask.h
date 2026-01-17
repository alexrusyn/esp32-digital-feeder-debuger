#pragma once

#include "./servo.h"

#include "freertos/FreeRTOS.h"
#include "esp_timer.h"

static inline uint64_t getTime()
{
    return esp_timer_get_time() / 1000;
}

void servoTask(void *pvParams)
{
    uint64_t prevTime = getTime();

    while (1)
    {
        uint64_t nowTime = getTime();
        uint32_t dt = nowTime - prevTime;

        prevTime = nowTime;

        servoUpdate(dt);

        vTaskDelay(pdMS_TO_TICKS(20)); // 50Hz
    }
}