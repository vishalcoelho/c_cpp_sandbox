#include "Timer.h"

void timer1Callback(uintptr_t arg)
{
    (void)arg;
}

int main(void)
{
    Timer_Params params;
    Timer_Params_init(&params);

    if (0 > Timer_init(&params))
    {
        exit(1);
    }

    Timer_Id tid1 = Timer_start(200, Timer_RunMode_ONESHOT, timer1Callback, (uintptr_t)NULL);

    return 0;
}