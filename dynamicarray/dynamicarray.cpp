#include <assert.h>
#include <iostream>

#include "dynamicarray.hpp"

#define PASS (1U)
#define FAIL (0U)

int cntError = 0;

static void printError(const std::exception &e, int lineNum, const char *function)
{
    std::cerr << "Error " << ++cntError
              << " at [line " << lineNum 
              << ", funtion " << function
              << "] : " << e.what() << std::endl;
}

int main(void)
{
    /* Test 1: create DA, check length, capacity and if empty. */
    DynamicArray<int> da1;
    assert(DynamicArray<int>::DEFAULT_DYNAMIC_ARRAY_SIZE == da1.getCapacity());
    assert(0 == da1.getSize());
    assert(true == da1.isEmpty());

    /* Test 2: Creating DA with negative capacity should throw an exception. */
    try
    {
        DynamicArray<int> da2(-2);
    }
    catch (const std::runtime_error &e)
    {
        printError(e, __LINE__, __FUNCTION__);
    }

    /* Test 3: Setting value at an index beyond length of the array should throw an exception. */
    try
    {
        da1.set(0, 30);
    }
    catch (const std::out_of_range &e)
    {
        printError(e, __LINE__, __FUNCTION__);
    }

    /* Test 4: Create a DA of capactiy 2, add 3 elements and make sure it doubles in capacity. */
    DynamicArray<int> da3(2);
    assert(0 == da3.getSize());
    assert(2 == da3.getCapacity());
    da3.append(25);
    assert(1 == da3.getSize());
    assert(2 == da3.getCapacity());
    da3.append(30);
    assert(2 == da3.getSize());
    assert(2 == da3.getCapacity());
    da3.append(45);
    assert(3 == da3.getSize());
    assert(4 == da3.getCapacity());
    assert(25 == da3.get(0));
    da3.set(0, 50);
    assert(30 == da3.get(1));
    da3.set(1, 55);
    assert(45 == da3.get(2));
    da3.set(2, 60);
    assert(50 == da3.get(0));
    assert(55 == da3.get(1));
    assert(60 == da3.get(2));
    try
    {
        da3.set(3, 65);
    }
    catch (const std::out_of_range &e)
    {
        printError(e, __LINE__, __FUNCTION__);
    }

    /* Test 5: Remove an element from the DA and make sure the array is shifted up. */
    assert(55 == da3.removeAt(1));
    assert(2 == da3.getSize());
    assert(50 == da3.get(0));
    assert(60 == da3.get(1));
    try
    {
        (void)da3.get(2);
    }
    catch (const std::out_of_range &e)
    {
        printError(e, __LINE__, __FUNCTION__);
    }

    /* Test 6: Check that contains only finds values within the legal length of the DA. */
    assert(true == da3.contains(50));
    assert(false == da3.contains(55));

    return 0;
}
