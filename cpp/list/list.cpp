#include <assert.h>
#include <iostream>

#include "list.hpp"
#include "../utils/utils.hpp"

static void testListIsEmpty(List<int> &listOfInts);
static void testListHasNNodes(List<int> &listOfInts, int nodeCount);

int main(void)
{
    printStartOfTest();
    List<int> listOfInts;
    testListIsEmpty(listOfInts);

    int x = 20, y = 25, z = 30;
    listOfInts.AddLast(x);
    listOfInts.AddLast(y);
    listOfInts.AddLast(z);
    testListHasNNodes(listOfInts, 3);

    assert(30 == listOfInts.RemoveLast());
    assert(25 == listOfInts.RemoveLast());
    assert(20 == listOfInts.RemoveLast());
    try
    {
        assert(0 == listOfInts.RemoveLast());
    }
    catch(const std::runtime_error& e)
    {
        printException(e, __LINE__, __FUNCTION__);
    }
    printEndOfTest();
    return 0;
}

static void testListIsEmpty(List<int> &listOfInts)
{
    assert(true == listOfInts.IsEmpty());
    printPass(__FUNCTION__);
}

static void testListHasNNodes(List<int> &listOfInts, int nodeCount)
{
    assert(nodeCount == listOfInts.GetSize());
    printPass(__FUNCTION__);
}
