#include <iostream>
#include <cassert>
#include <vector>
#include <functional>
#include "hashtable.h"



int main(int argc, char const *argv[]) {
    std::cout << std::hash<std::string>()("a") << "\n";
    HashTable<int, int> myTable {};
    for (int i = 0; i < 50; i++)
    {
        int val = i * 2;
        myTable.insert(i, val);
    }
    std::cout << myTable;
    return 0;
}

