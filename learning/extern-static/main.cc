#include <iostream>
using namespace std; //ONLY FOR DEMO

int count = 100;

int getCount(); //function declare
int incrementNum();
int nonStaticNum();


int main()
{
    int num = 5;
    cout << getCount() << endl;
    for (int i = 0; i < 5; i++) 
    {
        cout << incrementNum() << " ";
        //output : 0 1 2 3 4
    }
    cout << endl;

    for (int i=0; i < 5; i++)
       cout << nonStaticNum() << "";

    cout << endl;

    cout << num << endl;
    return 0;
}
