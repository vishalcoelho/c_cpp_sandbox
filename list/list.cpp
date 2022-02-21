#include <assert.h>
#include <iostream>

#include "list.hpp"
#include "../utils/utils.hpp"

static int testListIsEmpty(List<int> &listOfInts);
static int testListHasNNodes(List<int> &listOfInts, int nodeCount);

int main(void)
{
    printStartOfTest();
    List<int> listOfInts;
    assert(PASS == testListIsEmpty(listOfInts));

    int x = 20, y = 25, z = 30;
    listOfInts.AddLast(x);
    listOfInts.AddLast(y);
    listOfInts.AddLast(z);
    assert(PASS == testListHasNNodes(listOfInts, 3));

    assert(30 == listOfInts.RemoveLast());
    assert(25 == listOfInts.RemoveLast());
    assert(20 == listOfInts.RemoveLast());
    try
    {
        assert(0 == listOfInts.RemoveLast());
    }
    catch(const std::runtime_error& e)
    {
        printError(e, __LINE__, __FUNCTION__);
    }
    printEndOfTest();
    return 0;
}

static int testListIsEmpty(List<int> &listOfInts)
{
    int retval = FAIL;

    if (listOfInts.IsEmpty())
        retval = PASS;

    return (retval);
}

static int testListHasNNodes(List<int> &listOfInts, int nodeCount)
{
    int retval = FAIL;

    if (nodeCount == listOfInts.GetSize())
        retval = PASS;

    return (retval);
}
