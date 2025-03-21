#ifndef CACHED_QUEUE_H_
#define CACHED_QUEUE_H_

#include "queue.h"

typedef struct CachedQueue CachedQueue;

/**
 * @brief Cached Queue Sub-Class
 *
 * The CachedQueue *EXTENDS* the base Queue class by adding the ability to write
 * to disk.
 */
struct CachedQueue
{
    // Base Class
    Queue* queue;

    // New attributes
    char filename[80];
    int num_elems_on_disk;

    // private attributes
    FILE * fid;
    int fwrite;
    int fread;


    // Aggregation in sub-class
    Queue* output_queue;

    // Inherited virtual functions
    int (*is_full)(CachedQueue* const me);
    int (*is_empty)(CachedQueue* const me);
    size_t (*get_size)(CachedQueue* const me);
    void (*insert)(CachedQueue* const me, int k);
    int (*remove)(CachedQueue* const me);

    // new virtual functions
    void (*flush)(CachedQueue* const me);
    void (*load)(CachedQueue* const me);
};

/**
 * @brief Test if Queue is full
 *
 * @param me
 * @return int 1 Queue is full, 0 still has room
 */
int CachedQueue_is_full(CachedQueue* const me);


/**
 * @brief Test if queue is empty
 *
 * @param me
 * @return int 1 queue is empty, 0 has stuff
 */
int CachedQueue_is_empty(CachedQueue* const me);

/**
 * @brief Get the size of the queue
 *
 * @param me
 * @return size_t
 */
size_t CachedQueue_get_size(CachedQueue* const me);

/**
 * @brief Insert an element into the queue at the tail end
 *
 * @param me
 * @param k Element
 */
void CachedQueue_insert(CachedQueue* const me, int k);

/**
 * @brief Remove an element from the head of the queue
 *
 * @param me
 * @return int
 */
int CachedQueue_remove(CachedQueue* const me);

/**
 * @brief Write the insert buffer to disk
 *
 * To be called when insert buffer is full
 *
 * @param me
 */
void CachedQueue_flush(CachedQueue* const me);

/**
 * @brief Load data into the insert buffer from disk
 *
 * To be called only when insert buffer is empty
 *
 * @param me
 */
void CachedQueue_load(CachedQueue* const me);

/**
 * @brief Constructor for the CacheqQueue class
 *
 * @param me
 * @param filename file name, not to exceed 80 chars
 * @param is_full_fxn Function Pointer
 * @param is_empty_fxn Function Pointer
 * @param get_size_fxn Function Pointer
 * @param insert_fxn Function Pointer
 * @param remove_fxn Function Pointer
 * @param flush_fxn Function Pointer
 * @param load_fxn Function Pointer
 */
void CachedQueue_init(CachedQueue* const me,
    char* filename,
    int (*is_full_fxn)(CachedQueue* const me),
    int (*is_empty_fxn)(CachedQueue* const me),
    size_t (*get_size_fxn)(CachedQueue* const me),
    void (*insert_fxn)(CachedQueue* const me, int k),
    int (*remove_fxn)(CachedQueue* const me),
    void (*flush_fxn)(CachedQueue* const me),
    void (*load_fxn)(CachedQueue* const me)
);


 /**
 * @brief Destructor
 *
 * @param me
 */
void CachedQueue_cleanup(CachedQueue* const me);

/**
 * @brief Create an object of the CachedQueue class on the heap
 *
 * @return CachedQueue* Pointer to the object
 */
CachedQueue* CachedQueue_create(void);

/**
 * @brief Destroy an object of the Queue class
 *
 * @param me
 */
void CachedQueue_destroy(CachedQueue* const me);

#endif // CACHED_QUEUE_H_