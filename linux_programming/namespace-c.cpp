/*
 * Author: myapit
 * Demo of using multiple namespace 
 *
 */

#include <iostream>
#include <string>

// Namespace with class
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

//namespace with class and method outside namespace
namespace nsTwo {
    class Vehical {
        private:
            int engineCapacity;
            std::string engineType;

         public:
            void setVehicalData();
            void displayData();
    };
}

void nsTwo::Vehical::setVehicalData()
{
    std::cout << "Setting Engine Capacity  (cc) and Engine Type (diesel, petrol, electric)." << std::endl;
    engineCapacity=1200;
    engineType="Petrol";
}

void nsTwo::Vehical::displayData()
{
    std::cout << "This car have cc of :" << engineCapacity << std::endl;
    std::cout << "This car use " << engineType << " as it fuel." << std::endl;
}

//namespace with class oside

namespace nsThree {
        class animal;
}

class nsThree::animal {
    private:
         std::string animalName;

    public:
         void displayAnimal()
         {
             animalName = "Harimau";
             std::cout << "Animal name Harimau." << std::endl;
         }

         static void kucing()
         {
             std::cout << "it kucing.." << std::endl;
         }
};

/*
 * Main Program
 */


using namespace std;

int main()
{
    nsOne::myObjOne useObj;
    cout << "Namespace Object Ouput :" << useObj.sayHello() << endl;
    cout << "NS int output:" << useObj.lengthHello() << endl;
     
    nsTwo::Vehical car;
    car.setVehicalData();
    car.displayData();
   
    nsThree::animal ani;
    ani.displayAnimal();
    nsThree::animal::kucing();

    std::cout << "--Program Terminated--" << std::endl;
}
