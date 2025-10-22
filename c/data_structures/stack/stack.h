#ifndef __STACK_H__
#define __STACK_H__

#include <stdbool.h>

#define MAX_STACK_SIZE  (13U)

/**
 * @brief Structure defining the stack
 *
 */
typedef struct
{
    int top;    //!< index to the top of the stack
    int store[MAX_STACK_SIZE]; //!< store for the stack
}
stack_t;

typedef enum {
    STACK_SUCCESS = 0,
    STACK_ERROR,
    STACK_FULL,
    STACK_EMPTY
}stack_status_t;

 /**
  * @brief Initialize the stack structure
  *
  * @param s Pointer to the stack object
  */
void stack_init(stack_t */* s */);

/**
 * @brief Push an element on to the stack
 *
 * @param s Pointer to the stack object
 * @param val value to push atop the stack
 * @return stack_status_t STACK_SUCCESS if successful, STACK_FULL if stack is full.
 */
stack_status_t stack_push(stack_t */* s */, int /* val */);

/**
 * @brief Pop a value off the top of the stack
 *
 * @param s Pointer to the stack object
 * @param val value popped from the stack, NULL if stack is empty
 * @return stack_status_t STACK_SUCCESS if successful, STACK_EMPTY if stack is empty
 */
stack_status_t stack_pop(stack_t */* s */, int */* val */);


/**
 * @brief Peek at the value at the top of the stack
 *
 * @param s Pointer to the stack object
 * @param val value at the top of the stack, NULL if stack is empty
 * @return stack_status_t STACK_SUCCESS if successful, STACK_EMPTY if stack is empty
 */
stack_status_t stack_peek(stack_t */* s */, int */* val */);

/**
 * @brief Check if the stack is empty
 *
 * @param s Pointer to the stack object
 * @return true
 * @return false
 */
bool stack_is_empty(stack_t */* s */);

/**
 * @brief Check if the stack is full
 *
 * @param s Pointer to the stack object
 * @return true
 * @return false
 */
bool stack_is_full(stack_t */* s */);

/**
 * @brief Print out the contents of the stack
 *
 * @param s Pointer to the stack object
 */
void stack_print(stack_t */* s */);

#endif // __STACK_H__