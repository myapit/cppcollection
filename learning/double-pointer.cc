#include <iostream>
#include <cstdlib>

using namespace std; 

int main() 
{ 
	int box = 5;
	int * ptr = &box;
	int ** dPtr = &ptr; 
	
    cout << "box holds: " << box << endl;
	cout << "box lives at: " << &box << endl;
	cout << "ptr points to address: " << ptr << endl;
	cout << "The thing that ptr points to has the value: " << *ptr << endl;
	cout << "ptr lives at: " << &ptr << endl;
	cout << "dPtr points to: " << dPtr << endl;
	cout << "The thing that dPtr points to has the value: " << *dPtr << endl;
	cout << "The ptr that dPtr points to, points to an int with the value: " << **dPtr << endl;
	cout << "dPtr lives at: " << &dPtr << endl; 

	cout << "\n\nThing:		dPtr 	             ptr	     box\n";
	cout << "Values:    [" << dPtr << " ]---->[" << ptr << "] ---->[" << box << "]\n";
	cout << "Addresses:  " << &dPtr << "       " << &ptr << "       " << &box << "\n";

	return 0;
}
