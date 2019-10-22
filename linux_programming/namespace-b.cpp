/*
 * Author: myapit
 * Demo of using multiple namespace 
 *
 */

#include <iostream>
#include <string>

namespace one {
	int num = 100;
   
    int addNum()
	{
		return num+100;
	}
}

namespace two {
	std::string strHello="Hello";

    std::string sayHello()
	{
        return strHello + " myapit.";
	}

    int lengthHello()
    {
        return strHello.size();
    }
}


int main()
{
	std::cout << "Variable Number from ns one: " << one::num << std::endl;
	std::cout << "Func Number from ns one : " << one::addNum() << std::endl;
    std::cout << "Var from ns two :" << two::strHello << std::endl;
    std::cout << "Func from ns two: " << two::sayHello() << std::endl;
    std::cout << "Hello len.: " << two::lengthHello() << std::endl;

    std::cout << "Press any key to exit .. ";
	std::cin.get();
}
