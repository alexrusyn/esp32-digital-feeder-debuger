#include "control.h"

#include "encoder/encoder.h"
#include "motor/motor.h"

void control_move_to(int64_t target)
{
    int64_t pos = encoder_get_count();

    if (pos < target)
    {
        motor_set_dir(1);
        while (encoder_get_count() < target)
        {
            motor_step_pulse();
        }
    }
    else if (pos > target)
    {
        motor_set_dir(0);
        while (encoder_get_count() > target)
        {
            motor_step_pulse();
        }
    }
}