#include "Utility.h"
#include "HashTable.hpp"

/* File from HashTable project
 * author: Rafał Surdej
 */

using namespace std;

void test1()
{
    cout << "Adding 3 elements into different table cells." << endl;
    HashTable<int, string> h1;
    h1.insert(10, "First");
    h1.insert(7, "Second");
    h1.insert(33, "Third");
    h1.print(cout);
    cout << endl;
}

void test2()
{
    cout << "Adding 3 elements into the same table cell." << endl;
    HashTable<int, string> h1;
    h1.insert(7, "First");
    h1.insert(7 + N, "Second");
    h1.insert(7 + 2*N, "Third");
    h1.print(cout);
    cout << endl;
}

void test3()
{
    cout << "Trying to add 2 elements with the same key, but different data." << endl;
    HashTable<int, string> h1;
    h1.insert(7, "First");
    h1.insert(7, "Second");
    h1.print(cout);
    cout << endl;
}

void test4()
{
    cout << "Deleting an element from a cell with only 1 element. 3 elements at beginnig." << endl;
    HashTable<int, string> h1;
    h1.insert(10, "First");
    h1.insert(7, "Second");
    h1.insert(33, "Third");
    h1.erase(10);
    h1.print(cout);
    cout << endl;
}

void test5()
{
    cout << "Deleting an element from the beginning of a list. 3 elements at beginnig." << endl;
    HashTable<int, string> h1;
    h1.insert(7, "First");
    h1.insert(7 + N, "Second");
    h1.insert(7 + 2*N, "Third");
    h1.erase(7);
    h1.print(cout);
    cout << endl;
}

void test6()
{
    cout << "Deleting an element from the middle of a list. 3 elements at beginnig." << endl;
    HashTable<int, string> h1;
    h1.insert(7, "First");
    h1.insert(7 + N, "Second");
    h1.insert(7 + 2*N, "Third");
    h1.erase(7 + N);
    h1.print(cout);
    cout << endl;
}

void test7()
{
    cout << "Deleting an element from the end of a list. 5 elements at beginnig." << endl;
    HashTable<int, string> h1;
    h1.insert(7, "First");
    h1.insert(7 + N, "Second");
    h1.insert(7 + 2*N, "Third");
    h1.insert(3, "Fourth");
    h1.insert(18, "Fifth");
    h1.erase(7 + 2*N);
    h1.print(cout);
    cout << endl;
}

void test8()
{
    cout << "Lets try to iterate through our table and test -> operator. We have 3 items." << endl;
    HashTable<int, string> h1;
    h1.insert(1, "First");
    h1.insert(7, "Second");
    h1.insert(13, "Third");
    for (HashTable<int, string>::iterator it = h1.begin(); it != h1.end(); ++it)
        cout << "key = " << it->key << " value = " << it->data << endl;
    cout << "Now testing operator *." << endl;
    for (HashTable<int, string>::iterator it = h1.begin(); it != h1.end(); ++it)
        cout << "key = " << (*it).key << " value = " << (*it).data << endl;
    cout << endl;
}

void test9()
{
    cout << "Comparig iterators - both are the same." << endl;
    HashTable<int, string> h1;
    h1.insert(1, "First");
    h1.insert(7, "Second");
    HashTable<int, string>::iterator it = h1.begin();
    HashTable<int, string>::iterator it2 = it;
    cout << "it == it2? " << (it == it2) << endl << "it != it2? " << (it != it2) << endl;
    cout << "They are different now." << endl;
    ++it2;
    cout << "it == it2? " << (it == it2) << endl << "it != it2? " << (it != it2) << endl;
    cout << endl;
}


void unit_tests()
{
    test1();
    test2();
    test3();
    test4();
    test5();
    test6();
    test7();
    test8();
    test9();
}
