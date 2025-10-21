#include "queue.h"
#include <assert.h>
#include <stdio.h>

int main(void)
{
    queue_t *q = queue_create(10);

    if(q)
    {
        elem_t a = {.val = 15};
        elem_t b = {.val = 16};
        elem_t c = {.val = 17};
        elem_t d = {.val = 18};
        elem_t e = {.val = 19};
        elem_t f = {.val = 20};
        elem_t g = {.val = 21};
        elem_t h = {.val = 22};
        elem_t i = {.val = 23};
        elem_t j = {.val = 24};
        elem_t k = {.val = 25};

        elem_t *z = queue_dequeue(q);
        assert(z == NULL);

        printf("Enqueueing\n");
        (void)queue_enqueue(q, &a);
        (void)queue_enqueue(q, &b);
        (void)queue_enqueue(q, &c);

        assert(queue_is_empty(q) == false);
        assert(queue_is_full(q) == false);

        (void)queue_enqueue(q, &d);
        (void)queue_enqueue(q, &e);
        (void)queue_enqueue(q, &f);
        (void)queue_enqueue(q, &g);
        (void)queue_enqueue(q, &h);
        (void)queue_enqueue(q, &i);
        (void)queue_enqueue(q, &j);

        assert(queue_enqueue(q, &k) == QUEUE_FULL);
        assert(queue_is_full(q) == true);
        assert(queue_is_empty(q) == false);

        queue_print(q);

        printf("Dequeueing\n");
        while(!queue_is_empty(q)){
            z = queue_dequeue(q);
            printf("%d ",z->val);
        }
        printf("\n");

        assert(queue_is_empty(q) == true);

        printf("Enqueueing again\n");
        while(!queue_is_full(q)){
            (void)queue_enqueue(q, &a);
        }
        queue_print(q);

        printf("Dequeueing half\n");
        for (int i = 0; i < (q->cap/2); ++i)
        {
            z = queue_dequeue(q);
            printf("%d ", z->val);
        }
        printf("\n");
        printf("Remaining in Queue\n");
        queue_print(q);


        printf("Enqueueing half\n");
        for (int i = 0; i < (q->cap/2); ++i)
        {
            (void)queue_enqueue(q, &b);
        }
        queue_print(q);

    }
    else{
        printf("Could'nt create a queue\n");
    }


    return 0;
}