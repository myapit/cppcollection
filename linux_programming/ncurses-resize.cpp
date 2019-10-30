#include <iostream>
#include <ncurses.h>
#include <fstream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include "termcolor.hpp"
#include <iomanip>
#include <sstream>
#include <vector>
#include <typeinfo>
#include <bits/stdc++.h>
#include <chrono>
enum state{normal, insrt, command, visual};
state current_state;
void rowminus2(std::string text)
{
    int row, col;
    getmaxyx(stdscr, row, col);
    move(row-2,0);
    char text2[text.length()+1];
    strcpy(text2, text.c_str());
    printw(text2);
}
int main()
{
    current_state=normal;
    int row,col;
    int current_x=0;
    int current_y=1;
    int c;
    initscr();
    raw();
    keypad(stdscr, TRUE);
    move(current_y,current_x);
    noecho();
    while((c=getch())!=530)
    {
        getmaxyx(stdscr,row,col);
        if(c==58&&current_state==normal)//:Command
        {
            current_state=command;
            move(row-2,0);
            clrtoeol();
            move(row-1,0);
            printw(":");
            echo();
            refresh();
            if(c==263||c==27)
            {
                clrtoeol();
                move(1,0);
                current_state=normal;
                noecho();
            }
            else
            {
                char comm[100];        
                getstr(comm);
                std::string comm_tos=comm;
                if(comm_tos=="o")//opening file
                {
                    move(row-2,0);
                    clrtoeol();
                    rowminus2("File Name: ");
                    refresh();
                    move(row-1,0);
                    clrtoeol();
                    char comm1[100];
                    getstr(comm1);
                    std::string filename=comm1;
                    move(row-2,0);
                    clrtoeol();
                    move(row-1,0);
                    clrtoeol();
                    current_state=normal;
                    move(1,0);
                    noecho();
                }
                else
                {
                    move(row-1,0);
                    clrtoeol();
                    move(row-2,0);
                    clrtoeol();
                    move(1,0);
                    noecho();
                    current_state=normal;
                }
            }
            
        }
        if(c==27&&current_state!=normal)
        {
            current_state=normal;
        }
        if(current_state==normal)
        {
            move(1,0);
            switch(c)
            {
                case 260:
                    
                    current_x--;
                    break;

                case 261:
                    current_x++;
                    break;

                case 259:
                    current_y--;
                    break;

                case 258:
                    current_y++;
                    break;

            }
            move(current_y,current_x);
            refresh();
        }
    }
    endwin();
    return 0;
}