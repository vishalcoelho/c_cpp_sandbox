#include <assert.h>
#include <iostream>

#include "stack.hpp"
#include "../utils/utils.hpp"

static void testInitStackCorrect(Stack<int> &stack);
static void testStackPushPop(Stack<int> &stack);
static void testStackPeek(Stack<int> &stack);

int main(void)
{
    printStartOfTest();
    Stack<int> stack;
    testInitStackCorrect(stack);
    testStackPushPop(stack);
    testStackPeek(stack);
    printEndOfTest();
    return 0;
}

static void testInitStackCorrect(Stack<int> &stack)
{
    assert(0 == stack.GetSize());
    assert(true == stack.IsEmpty());
    printPass(__FUNCTION__);
}

static void testStackPushPop(Stack<int> &stack)
{
    stack.Push(10);
    assert(1 == stack.GetSize());
    stack.Push(15);
    assert(2 == stack.GetSize());
    stack.Push(20);
    assert(3 == stack.GetSize());
    stack.Push(30);
    assert(4 == stack.GetSize());
    assert(30 == stack.Pop());
    assert(3 == stack.GetSize());
    assert(20 == stack.Pop());
    assert(2 == stack.GetSize());
    assert(15 == stack.Pop());
    assert(1 == stack.GetSize());
    assert(10 == stack.Pop());
    assert(0 == stack.GetSize());
    try
    {
        (void)stack.Pop();
    }
    catch(const std::runtime_error& e)
    {
        printException(e, __LINE__, __FUNCTION__);
    }
    printPass(__FUNCTION__);
}

static void testStackPeek(Stack<int> &stack)
{
    stack.Push(10);
    stack.Push(15);
    assert(15 == stack.Peek());
    stack.Push(20);
    stack.Push(30);
    assert(30 == stack.Peek());
    (void)stack.Pop();
    (void)stack.Pop();
    (void)stack.Pop();
    (void)stack.Pop();
    try
    {
        (void)stack.Peek();
    }
    catch(const std::runtime_error& e)
    {
        printException(e, __LINE__, __FUNCTION__);
    }
    printPass(__FUNCTION__);
}