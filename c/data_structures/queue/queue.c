#include "queue.h"
#include <string.h>
#include <stdio.h>

queue_t * queue_create(size_t size_of_queue)
{
    // Using calloc() instead of malloc() as I want zero initialized memory.
    queue_t *q = (queue_t *)calloc(1, sizeof(queue_t));
    if (q != NULL)
    {
        q->store = (elem_t *)calloc(size_of_queue, sizeof(elem_t));
        if (q->store != NULL)
        {
            // We start head at a negative index as we will increment first before dequeuing
            //   head tail
            //      | |
            //      v v
            //     +----+----+----+----+----+----+----+
            //     |    |    |    |    |    |    |    |
            //     +----+----+----+----+----+----+----+
            q->head = 0;
            q->tail = 0;
            q->sz = 0;
            q->cap = size_of_queue;
        }
        else
        {
            // Cant allocate the store, destroy the queue and return it.
            free(q);
            // No dangling pointers!!!
            q = NULL;
        }
    }
    else
    {
        q = NULL;
    }

    return q;
}


queue_status_t queue_enqueue(queue_t *q, elem_t *elem)
{
    queue_status_t ret = QUEUE_SUCCESS;
    //      head            tail-.
    //       |               |   |
    //       v <-----sz----->v   v
    //     +----+----+----+----+----+----+----+
    //     | a  |  b | c  | d  | e  |    |    |
    //     +----+----+----+----+----+----+----+

    if (queue_is_full(q))
    {
        ret = QUEUE_FULL;
    }
    else
    {
        q->tail = (q->head + q->sz) % q->cap;
        memcpy(&q->store[q->tail], elem, sizeof(elem_t));
        q->sz++;
    }

    return ret;
}

elem_t * queue_dequeue(queue_t *q)
{
    elem_t *ret = NULL;

    //      head-.              tail
    //       |   |               |
    //       v <-|---sz--------->v
    //       v   v<---new_sz---->v
    //     +----+----+----+----+----+----+----+
    //     | a  |  b | c  | d  | e  |    |    |
    //     +----+----+----+----+----+----+----+

    if (!queue_is_empty(q))
    {
        ret = &q->store[q->head];
        q->head = (q->head + 1) % q->cap;
        q->sz--;
    }

    return ret;
}

bool queue_is_empty(queue_t *q)
{
    return (q->sz == 0);
}

bool queue_is_full(queue_t *q)
{
    return(q->sz == q->cap);

}

elem_t *queue_peek(queue_t *q)
{
    elem_t *ret = NULL;
    //  head +1        tail
    //   |    |         |
    //   v    v         v
    //     +----+----+----+----+----+----+----+
    //     | a  | b  |    |    |    |    |    |
    //     +----+----+----+----+----+----+----+
    if(!queue_is_empty(q))
    {
        return &q->store[q->head + 1];
    }

    return ret;
}

void queue_print(queue_t *q)
{
    for (int i = 0; i < q->sz; ++i)
    {
        int idx = (q->head + i) % q->cap;
        printf("%d ", q->store[idx].val);
    }
    printf("\n");
}
