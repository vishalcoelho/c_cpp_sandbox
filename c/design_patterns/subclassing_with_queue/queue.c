#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "queue.h"

int Queue_is_full(Queue* const me)
{
    return (me->size == QUEUE_SIZE);
}

int Queue_is_empty(Queue* const me)
{
    return(me->size == 0);
}

size_t Queue_get_size(Queue* const me)
{
    return me->size;
}

void Queue_insert(Queue* const me, int k)
{
    if (!me->is_full(me))
    {
        me->buffer[me->head] = k;
        me->head = (me->head + 1) % QUEUE_SIZE;
        ++me->size;
    }
}

int Queue_remove(Queue* const me)
{
    int value = INT_MIN;
    if (!me->is_empty(me))
    {
        value = me->buffer[me->tail];
        me->tail = (me->tail + 1) % QUEUE_SIZE;
        --me->size;
    }

    return value;
}

void Queue_init(Queue* const me,
    int (*is_full_fxn)(Queue* const me),
    int (*is_empty_fxn)(Queue* const me),
    size_t (*get_size_fxn)(Queue* const me),
    void (*insert_fxn)(Queue* const me, int k),
    int (*remove_fxn)(Queue* const me))
{
    me->head = 0;
    me->tail = 0;
    me->size = 0;

    // Init function pointers
    me->is_full = is_full_fxn;
    me->is_empty = is_empty_fxn;
    me->get_size = get_size_fxn;
    me->insert = insert_fxn;
    me->remove = remove_fxn;
}

void Queue_cleanup(Queue* const me)
{
    // @future Do Nothing for the moment
}

Queue * Queue_create(void)
{
    Queue* me  = (Queue *)malloc(sizeof(Queue));
    if (me != NULL)
    {
        Queue_init(me, Queue_is_full, Queue_is_empty, Queue_get_size, Queue_insert, Queue_remove);
    }

    return me;
}

void Queue_destroy(Queue* const me)
{
    if (me != NULL)
    {
        Queue_cleanup(me);
    }

    free(me);

}
