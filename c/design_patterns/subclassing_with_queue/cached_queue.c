#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "cached_queue.h"

int CachedQueue_is_full(CachedQueue* const me)
{
    return (me->queue->is_full(me->queue) &&
            me->output_queue->is_full(me->output_queue));
}

int CachedQueue_is_empty(CachedQueue* const me)
{
    return (me->queue->is_empty(me->queue) &&
            me->output_queue->is_empty(me->output_queue) &&
            (me->num_elems_on_disk == 0));
}

size_t CachedQueue_get_size(CachedQueue* const me)
{
    return (me->queue->get_size(me->queue) +
            me->output_queue->get_size(me->output_queue) +
            me->num_elems_on_disk);
}

void CachedQueue_insert(CachedQueue* const me, int k)
{
    if(me->queue->is_full(me->queue))
    {
        // if the insert queue is full, flush it to disk
        me->flush(me);
    }
    // insert the next element into the insert buffer
    me->queue->insert(me->queue, k);
}

int CachedQueue_remove(CachedQueue* const me)
{
    if (!me->output_queue->is_empty(me->output_queue))
    {
        // if there is data in the output queue, return it
        return me->output_queue->remove(me->output_queue);
    }
    else if (me->num_elems_on_disk > 0)
    {
        // if the output queue is empty but there are elements on disk, load as
        // much as possible to the output queue and remove the oldest entry.
        me->load(me);
        return me->output_queue->remove(me->output_queue);
    }
    else
    {
        // Nothing is left on disk and output queue is empty, remove from the insert buffer
        return me->queue->remove(me->queue);
    }
}

void CachedQueue_flush(CachedQueue * const me)
{
    // Continue writing from where i left off
    if (fseek(me->fid, me->fwrite, SEEK_SET) != 0)
    {
        perror("Unable to recover write position");
        exit(EXIT_FAILURE);
    }

    printf("Flush: start write at pos %d\n", me->fwrite);

    while(!me->queue->is_empty(me->queue))
    {
        // drain the insert buffer and save each element to disk
        int elem = me->queue->remove(me->queue);
        (void)fwrite(&elem, sizeof(elem), 1, me->fid);
        me->num_elems_on_disk++;
    }

    me->fwrite = ftell(me->fid);
    printf("Flush: end write at pos %d\n", me->fwrite);

}

void CachedQueue_load(CachedQueue * const me)
{
    // Continue reading from where i left off
    if (fseek(me->fid, me->fread, SEEK_SET) != 0)
    {
        perror("Unable to recover read position");
        exit(EXIT_FAILURE);
    }
    printf("Load: start read at pos %d\n", me->fread);

    // keep loading elements from disk into the output queue until full, or
    // until we reach the end of file; said differently, keep load from file
    // while output queue has space AND we haven't reached the end of file.
    while (!me->output_queue->is_full(me->output_queue) &&
           !feof(me->fid))
    {
        int elem;
        (void)fread(&elem, sizeof(elem), 1, me->fid);
        me->output_queue->insert(me->output_queue, elem);
        me->num_elems_on_disk--;
    }

    me->fread = ftell(me->fid);
    printf("Load: end read at pos %d\n", me->fread);
}

void CachedQueue_init(CachedQueue* const me,
    char* filename,
    int (*is_full_fxn)(CachedQueue* const me),
    int (*is_empty_fxn)(CachedQueue* const me),
    size_t (*get_size_fxn)(CachedQueue* const me),
    void (*insert_fxn)(CachedQueue* const me, int k),
    int (*remove_fxn)(CachedQueue* const me),
    void (*flush_fxn)(CachedQueue* const me),
    void (*load_fxn)(CachedQueue* const me))
{
    // Initialize base class
    me->queue = Queue_create();

    // Initialize sub-class attributes
    me->num_elems_on_disk = 0;
    strcpy(me->filename, filename);

    // Initialize private attributes
    // open file in binary mode, overwrite exsiting or create new
    // if doesn't exist
    me->fid = fopen(me->filename, "wb+");
    if (me->fid == NULL){
        perror("Error Occured creating/opening file!");
        exit(EXIT_FAILURE);
    }
    me->fwrite = 0;
    me->fread = 0;


    // Initialize aggregates
    me->output_queue = Queue_create();

    // Init sub-class virtual function pointers
    me->is_full = is_full_fxn;
    me->is_empty = is_empty_fxn;
    me->get_size = get_size_fxn;
    me->insert = insert_fxn;
    me->remove = remove_fxn;
    me->flush = flush_fxn;
    me->load = load_fxn;
}

void CachedQueue_cleanup(CachedQueue* const me)
{
    // clean up aggregates
    Queue_cleanup(me->output_queue);

    // Close file
    fclose(me->fid);

    // clean up base class
    Queue_cleanup(me->queue);
}

CachedQueue * CachedQueue_create(void)
{
    CachedQueue* me  = (CachedQueue *)malloc(sizeof(CachedQueue));
    if (me != NULL)
    {
        CachedQueue_init(me, "queuebuffer.dat",
            CachedQueue_is_full, CachedQueue_is_empty, CachedQueue_get_size, CachedQueue_insert,
            CachedQueue_remove, CachedQueue_flush, CachedQueue_load);
    }

    return me;
}

void CachedQueue_destroy(CachedQueue* const me)
{
    if (me != NULL)
    {
        CachedQueue_cleanup(me);
    }

    free(me);

}
