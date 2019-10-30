#include <fstream>
#include <iostream>
#include <string>

#include <ncurses.h>

int main()
{
    std::ifstream inputfile("filew.txt");
    std::string line;

    initscr();

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

    refresh();

    std::cin.ignore();
    endwin();
}