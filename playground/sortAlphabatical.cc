#include <iostream>
#include <map>
#include <string>

using namespace std;

int main()
{
	typedef map(string,unsigned) wlist_t;
	wlist_t words;
	string word;
	while(cin){ cin >> word; words[word]+=1; }
	for(wlist_t::iterator i=words.begin(); i!=words.end(); i++)
	cout << i->first << ":" << i->second << endl;
}
