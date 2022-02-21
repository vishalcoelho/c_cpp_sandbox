#include <assert.h>
#include <iostream>

#include "list.hpp"

#define PASS (1U)
#define FAIL (0U)

static int testListIsEmpty(List<int> &listOfInts);
static int testListHasNNodes(List<int> &listOfInts, int nodeCount);

int main(void)
{
    List<int> listOfInts;
    assert(PASS == testListIsEmpty(listOfInts));

    int x = 20, y = 25, z = 30;
    listOfInts.addLast(x);
    listOfInts.addLast(y);
    listOfInts.addLast(z);
    assert(PASS == testListHasNNodes(listOfInts, 3));

    assert(30 == listOfInts.removeLast());
    assert(25 == listOfInts.removeLast());
    assert(20 == listOfInts.removeLast());
    try
    {
        assert(0 == listOfInts.removeLast());
    }
    catch(const std::runtime_error& e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}

static int testListIsEmpty(List<int> &listOfInts)
{
    int retval = FAIL;

    if (listOfInts.isEmpty())
        retval = PASS;

    return (retval);
}

static int testListHasNNodes(List<int> &listOfInts, int nodeCount)
{
    int retval = FAIL;

    if (nodeCount == listOfInts.getSize())
        retval = PASS;

    return (retval);
}
