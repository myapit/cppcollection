/*
 * Author : myapit
 * E-mail : 9w2xhr@gmail.com
 * Purpose: Learning note
 * Compile: g++ --std=c++14
 * */

#include <iostream>

using namespace std;

int main()
{
    int mynum[5] = {1,2,3,4,5};

    // short version
    for (auto pl : mynum)
        cout << pl;
    
    cout << endl;
    // long version
    for (int i = 0; i != 5; ++i)
        cout << mynum[i];
    
    //other short example
    char a[] = {'a','b','c'};
    for (char& x : a) { std::cout << x ; }
    
    cout << endl;
    return 0;
}
