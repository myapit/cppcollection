#include <cstdlib>
#include "list.hpp"

using namespace std;

int main (int argc, char** argv)
{
  List Apit;

  Apit.AddNode(9);
  Apit.AddNode(1);
  Apit.AddNode(3);
  Apit.AddNode(5);
  Apit.AddNode(7);
  Apit.PrintList();

  Apit.DeleteNode(3);
  Apit.PrintList();


  return 0;
} //end main