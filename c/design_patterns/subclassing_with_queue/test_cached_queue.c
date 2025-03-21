#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "cached_queue.h"

#define CACHED_QUEUE_SIZE   (3*QUEUE_SIZE)

int main(void)
{
    CachedQueue* myQ;
    myQ = CachedQueue_create();

    // Add elements to the queue
    int curr_head;
    for(int j=0, k=1000; j<CACHED_QUEUE_SIZE; ++j, --k)
    {
        curr_head = myQ->queue->head;
        myQ->insert(myQ, k);
        printf("Inserting %d at position %d, size=%d\n", k, curr_head, myQ->get_size(myQ));
    }

    // Remove elements from the queue
    int curr_tail;
    for(int j=0, k=INT_MIN; j<CACHED_QUEUE_SIZE; ++j)
    {
        curr_tail = myQ->queue->tail;
        k = myQ->remove(myQ);
        printf("Removing %d at position %d, size=%d\n", k, curr_tail, myQ->get_size(myQ));
    }


    CachedQueue_destroy(myQ);

    return EXIT_SUCCESS;
}