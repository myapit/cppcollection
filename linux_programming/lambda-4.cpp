/* lam.cpp */
#include <iostream>
using namespace std;

int main()
{
  /* case #1 - compiler deduces return type */
  cout << [](int n) {return n*n;} (5);
  cout << endl;
  /* case #2 - explicit return type */
  cout << [](int n)->int {return n*n;} (5);

  return 0;
}