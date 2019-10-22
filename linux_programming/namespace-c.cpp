/*
 * Author: myapit
 * Demo of using multiple namespace 
 *
 */

#include <iostream>
#include <string>


namespace nsOne {
    class myObjOne {
        private:
            std::string strHello="Hello";
        public:
        std::string sayHello()
    	{
            return strHello + " myapit.";
	    }   

        int lengthHello()
        {
            return strHello.size();
        }   
    };
}

using namespace std;
int main()
{
    nsOne::myObjOne useObj;
    
    cout << "Namespace Object Ouput :" << useObj.sayHello() << endl;
    cout << "NS int output:" << useObj.lengthHello() << endl;

    std::cout << "Press any key to exit .. ";
	std::cin.get();
}
