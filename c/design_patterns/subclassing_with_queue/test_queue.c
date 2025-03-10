#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include "queue.h"

int main(void)
{
    Queue* myQ;
    myQ = Queue_create();

    // Add elements to the queue
    int curr_head;
    for(int j=0, k=1000; j<QUEUE_SIZE; ++j, --k)
    {
        curr_head = myQ->head;
        myQ->insert(myQ, k);
        printf("Inserting %d at position %d, size=%d\n", k, curr_head, myQ->get_size(myQ));
    }

    // Remove elements from the queue
    int curr_tail;
    for(int j=0, k=INT_MIN; j<QUEUE_SIZE; ++j)
    {
        curr_tail = myQ->tail;
        k = myQ->remove(myQ);
        printf("Removing %d at position %d, size=%d\n", k, curr_tail, myQ->get_size(myQ));
    }


    Queue_destroy(myQ);

    return EXIT_SUCCESS;
}