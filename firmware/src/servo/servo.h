#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "math.h"

#define SERVO_GPIO 18 // GPIO support mcpwm: 2, 4, 12–19, 21–23, 25–27, 32–33

#define SERVO_MIN_PULSE_US 900
#define SERVO_MAX_PULSE_US 2100

#define SERVO_MIN_ANGLE -90
#define SERVO_MAX_ANGLE 90

typedef struct
{
    float currentAngle;
    float targetAngle;
    float speed;
    bool isMoving;
} servo_state_t;

void initMCPWNServoChannel();
void servoUpdate(uint32_t dt);

void setServoAbsoluteAngle(float angle, float speed);
void setServoRelativeAngle(float angle, float speed);

float getServoAngle();
