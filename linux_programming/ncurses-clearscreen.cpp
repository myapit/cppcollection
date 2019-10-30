#include <iostream>
#include <curses.h>

using namespace std;
int main()
{
    initscr();
    (void)echo();
    refresh();
    cout << "yadayada"<<endl;
    //clear();
    cout << "Enter keyinterget :";
    char n;
    cin >> n;
    cout << "output : " << n << endl;
    cout << "..." << endl;
    cin.get();
     //clear();
     //endwin();
    return 0;
}
