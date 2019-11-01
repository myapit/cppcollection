/*
 * Author: myapit
 * Purpose: terminal application with menu
 *
 */

#include <iostream>
#include <iomanip>
#include <string>
#include <ncurses.h>

#include "linux_programming/termcolor.hpp"

class ncurseswrap
{
    public:
        ncurseswrap()   { initscr();    }
        ~ncurseswrap()  { endwin();     }
        void refresh() { ::refresh();  }
};

void terminal_menu()
{
    //ncursewrap nc;
    /* std::cout << "_    _            _ " << std::endl;    
    std::cout << "| |  | |          (_) " << std::endl;   
    std::cout << "| |  | | __ _ _ __ _ ___ " << std::endl;
    std::cout << "| |/\\| |/ _` | '__| / __|" << std::endl;
    std::cout << "\\  /\\  / (_| | |  | \\__ \\" << std::endl;
    std::cout << " \\/  \\/ \\__,_|_|  |_|___/" << std::endl; */

   
	std::cout << std::setfill('*') << std::setw(80) << std::endl; 
//	std::cout << std::setfill('x') << std::setw(10)  << std::endl;
     std::cout << " " << std::endl 
	      << "                                    " << std::endl 
              << termcolor::yellow
	      <<"██╗    ██╗ █████╗ ██████╗ ██╗███████╗ "  << std::endl
              <<"██║    ██║██╔══██╗██╔══██╗██║██╔════╝ "  << std::endl
              <<"██║ █╗ ██║███████║██████╔╝██║███████╗ "  << std::endl
              <<"██║███╗██║██╔══██║██╔══██╗██║╚════██║ "  << std::endl
              <<"╚███╔███╔╝██║  ██║██║  ██║██║███████║ "  << std::endl
              <<" ╚══╝╚══╝ ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝╚══════╝ "  << std::endl << termcolor::reset;
    
/*    
    printw("██╗    ██╗ █████╗ ██████╗ ██╗███████╗\n");
    printw("██║    ██║██╔══██╗██╔══██╗██║██╔════╝\n");
    printw("██║ █╗ ██║███████║██████╔╝██║███████╗\n");
    printw("██║███╗██║██╔══██║██╔══██╗██║╚════██║\n");
    printw(" ███╔███╔╝██║  ██║██║  ██║██║███████║\n");
    printw(" ╚══╝╚══╝ ╚═╝  ╚═╝╚═╝  ╚═╝╚═╝╚══════╝\n");
                                              
*/

    //nc.refresh();
}

int main() //int argc, char *argv[])
{
  //  ncurseswrap nc;
  //  attron(A_ALTCHARSET);
   // initscr();
   // (void)echo();
    //refresh();
    std::cout.flush();
    std::cout << "\033[2J\033[1;1H";
    terminal_menu();
  //  attroff(A_ALTCHARSET);
    //nc.refresh();
    //wrefresh(startScreen);
    //getch();
    std::cin.get();
    return 0;
}

