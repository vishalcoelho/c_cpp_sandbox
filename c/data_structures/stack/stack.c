#include "stack.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 *       init -> push -> pop  -> push -> push -> push -> push  -> pop
 *                                                       [X]
 *       +--+    +--+    +--+    +--+    +--+    +--+    +--+    +--+
 *       |  |    |  |    |  |    |  |    |  |top>| c|top>| c|    |  |
 *       +--+    +--+    +--+    +--+    +--+    +--+    +--+    +--+
 *       |  |    |  |    |  |    |  |top>| b|    | b|    | b|top>| b|
 *       +--+    +--+    +--+    +--+    +--+    +--+    +--+    +--+
 *       |  |top>| a|    |  |top>| a|    | a|    | a|    | a|    | a|
 *       +--+    +--+    +--+    +--+    +--+    +--+    +--+    +--+
 *   top>            top>
 */



void stack_init(stack_t *s)
{
    s->top = -1;
}

stack_status_t stack_push(stack_t *s, int val)
{
    stack_status_t ret = STACK_SUCCESS;

    if (!stack_is_full(s))
    {
        s->store[++s->top] = val;
    }
    else
    {
        ret = STACK_FULL;
    }

    return ret;
}

stack_status_t stack_pop(stack_t *s, int *val)
{
    stack_status_t ret = STACK_SUCCESS;

    if(!stack_is_empty(s))
    {
        if(val != NULL)
        {
            memcpy(val, &s->store[s->top], sizeof(int));
            s->top--;
        }
        else
        {
            ret = STACK_ERROR;
        }
    }
    else
    {
        ret = STACK_EMPTY;
    }

    return ret;
}


stack_status_t stack_peek(stack_t *s, int *val)
{
    stack_status_t ret = STACK_SUCCESS;

    if(!stack_is_empty(s))
    {
        if(val != NULL)
        {
            memcpy(val, &s->store[s->top], sizeof(int));
        }
        else
        {
            ret = STACK_ERROR;
        }
    }
    else
    {
        ret = STACK_EMPTY;
    }

    return ret;
}


bool stack_is_empty(stack_t *s)
{
    return (s->top == -1);

}

bool stack_is_full(stack_t *s)
{
    return(s->top == (MAX_STACK_SIZE-1));
}

void stack_print(stack_t *s)
{
    if (!stack_is_empty(s))
    {
        for(int i = 0; i <= s->top; ++i)
        {
            printf("%d ", s->store[i]);
        }
        printf("\n");
    }
}