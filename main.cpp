#include "hashtable.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cassert>
#include <vector>

template <>
int HashTable<std::string, int>::null_object_ = 0;

void simple_int()
{
    HashTable<int, int> myTable {};
    for (int i = 0; i < 50; i++)
    {
        int val = i * 2;
        myTable.insert(i, val);
    }
    std::cout << myTable;
}

void string_test()
{
    std::ifstream input_file("teststrings.txt");
    HashTable<std::string, int> table {100};
    // read file of strings to put into hash table
    std::string input;
    int i = 1;
    while (std::getline(input_file, input))
    {
        table.insert(input, i);
        i++;
    }
    input_file.close();

    // output to file for better readability
    std::ofstream output_file("teststringsoutput.txt");
    output_file << table;
    output_file.close();
    std::string testget = "decision";
    std::cout << table.get(testget) << "\n";

    table.remove(testget);

    std::cout << table.get(testget) << "\n";

}


int main(int argc, char const *argv[])
{
    string_test();
    return 0;
}

