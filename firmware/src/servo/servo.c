#include "./servo.h"

#include "driver/mcpwm_prelude.h"
#include "esp_log.h"

servo_state_t servoState = {0};

static mcpwm_timer_handle_t timer = NULL;
static mcpwm_oper_handle_t operator = NULL;
static mcpwm_cmpr_handle_t comparator = NULL;
static mcpwm_gen_handle_t generator = NULL;

static inline uint32_t angleToPulseUs(float angle)
{
    float normalized = (angle - SERVO_MIN_ANGLE) / (SERVO_MAX_ANGLE - SERVO_MIN_ANGLE);
    float pulse = SERVO_MIN_PULSE_US + (SERVO_MAX_PULSE_US - SERVO_MIN_PULSE_US) * normalized;

    return (uint32_t)pulse;
}

static void setServoPulseUs(float angle)
{
    uint32_t pulseUs = angleToPulseUs(angle);
    mcpwm_comparator_set_compare_value(comparator, pulseUs);

    ESP_LOGI("SET_PULSE", "Angle: %.2f -> Pulse: %u us", angle, pulseUs);
}

void setServoAbsoluteAngle(float angle, float speed)
{
    servoState.targetAngle = angle < SERVO_MIN_ANGLE
                                 ? SERVO_MIN_ANGLE
                             : angle > SERVO_MAX_ANGLE
                                 ? SERVO_MAX_ANGLE
                                 : angle;

    servoState.speed = speed;
    servoState.isMoving = true;
}

void setServoRelativeAngle(float angle, float speed)
{
    setServoAbsoluteAngle(servoState.currentAngle + angle, speed);
}

void servoUpdate(uint32_t dt)
{
    if (!servoState.isMoving)
    {
        return;
    }

    float delta = servoState.targetAngle - servoState.currentAngle;
    float dir = (delta > 0) ? 1.0f : -1.0f;
    float step = servoState.speed * (dt / 1000.0f);

    if (fabsf(delta) <= step)
    {
        servoState.currentAngle = servoState.targetAngle;
        servoState.isMoving = false;
    }
    else
    {
        servoState.currentAngle += dir * step;
    }

    setServoPulseUs(servoState.currentAngle);
}

void initMCPWNServoChannel()
{
    mcpwm_timer_config_t timer_config = {
        .group_id = 0,
        .clk_src = MCPWM_TIMER_CLK_SRC_DEFAULT,
        .resolution_hz = 1 * 1000 * 1000,
        .period_ticks = 20000,
        .count_mode = MCPWM_TIMER_COUNT_MODE_UP,
    };

    mcpwm_new_timer(&timer_config, &timer);

    mcpwm_operator_config_t operator_config = {
        .group_id = 0,
    };

    mcpwm_new_operator(&operator_config, &operator);
    mcpwm_operator_connect_timer(operator, timer);

    mcpwm_comparator_config_t comparator_config = {
        .flags.update_cmp_on_tez = true,
    };

    mcpwm_new_comparator(operator, &comparator_config, &comparator);

    mcpwm_generator_config_t generator_config = {
        .gen_gpio_num = SERVO_GPIO,
    };

    mcpwm_new_generator(operator, &generator_config, &generator);

    mcpwm_generator_set_action_on_timer_event(
        generator,
        MCPWM_GEN_TIMER_EVENT_ACTION(MCPWM_TIMER_DIRECTION_UP, MCPWM_TIMER_EVENT_EMPTY, MCPWM_GEN_ACTION_HIGH));

    mcpwm_generator_set_action_on_compare_event(
        generator,
        MCPWM_GEN_COMPARE_EVENT_ACTION(MCPWM_TIMER_DIRECTION_UP, comparator, MCPWM_GEN_ACTION_LOW));

    mcpwm_timer_enable(timer);
    mcpwm_timer_start_stop(timer, MCPWM_TIMER_START_NO_STOP);

    setServoPulseUs(.0f);
}

float getServoAngle()
{
    return servoState.currentAngle;
}
