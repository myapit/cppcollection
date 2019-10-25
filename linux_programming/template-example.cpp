/*
 * Author: hafeez
 * Purpose: example of using template syntax
 */

#include <iostream>

using namespace std;

template <class T>
T getMax (T a, T b) {
    return (a>b?a:b);
}

int main()
{
    int x=23, y=19, c;
    long j=1, k=14, m;
    c=getMax(x,y);
    m=getMax<long>(j,k);
    cout << c << endl;
    cout << m << endl;

    return 0;
}
