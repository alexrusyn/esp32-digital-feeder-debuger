#include "encoder.h"
#include "driver/gpio.h"
#include "esp_log.h"

static const char *TAG = "ENCODER";
static pcnt_unit_t enc_unit = PCNT_UNIT_0;

void encoder_init(gpio_num_t pinA, gpio_num_t pinB)
{
    pcnt_config_t pcnt_config = {
        .pulse_gpio_num = pinA,
        .ctrl_gpio_num = pinB,
        .channel = PCNT_CHANNEL_0,
        .unit = enc_unit,
        .pos_mode = PCNT_COUNT_INC,
        .neg_mode = PCNT_COUNT_DEC,
        .lctrl_mode = PCNT_MODE_KEEP,
        .hctrl_mode = PCNT_MODE_REVERSE,
        .counter_h_lim = 32767,
        .counter_l_lim = -32767};

    ESP_ERROR_CHECK(pcnt_unit_config(&pcnt_config));
    ESP_ERROR_CHECK(pcnt_counter_clear(enc_unit));
    ESP_ERROR_CHECK(pcnt_counter_resume(enc_unit));

    ESP_LOGI(TAG, "Encoder initialized on A=%d B=%d", pinA, pinB);
}

int64_t encoder_get_count(void)
{
    int16_t count;
    pcnt_get_counter_value(enc_unit, &count);
    return (int64_t)count;
}

void encoder_clear(void)
{
    pcnt_counter_clear(enc_unit);
}