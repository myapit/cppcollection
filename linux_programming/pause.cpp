#include <ios>      // Required for streamsize
#include <iostream>
#include <istream>
#include <limits>   // Required for numeric_limits

void myflush ( std::istream& in )
{
  in.ignore ( std::numeric_limits<std::streamsize>::max(), '\n' );
  in.clear();
}

void mypause() 
{ 
  std::cout<<"Press [Enter] to continue . . .";
  std::cin.get();
} 

int main()
{
  int number;

  // Test with an empty stream
  std::cout<<"Hello, world!\n" ;
  mypause();

  // Leave extra input in the stream
  std::cout<<"Enter more than one character" ;

  myflush ( std::cin );
  mypause();

  std::cin.get();
}