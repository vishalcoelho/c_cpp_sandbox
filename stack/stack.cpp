#include <assert.h>
#include <iostream>

#include "stack.hpp"

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


static void testInitStackCorrect(Stack<int> &stack);
static void testStackPushPop(Stack<int> &stack);
static void testStackPeek(Stack<int> &stack);

int main(void)
{
    Stack<int> stack;
    testInitStackCorrect(stack);
    testStackPushPop(stack);
    testStackPeek(stack);
    
    return 0;
}

static void testInitStackCorrect(Stack<int> &stack)
{
    assert(0 == stack.size());
    assert(true == stack.isEmpty());
}

static void testStackPushPop(Stack<int> &stack)
{
    stack.push(10);
    assert(1 == stack.size());
    stack.push(15);
    assert(2 == stack.size());
    stack.push(20);
    assert(3 == stack.size());
    stack.push(30);
    assert(4 == stack.size());
    assert(30 == stack.pop());
    assert(3 == stack.size());
    assert(20 == stack.pop());
    assert(2 == stack.size());
    assert(15 == stack.pop());
    assert(1 == stack.size());
    assert(10 == stack.pop());
    assert(0 == stack.size());
    try
    {
        (void)stack.pop();
    }
    catch(const std::runtime_error& e)
    {
        printError(e, __LINE__, __FUNCTION__);
    }
    
}

static void testStackPeek(Stack<int> &stack)
{
    stack.push(10);
    stack.push(15);
    assert(15 == stack.peek());
    stack.push(20);
    stack.push(30);
    assert(30 == stack.peek());
    (void)stack.pop();
    (void)stack.pop();
    (void)stack.pop();
    (void)stack.pop();
    try
    {
        (void)stack.peek();
    }
    catch(const std::runtime_error& e)
    {
        printError(e, __LINE__, __FUNCTION__);
    }    
}