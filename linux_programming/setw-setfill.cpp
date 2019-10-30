/*
 * Author : myapit
 * Purpose: example of setw and setfill usage
 */

#include <iostream>
#include <iomanip>

using namespace std; // in small code example only
int main()
{
    cout << setw(10) << "Hello\n";
    cout << setfill('#') << setw(20) << "hai\n";

    return 0;
}

/*
output:

    Hello
################hai


*/
