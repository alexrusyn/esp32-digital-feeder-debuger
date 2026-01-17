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

// #include "logic_analyzer/logic_analyzer.h"
#include "logic_analyzer/task.h"

#include "test.h"

#define ENC_A 34
#define ENC_B 35
#define STEP 26
#define DIR 25
#define EN 27

void app_main()
{
    // initLed();
    // initMCPWNServoChannel();

    // startServer();

    start_test_signal();

    // xTaskCreate(servoTask, "servo_task", 2048, NULL, 5, NULL);
    xTaskCreate(logicAnalyzerTask, "logic_analyzer_task", 4096, NULL, 10, NULL);

    // setServoAbsoluteAngle(0, 1500);

    // vTaskDelay(pdMS_TO_TICKS(5000));

    // setServoAbsoluteAngle(90, 1500);

    // encoder_init(ENC_A, ENC_B);
    // motor_init(STEP, DIR, EN);

    // motor_enable(true);
}