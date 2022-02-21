#include <assert.h>
#include <stdexcept>

#include "arraylist.hpp"
#include "../utils/utils.hpp"

static void testALInitCorrect(ArrayList<int> &arraylist, int size);
static void testALAddGetSet
(ArrayList<int> &arraylist);

int main (void)
{
    printStartOfTest();
    ArrayList<int> array1;
    testALInitCorrect(array1, 0);
    ArrayList<int> array2(5);
    testALInitCorrect(array2, 5);
    ArrayList<int> array3(2);
    testALAddGetSet
    (array3);
    printEndOfTest();
    return 0;
}

static void testALInitCorrect(ArrayList<int> &arraylist, int size)
{
    assert(size == arraylist.GetSize());
    assert(size == arraylist.GetCapacity());
}

static void testALAddGetSet
(ArrayList<int> &arraylist)
{
    arraylist.Add(10);
    arraylist.Add(20);
    assert(2 == arraylist.GetSize());
    try
    {
        arraylist.Add(30);
    }
    catch(const std::out_of_range& e)
    {
        printError(e, __LINE__, __FUNCTION__);
    }
    assert(10 == arraylist.Get(0));
    assert(20 == arraylist.Get(1));
    arraylist.Set(1, 30);
    assert(30 == arraylist.Get(1));

    try
    {
        arraylist.Set(3, 30);
    }
    catch(const std::out_of_range& e)
    {
        printError(e, __LINE__, __FUNCTION__);
    }

    try
    {
        arraylist.Get(3);
    }
    catch(const std::out_of_range& e)
    {
        printError(e, __LINE__, __FUNCTION__);
    }
}