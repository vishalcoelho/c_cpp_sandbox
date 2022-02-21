#ifndef UTILS_HPP_
#define UTILS_HPP_

#include <stdexcept>
#include <iostream>

#define PASS (1U)
#define FAIL (0U)

int cntError = 0;

static void printStartOfTest(void)
{
    std::cout << "=== Start of Test ===" << std::endl;
}

static void printEndOfTest(void)
{
    std::cout << "=== End of Test ===" << std::endl;
}

static void printError(const std::exception &e, int lineNum, const char *function)
{
    std::cerr << "Error " << ++cntError
              << " at [line " << lineNum 
              << ", funtion " << function
              << "] : " << e.what() << std::endl;
}

#endif /* UTILS_HPP_ */