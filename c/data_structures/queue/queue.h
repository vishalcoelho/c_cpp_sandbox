#ifndef __QUEUE_H__
#define __QUEUE_H__

#include <stdlib.h>
#include <stdbool.h>

/**
 * @brief Structure defines the elements of the queue.
 *
 */
typedef struct {
    int val;
}elem_t;

typedef enum {
    QUEUE_SUCCESS = 0,
    QUEUE_ERROR,
    QUEUE_FULL
}queue_status_t;

/**
 * @brief The queue structure itself
 *
 * A circular queue is a First-in-First-out (FIFO) structure meaning the first element to be queued up is
 * also the first element to be dequeued.
 *
 *              head                           tail
 *                |                             |
 *                v                             v
 *              +----+----+----+----+----+----+----+
 *    dequeue<--|    |    |    |    |    |    |    |<--enqueue
 *              +----+----+----+----+----+----+----+
 */
typedef struct {
    int head;   //!< Head index in the queue
    int tail;   //!< tail index in the queue
    size_t sz;  //!< current size of the queue
    size_t cap; //!< actual capacity of the queue
    elem_t *store; //!< pointer to the backing store
}queue_t;

/**
 * @brief A Queue constructor: create a queue of requested size
 *
 * @param size_of_queue Number of elements in the queue
 * @return queue_t * Pointer to the created queue
 */
queue_t * queue_create(size_t /* size_of_queue */);

/**
 * @brief Enqueue an element into the queue
 *
 * @param q Pointer to the queue
 * @param elem Element to queue up
 * @return queue_status_t QUEUE_SUCCESS if able to queue elem, QUEUE_FULL if queue is at capacity
 */
queue_status_t queue_enqueue(queue_t */* q */, elem_t */* elem */);

/**
 * @brief Dequeue an element from the queue
 * @param q Pointer to the queue
 * @return elem_t* Dequeued element
 */
elem_t * queue_dequeue(queue_t */* q */);

/**
 * @brief Check if the queue is empty
 *
 * @param q pointer to the queue
 * @return true empty
 * @return false not empty
 */
bool queue_is_empty(queue_t */* q */);

/**
 * @brief Check if the queue is full
 *
 * @param q pointer to the queue
 * @return true full
 * @return false not full
 */
bool queue_is_full(queue_t */* q */);

/**
 * @brief Peek at the head of the queue
 *
 * @param q pointer to the queue
 * @return elem_t* element at the head of the queue, or NULL, if empty.
 */
elem_t *queue_peek(queue_t */* q */);

/**
 * @brief Print the contents of the queue
 *
 * @param q pointer to the queue
 */
void queue_print(queue_t */* q */);

#endif // __QUEUE_H__
