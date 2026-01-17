#pragma once

#include "logic_analyzer.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "esp_log.h"

static TaskHandle_t taskHandler;

void logicAnalyzerTask(void *pvParameter)
{
    ESP_LOGI("LA_TEST", "logic_analyzer_task started");

    taskHandler = xTaskGetCurrentTaskHandle();

    initLogicAnalyzer(GPIO_NUM_4, taskHandler);
    startLogicAnalyzerCapture();

    while (1)
    {
        ESP_LOGI("LA_TEST", "Waiting for RMT...");
        ulTaskNotifyTake(pdTRUE, portMAX_DELAY);
        ESP_LOGI("LA_TEST", "RMT ISR hit count = %lu", getDebug());

        const logic_analyzer_sample_t *samples;
        size_t count = getLogicAnalyzerSamples(&samples);

        for (size_t i = 0; i < count; i++)
        {
            ESP_LOGI(
                "logic_analyzer",
                "level: %u, duration: %u",
                samples[i].level,
                samples[i].duration);
        }

        // startLogicAnalyzerCapture();
    }
}