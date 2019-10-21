/*
Author: myapit
Purpose:  sample of c++ on windows with make file. (using NMAKE)
*/

#include <iostream>
#include "myheader.h"

int main(int argc, char* argv[])
{
  std::cout << "Selamat datang ke ..." << std::endl;
 // std::cout << "Nombor dari header file:" << mynumber << std::endl;
  displayNumber();
  std::cout << "Tekan [Enter] untuk tutup" << std::endl;
  std::cin.get();

  return 0;
}