#include <assert.h>
#include <iostream>

#include "dynamicarray.hpp"
#include "../utils/utils.hpp"

int main(void)
{
    printStartOfTest();
    /* Test 1: create DA, check length, capacity and if empty. */
    DynamicArray<int> da1;
    assert(DynamicArray<int>::DEFAULT_DYNAMIC_ARRAY_SIZE == da1.GetCapacity());
    assert(0 == da1.GetSize());
    assert(true == da1.IsEmpty());

    /* Test 2: Creating DA with negative capacity should throw an exception. */
    try
    {
        DynamicArray<int> da2(-2);
    }
    catch (const std::runtime_error &e)
    {
        printException(e, __LINE__, __FUNCTION__);
    }

    /* Test 3: Setting value at an index beyond length of the array should throw an exception. */
    try
    {
        da1.Set(0, 30);
    }
    catch (const std::out_of_range &e)
    {
        printException(e, __LINE__, __FUNCTION__);
    }

    /* Test 4: Create a DA of capactiy 2, add 3 elements and make sure it doubles in capacity. */
    DynamicArray<int> da3(2);
    assert(0 == da3.GetSize());
    assert(2 == da3.GetCapacity());
    da3.Append(25);
    assert(1 == da3.GetSize());
    assert(2 == da3.GetCapacity());
    da3.Append(30);
    assert(2 == da3.GetSize());
    assert(2 == da3.GetCapacity());
    da3.Append(45);
    assert(3 == da3.GetSize());
    assert(4 == da3.GetCapacity());
    assert(25 == da3.Get(0));
    da3.Set(0, 50);
    assert(30 == da3.Get(1));
    da3.Set(1, 55);
    assert(45 == da3.Get(2));
    da3.Set(2, 60);
    assert(50 == da3.Get(0));
    assert(55 == da3.Get(1));
    assert(60 == da3.Get(2));
    try
    {
        da3.Set(3, 65);
    }
    catch (const std::out_of_range &e)
    {
        printException(e, __LINE__, __FUNCTION__);
    }

    /* Test 5: Remove an element from the DA and make sure the array is shifted up. */
    assert(55 == da3.RemoveAt(1));
    assert(2 == da3.GetSize());
    assert(50 == da3.Get(0));
    assert(60 == da3.Get(1));
    try
    {
        (void)da3.Get(2);
    }
    catch (const std::out_of_range &e)
    {
        printException(e, __LINE__, __FUNCTION__);
    }

    /* Test 6: Check that Contains only finds values within the legal length of the DA. */
    assert(true == da3.Contains(50));
    assert(false == da3.Contains(55));
    printEndOfTest();

    return 0;
}
