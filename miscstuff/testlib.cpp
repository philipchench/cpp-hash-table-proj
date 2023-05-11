#include "testlib.h"
#include <iostream>

int f(int x, int y) {
    int z = x + y;
    std::cout << "output is: " << z << "\n";
    return z;
}