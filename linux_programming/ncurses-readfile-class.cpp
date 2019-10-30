#include <fstream>
#include <iostream>
#include <string>

#include <ncurses.h>

class ncursewrap
{
    public:
    ncursewrap()   { initscr();    }
    ~ncursewrap()  { endwin();     }
    void refresh() { ::refresh();  }
};

int main()
{
    std::ifstream inputfile("file.txt");
    std::string line;

    ncursewrap nc;

    if(inputfile.is_open())
    {
        while (inputfile >> line)
        {
            printw("%s\n", line.c_str());
        }
    } else
    {
        printw("didnt find file `file.txt`\n");
    }

    nc.refresh();

    std::cin.ignore();
}