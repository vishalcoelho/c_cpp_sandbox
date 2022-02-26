#include <assert.h>
#include <stdexcept>

#include "binaryheap.hpp"
#include "../utils/utils.hpp"

static void testPQInitCorrect(BinaryHeap<int> &heap);
static void testPQInitCorrect(BinaryHeap<int> &heap, int size);
static void testPQAddAndSwim(BinaryHeap<int> &heap);
static void testPQPollAndSink(BinaryHeap<int> &heap);

int main (void)
{
    printStartOfTest();
    BinaryHeap<int> heap1;
    testPQInitCorrect(heap1);

    BinaryHeap<int> heap2(10);
    testPQInitCorrect(heap2, 10);

    BinaryHeap<int> heap3(5);
    testPQAddAndSwim(heap3);

    printEndOfTest();
    return 0;
}

static void testPQInitCorrect(BinaryHeap<int> &heap)
{
    assert(0 == heap.GetSize());
    assert(0 == heap.GetCapacity());
    printPass(__FUNCTION__);
}

static void testPQInitCorrect(BinaryHeap<int> &heap, int size)
{
    assert(0 == heap.GetSize());
    assert(size == heap.GetCapacity());
    printPass(__FUNCTION__);
}

static void testPQAddAndSwim(BinaryHeap<int> &heap)
{
    heap.Add(4);
    heap.Add(3);
    heap.Add(2);
    heap.Add(1);
    heap.Add(0);

    assert(true == heap.IsMinHeap(0));
    printPass(__FUNCTION__);
}

static void testPQPollAndSink(BinaryHeap<int> &heap)
{
    heap.Add(4);
    heap.Add(3);
    heap.Add(2);
    heap.Add(1);
    heap.Add(0);

    assert(0 == heap.Poll());
    assert(true == heap.IsMinHeap(0));
    assert(1 == heap.Poll());
    assert(true == heap.IsMinHeap(0));
    assert(3 == heap.Poll());
    assert(true == heap.IsMinHeap(0));
    assert(4 == heap.Poll());
    assert(true == heap.IsMinHeap(0));
    assert(2 == heap.Poll());
    assert(true == heap.IsMinHeap(0));

    assert(INT64_MAX == heap.Poll());
    printPass(__FUNCTION__);
}
