#include <assert.h>
#include <iostream>

#include "queue.hpp"
#include "../utils/utils.hpp"

static void testInitQueueCorrect(Queue<int> &queue);
static void testQueueEnqueueDequeue(Queue<int> &queue);
static void testQueuePeek(Queue<int> &queue);

int main(void)
{
    printStartOfTest();
    Queue<int> queue;
    testInitQueueCorrect(queue);
    testQueueEnqueueDequeue(queue);
    testQueuePeek(queue);
    printEndOfTest();
    return 0;
}

static void testInitQueueCorrect(Queue<int> &queue)
{
    assert(0 == queue.GetSize());
    assert(true == queue.IsEmpty());
    printPass(__FUNCTION__);
}

static void testQueueEnqueueDequeue(Queue<int> &queue)
{
    queue.Enqueue(10);
    assert(1 == queue.GetSize());
    queue.Enqueue(15);
    assert(2 == queue.GetSize());
    queue.Enqueue(20);
    assert(3 == queue.GetSize());
    queue.Enqueue(30);
    assert(4 == queue.GetSize());
    assert(10 == queue.Dequeue());
    assert(3 == queue.GetSize());
    assert(15 == queue.Dequeue());
    assert(2 == queue.GetSize());
    assert(20 == queue.Dequeue());
    assert(1 == queue.GetSize());
    assert(30 == queue.Dequeue());
    assert(0 == queue.GetSize());
    try
    {
        (void)queue.Dequeue();
    }
    catch(const std::runtime_error& e)
    {
        printException(e, __LINE__, __FUNCTION__);
    }
    printPass(__FUNCTION__);
}

static void testQueuePeek(Queue<int> &queue)
{
    queue.Enqueue(10);
    queue.Enqueue(15);
    assert(10 == queue.Peek());
    queue.Enqueue(20);
    queue.Enqueue(30);
    assert(10 == queue.Peek());
    (void)queue.Dequeue();
    (void)queue.Dequeue();
    (void)queue.Dequeue();
    (void)queue.Dequeue();
    try
    {
        (void)queue.Peek();
    }
    catch(const std::runtime_error& e)
    {
        printException(e, __LINE__, __FUNCTION__);
    }
    printPass(__FUNCTION__);
}