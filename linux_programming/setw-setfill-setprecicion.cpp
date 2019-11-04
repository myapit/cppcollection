#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
	    cout<<"USING setw() ..............\n";
	    cout<< setw(10) <<11<<"\n";
	    cout<< setw(10) <<2222<<"\n";
	    cout<< setw(10) <<33333<<"\n";
	    cout<< setw(10) <<4<<"\n";

	    cout<<"USING setw() & setfill() [type- I]...\n";
	    cout<< setfill('0');
	    cout<< setw(10) <<11<<"\n";
	    cout<< setw(10) <<2222<<"\n";
	    cout<< setw(10) <<33333<<"\n";
	    cout<< setw(10) <<4<<"\n";

	    cout<<"USING setw() & setfill() [type-II]...\n";
	    cout<< setfill('-')<< setw(10) <<11<<"\n";
	    cout<< setfill('*')<< setw(10) <<2222<<"\n";
	    cout<< setfill('@')<< setw(10) <<33333<<"\n";
	    cout<< setfill('#')<< setw(10) <<4<<"\n";
	    
		cout<<"USING fixed .......................\n";
		cout.setf(ios::floatfield,ios::fixed);
		cout<< setprecision(5)<<1234.537<< endl;

		cout<<"USING scientific ..................\n";
		cout.setf(ios::floatfield,ios::scientific);
		cout<< setprecision(5)<<1234.537<< endl;



		return 0;
}
