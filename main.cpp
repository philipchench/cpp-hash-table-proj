#include "hashtable.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cassert>
#include <vector>

class Test
{
    public:
        Test() 
        {
            std::cout << "Test object created. \n";
        }
        ~Test()
        {
            std::cout << "Test object destroyed. \n";
        }
        Test(const Test& obj)
        {
            std::cout << "Copy constructor called for Test object. \n";
        }
        Test operator=(const Test& obj)
        {
            std::cout << "Copy operator called for Test object. \n";
        }

        // custom stdout
        friend std::ostream& operator<< (std::ostream & out, const Test & t)
        {
            out << "Test object";
            return out;
        }

};

// template <>
// int HashTable<std::string, int>::null_object_ = 0;
// template <>
// int HashTable<int, int>::null_object_ = 0;
// template <>
// double HashTable<double, double>::null_object_ = 0;
// template <>
// double HashTable<int, double>::null_object_ = 0;


/*
    Simple insertion and get, makes sure that values get are correct
*/
void simple_int_insert_get()
{
    std::cout << "Test simple integer insertion and get: \n";
    HashTable<int, int> myTable {};
    int x = 1;
    int y = 2;
    myTable.insert(x, y);
    myTable.insert(y, x);
    std::cout << myTable;
    assert(myTable.get(x) == y);
    assert(myTable.get(y) == x);
    std::cout << "Success. \n";
}

/*
    Simple insertion and get for doubles
*/
void simple_double_insert_get()
{
    std::cout << "Test simple double insertion and get: \n";
    HashTable<double, double> myTable {};
    double x = 1.0;
    double y = 2.5;
    myTable.insert(x, y);
    myTable.insert(y, x);
    std::cout << myTable;
    assert(myTable.get(x) == y);
    assert(myTable.get(y) == x);
    std::cout << "Success. \n";
}

/*
    Simple insertion and get for int keys and double values
*/
void simple_int_double_insert_get()
{
    std::cout << "Test integer key double value insertion and get: \n";
    HashTable<int, double> myTable {};
    int x1 = 1;
    int x2 = 2;
    double y1 = 2.5;
    double y2 = 253477.55;
    myTable.insert(x1, y1);
    myTable.insert(x2, y2);
    std::cout << myTable;
    assert(myTable.get(x1) == y1);
    assert(myTable.get(x2) == y2);
    std::cout << "Success. \n";
}

/*
    insertion and get, but insert on same key
*/
void int_insert_override()
{
    std::cout << "Test integer insertion same key override value: \n";
    HashTable<int, int> myTable {};
    int x = 1;
    int y = 2;
    myTable.insert(x, y);
    std::cout << myTable;
    assert(myTable.get(x) == y);
    myTable.insert(x, x);
    std::cout << myTable;
    assert(myTable.get(x) == x);
    std::cout << "Success. \n";
}

/*
    inserting lots of integers
*/
void many_int()
{
    std::cout << "Test inserting many integers: \n";
    HashTable<int, int> myTable {};
    for (int i = 0; i < 1000; i++)
    {
        int val = i * 2;
        myTable.insert(i, val);
    }
    int x1 = 100;
    int y1 = 200;
    int x2 = 200;
    int y2 = 400;
    int x3 = 365;
    int y3 = 730;
    assert(myTable.get(x1) == y1);
    assert(myTable.get(x2) == y2);
    assert(myTable.get(x3) == y3);
    std::cout << myTable;
    std::cout << "Success. \n";
}

/*
    lots of strings and test remove
*/
void string_test()
{
    std::cout << "Test inserting many string keys and int values: \n";
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
    auto& testvalue = table.get(testget);
    std::cout << testvalue << "\n";
    assert(testvalue == 209);
    table.remove(testget);
    // should be gone!!
    testvalue = table.get(testget);
    std::cout << testvalue << "\n";
    assert(testvalue == 0);
    std::cout << "Success. \n";

}

/*
    test class object and see if properly destroyed
*/
void testclass()
{
    std::cout << "Test Test class and destruction when out of scope: \n";
    HashTable<std::string, Test> myTable {};
    std::string x1 = "test1"; // created
    std::string x2 = "test2"; // created
    Test t1 {};
    Test t2 {};
    myTable.insert(x1, t1); // copy constructor invoked then destroy temp obj
    myTable.insert(x2, t2);
    std::cout << myTable;
    std::cout << "Success. \n";
}


int main(int argc, char const *argv[])
{
    string_test();
    return 0;
}

