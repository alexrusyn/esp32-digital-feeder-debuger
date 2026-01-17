#pragma once

#include "stdint.h"
#include "driver/rmt_types.h"
#include "driver/gpio.h"

#define RMT_RESOLUTION_HZ 20 * 1000 * 1000
#define RMT_MEM_SYMBOLS 256 // 16Kb
// #define RX_BUF_SIZE (RMT_MEM_SYMBOLS * sizeof(rmt_symbol_word_t)) // 1 word = 4b, 4096 * 4 = 16384
#define LOGIC_ANALYZER_MAX_SAMPLES (RMT_MEM_SYMBOLS * 2)

typedef struct
{
    uint8_t level;
    uint32_t duration;
} logic_analyzer_sample_t;

void initLogicAnalyzer(gpio_num_t gpio, void *ctx);
void startLogicAnalyzerCapture(void);
size_t getLogicAnalyzerSamples(const logic_analyzer_sample_t **out);

uint32_t getDebug();