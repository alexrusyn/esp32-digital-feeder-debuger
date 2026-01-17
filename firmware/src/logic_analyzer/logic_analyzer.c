#include "logic_analyzer.h"
#include "driver/rmt_rx.h"

#include "esp_log.h"

volatile uint32_t debug = 0;

static rmt_channel_handle_t rxChannel;
static rmt_symbol_word_t rxSymbols[RMT_MEM_SYMBOLS];

static logic_analyzer_sample_t samplesBuffer[LOGIC_ANALYZER_MAX_SAMPLES];
static size_t sampleCount;

static void *notifyCtx;

static rmt_receive_config_t receiveConf = {
    .signal_range_min_ns = 50,
    .signal_range_max_ns = 3276750,
};

static void processSamples(size_t symbolsNum, rmt_symbol_word_t *samples)
{
    sampleCount = 0;

    for (size_t i = 0; i < symbolsNum && sampleCount < LOGIC_ANALYZER_MAX_SAMPLES; i++)
    {
        samplesBuffer[sampleCount++] = (logic_analyzer_sample_t){
            .level = samples[i].level0,
            .duration = samples[i].duration0,
        };

        if (sampleCount >= LOGIC_ANALYZER_MAX_SAMPLES)
            break;

        samplesBuffer[sampleCount++] = (logic_analyzer_sample_t){
            .level = samples[i].level1,
            .duration = samples[i].duration1,
        };
    }
}

static bool rmtRxDoneISR(
    rmt_channel_handle_t channelHandler,
    const rmt_rx_done_event_data_t *eData,
    void *userCtx)
{
    debug++;

    notifyCtx = userCtx;
    return true;
}

void initLogicAnalyzer(gpio_num_t gpio, void *ctx)
{
    notifyCtx = ctx;

    rmt_rx_channel_config_t rxChannelConfig = {
        .clk_src = RMT_CLK_SRC_DEFAULT,
        .resolution_hz = RMT_RESOLUTION_HZ,
        .mem_block_symbols = RMT_MEM_SYMBOLS,
        .gpio_num = gpio,
    };

    rmt_new_rx_channel(&rxChannelConfig, &rxChannel);

    rmt_rx_event_callbacks_t cbs = {
        .on_recv_done = rmtRxDoneISR,
    };

    rmt_rx_register_event_callbacks(rxChannel, &cbs, NULL);
    rmt_enable(rxChannel);
}

void startLogicAnalyzerCapture()
{
    rmt_receive(rxChannel, rxSymbols, RMT_MEM_SYMBOLS, &receiveConf);
}

size_t getLogicAnalyzerSamples(const logic_analyzer_sample_t **out)
{
    processSamples(RMT_MEM_SYMBOLS, rxSymbols);

    *out = samplesBuffer;
    return sampleCount;
}

uint32_t getDebug()
{
    return debug;
}