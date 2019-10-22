/*
 * Author: myapit
 * Demo of using single namespace 
 *
 */

#include <iostream>

namespace {
	int num = 100;
   
    int addNum()
	{
		return num+100;
	}
}

int main()
{
	std::cout << "Variable Number : " << num << std::endl;
	std::cout << "Func Numbner : " << addNum() << std::endl;
	std::cin.get();
}
