// #include "freertos/FreeRTOS.h"
// #include "freertos/task.h"

// #include "encoder/encoder.h"
// #include "motor/motor.h"
// #include "control/control.h"

#include "esp_log.h"

#include "led/led.h"

#include "server/server.h"

#include "servo/servo.h"
#include "servo/servoTask.h"

#define ENC_A 34
#define ENC_B 35
#define STEP 26
#define DIR 25
#define EN 27

static const char *TAG = "MAIN";

void app_main()
{
    initLed();
    // initMCPWNServoChannel();
    startServer();

    // xTaskCreate(servoTask, "servo_task", 2048, NULL, 5, NULL);

    // encoder_init(ENC_A, ENC_B);
    // motor_init(STEP, DIR, EN);

    // motor_enable(true);

    // while (1)
    // {
    //     control_move_to(200);
    //     vTaskDelay(pdMS_TO_TICKS(1000));

    //     control_move_to(0);
    //     vTaskDelay(pdMS_TO_TICKS(1000));
    // }
}