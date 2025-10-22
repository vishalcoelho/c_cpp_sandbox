#include "stack.h"
#include <stdio.h>
#include <assert.h>

int main(void)
{
    stack_t s, *ps = &s;

    stack_init(ps);

    assert(stack_pop(ps, NULL) == STACK_EMPTY);
    int tmp;
    assert(stack_pop(ps, &tmp) == STACK_EMPTY);

    for (int i = 0; i < MAX_STACK_SIZE; ++i)
    {
        (void)stack_push(ps, i);
        stack_print(ps);
    }
    assert(stack_pop(ps, NULL) == STACK_ERROR);
    assert(stack_push(ps, 10) == STACK_FULL);

    while(!stack_is_empty(ps))
    {
        assert(stack_pop(ps, &tmp) == STACK_SUCCESS);
        printf("popped %d\n", tmp);
    }

    assert(stack_pop(ps, &tmp) == STACK_EMPTY);
    return 0;
}