#ifndef TIMER_H__
#define TIMER_H__

#include <stdint.h>

typedef enum Timer_RunMode_t
{
    Timer_RunMode_ONESHOT = 0,
    Timer_RunMode_PERIODIC = 1
} Timer_RunMode;

typedef int8_t Timer_Id;

/** Timer callback definition.
 *  @param[in] id of the timer instance
 *  @param[in] arg user defined argument
 */
typedef void (*Timer_Callback)(Timer_Id id, uintptr_t arg);

/** Structure defining the parameter list used to initialize a Timer instance. */
typedef struct Timer_Params_t
{
    Timer_RunMode runMode; //!<  Mode of operation for this instance.
    uint32_t period;       //!< Programmed period.
} Timer_Params;

/**
 * @brief Initialize the timer parameters with defaults.
 * @param[in] params Pointer to a non-NULL param object.
 */
extern void Timer_Params_init(Timer_Params *params);

/**
 * @brief Initialize the timing provider from a parameter list.
 * @param[in] params pointer to the initialization parameters.
 * @return status of the initialization process, >0 on success.
 */
extern int Timer_init(const Timer_Params *params);

/**
 * @brief Start a timer with a specified interval
 * @param[in] interval Timer interval in milliseconds
 * @param[in] mode Run mode of the timer.
 * @param[in] cb Callback function--cannot be NULL.
 * @param[in] arg User supplied argument--can be NULL.
 * @return ID of a timer instance
 */
extern Timer_Id Timer_start(uint32_t interval,
                            Timer_RunMode mode,
                            Timer_Callback cb,
                            uintptr_t arg);

/**
 * @brief Cancel a timer instance.
 * @param[in] id ID of an instance of the timer object.
 */
extern void Timer_stop(Timer_Id id);

#endif // TIMER_H__