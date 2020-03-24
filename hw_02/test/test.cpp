#include "test.h"
#include <iostream>


int Test::failedNum = 0;
int Test::totalNum = 0;

void Test::check(bool expr, const char *func, const char  *filename, size_t lineNum) {
    ++Test::totalNum;
    if (!expr) {
        std::cout << "Assertion failed in func: '" << func << "', in file: '" << filename << "', line: " << lineNum << '\n';
        ++Test::failedNum;
    }
}

bool Test::showFinalResult() {
    std::cout << "Passed " << totalNum - failedNum << '/' << totalNum << '\n';
    if (failedNum == 0) return true;
    return false;
}