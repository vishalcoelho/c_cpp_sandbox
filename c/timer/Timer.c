#include "Timer.h"

/** Oapaque structure with the timer implementation. */
typedef struct Timer_Object_t
{
    Timer_RunMode runMode;
    uint32_t period;
} Timer_Object;

void Timer_Params_init(Timer_Params *params)
{
    (void)params;
    if (NULL != params)
    {
        params->period = 0;
        params->runMode = Timer_RunMode_ONESHOT;
    }
}

int Timer_init(const Timer_Params *params)
{
}

Timer_Id Timer_start(uint32_t interval,
                     Timer_RunMode mode,
                     Timer_Callback cb,
                     uintptr_t arg)
{
}

void Timer_stop(Timer_Id id)
{
}
