#ifndef QUEUE_H_
#define QUEUE_H_

#define QUEUE_SIZE  10

typedef struct Queue Queue;

/**
 * @brief Queue Class
 *
 * Elements are added to the head of the queue and removed from the tail.
 * head always points to the next entry of the last one queued up while tail
 * points to the earliest.
 *
 * Queue is Empty
 *                                QUEUE_SIZE
 *                                v
 *   +-----------------------------+
 *   |--|..........................|
 *   +-----------------------------+
 *    ^^
 *    ||
 * head|
 *    tail
 *
 *
 * Adding Elements
 *                              QUEUE_SIZE
 *                              v
 * +-----------------------------+
 * |A|B|C|D|-|...................|
 * +-----------------------------+
 *  ^       ^
 *  |       |
 *  tail  head
 *
 * Removing Elements
 *                              QUEUE_SIZE
 *                              v
 * +-----------------------------+
 * |.|B|C|D|-|...................|
 * +-----------------------------+
 *    ^     ^
 *    |     |
 *    tailhead
 *
 * NOTE: the head and tail pointers may wrap around
 *
 *  *                              QUEUE_SIZE
 *                              v
 * +-----------------------------+
 * |Z|-|...............|U|V|W|X|Y|
 * +-----------------------------+
 *    ^                 ^
 *    |                 |
 *  head                tail
 */
struct Queue
{
    int buffer[QUEUE_SIZE];
    int head;
    int tail;
    int size;

    int (*is_full)(Queue* const me);
    int (*is_empty)(Queue* const me);
    size_t (*get_size)(Queue* const me);
    void (*insert)(Queue* const me, int k);
    int (*remove)(Queue* const me);
};

/**
 * @brief Test if Queue is full
 *
 * @param me
 * @return int 1 Queue is full, 0 still has room
 */
int Queue_is_full(Queue* const me);


/**
 * @brief Test if queue is empty
 *
 * @param me
 * @return int 1 queue is empty, 0 has stuff
 */
int Queue_is_empty(Queue* const me);

/**
 * @brief Get the size of the queue
 *
 * @param me
 * @return size_t
 */
size_t Queue_get_size(Queue* const me);

/**
 * @brief Insert an element into the queue at the tail end
 *
 * @param me
 * @param k Element
 */
void Queue_insert(Queue* const me, int k);

/**
 * @brief Remove an element from the head of the queue
 *
 * @param me
 * @return int
 */
int Queue_remove(Queue* const me);

/**
 * @brief Constructor for the Queue class
 *
 * @param me
 * @param is_full_fxn Function Pointer
 * @param is_empty_fxn Function Pointer
 * @param get_size_fxn Function Pointer
 * @param insert_fxn Function Pointer
 * @param remove_fxn Function Pointer
 */
void Queue_init(Queue* const me,
    int (*is_full_fxn)(Queue* const me),
    int (*is_empty_fxn)(Queue* const me),
    size_t (*get_size_fxn)(Queue* const me),
    void (*insert_fxn)(Queue* const me, int k),
    int (*remove_fxn)(Queue* const me)
);


 /**
 * @brief Destructor
 *
 * @param me
 */
void Queue_cleanup(Queue* const me);

/**
 * @brief Create an object of the Queue class on the heap
 *
 * @return Queue* Pointer to the object
 */
Queue * Queue_create(void);

/**
 * @brief Destroy an object of the Queue class
 *
 * @param me
 */
void Queue_destroy(Queue* const me);

#endif // QUEUE_H_