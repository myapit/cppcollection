/*
Author : myapit
E-mail : 9w2xhr@gmail.com
Purpose: Learning note
*/

#include <iostream>

using std::cout;
using std::endl;

int main(int argc, char* argv[])
{
  cout << "Program to retrieve argc and argv[]." << endl;
  cout << "argc = " << argc << endl;
  cout << "What in argv[]: " << endl;

  for (int index = 0; index < argc; ++index)
  {
    cout << "argv[" << argc << "] = " << argv[index] << endl;
  }
  return 0;
}