#include <assert.h>
#include <stdexcept>

#include "binaryheap.hpp"
#include "../utils/utils.hpp"

static void testPQInitCorrect(BinaryHeap<int> &heap);
static void testPQInitCorrect(BinaryHeap<int> &heap, int size);
static void testPQAddAndSwim(BinaryHeap<int> &heap);

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
}

static void testPQInitCorrect(BinaryHeap<int> &heap, int size)
{
    assert(0 == heap.GetSize());
    assert(size == heap.GetCapacity());
}

static void testPQAddAndSwim(BinaryHeap<int> &heap)
{
    heap.Add(4);
    heap.Add(3);
    heap.Add(2);
    heap.Add(1);
    heap.Add(0);

    assert(true == heap.IsMinHeap(0));
}