
/*
http://www.cplusplus.com/forum/unices/36461/
This is a list of codes used in C++ to change the text color:

black - 30
red - 31
green - 32
brown - 33
blue - 34
magenta - 35
cyan - 36
lightgray - 37

Now these are the basic colours.

Usage of "\033[":
This is to handle the console cursor. I do not have a complete reference so I ask people who know about it to comment with what I do not have.

* 'm' character at the end of each of the following sentences is used as a stop character, where the system should stop and parse the \033[ sintax.
Rujukan

\033[0m - is the default color for the console
\033[0;#m - is the color of the text, where # is one of the codes mentioned above
\033[1m - makes text bold
\033[1;#m - makes colored text bold**
\033[2;#m - colors text according to # but a bit darker
\033[4;#m - colors text in # and underlines
\033[7;#m - colors the background according to #
\033[9;#m - colors text and strikes it
\033[A - moves cursor one line above (carfull: it does not erase the previously written line)
\033[B - moves cursor one line under
\033[C - moves cursor one spacing to the right
\033[D - moves cursor one spacing to the left
\033[E - don't know yet
\033[F - don't know yet

\033[2K - erases everything written on line before this.
*/
#include <iostream>
///#include <mysql.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <map>
#include <sstream>
#include <memory>
#include <stdexcept>
#include <cstdio>
#include <time.h>
#include <vector>

using namespace std;


/*namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}
*/

int main(int argc, char ** argv)
{
    //std::stringstream ss;
    //ss << 0;
    //std::string str = ss.str();
    //std::string default_console = "\033["+itoa(0)+"m";
    std::ostringstream ss;
    ss << 0;
    std::string default_console = "\033["+ ss.str() +"m";
    for (int i = 30; i <= 37; i++)
    {
        ss << i;
        std::string str = ss.str();
        
        //std::string color = "\033[0;"+itoa(i)+"m";
        std::string color = "\033[0;"+str+"m";

        std::cout<<color<<"test "<<i<<std::endl;

        //color = "\033[1"+itoa(i)+"m";
        color = "\033[1"+str+"m";

        std::cout<<color<<"test "<<i<<" bold"<<std::endl;
        std::cout<<default_console<<std::endl;

    }

    std::cout << "Done" << std::endl;

    return 0;
}
