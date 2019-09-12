
#include <ncurses.h>

int barmenu(const char **array, const int row, const int col, const int arraylength, const int width, int menulength, int selection);

int main(void)
        {
        int selection,row=1, col=10, arraylength=10, width=5, menulength=5;
        const char *testarray[]={"Zero", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine"};
        initscr();
        noecho();
        keypad(stdscr,TRUE);

        selection=barmenu(testarray,row,col,arraylength,width,menulength,3);

        mvprintw(15,0,"Selection= %d",selection);
        refresh();
        getch();

        endwin();
        return 0;
        }

int barmenu(const char **array,const int row, const int col, const int arraylength, const int width, int menulength, int selection)
        {
        int counter,offset=0,ky=0;
        char formatstring[7];
        curs_set(0);

        if (arraylength < menulength)
                menulength=arraylength;

        if (selection > menulength)
                offset=selection-menulength+1;

        sprintf(formatstring,"%%-%ds",width); // remove - sign to right-justify the menu items

        while(ky != 27)
                {
                for (counter=0; counter < menulength; counter++)
                        {
                        if (counter+offset==selection)
                                attron(A_REVERSE);
                        mvprintw(row+counter,col,formatstring,array[counter+offset]);
                        attroff(A_REVERSE);
                        }

                ky=getch();

                switch(ky)
                        {
                        case KEY_UP:
                                if (selection)
                                        {
                                        selection--;
                                        if (selection < offset)
                                                offset--;
                                        }
                                break;
                        case KEY_DOWN:
                                if (selection < arraylength-1)
                                        {
                                        selection++;
                                        if (selection > offset+menulength-1)
                                                offset++;
                                        }
                                break;
                        case KEY_HOME:
                                selection=0;
                                offset=0;
                                break;
                        case KEY_END:
                                selection=arraylength-1;
                                offset=arraylength-menulength;
                                break;
                        case KEY_PPAGE:
                                selection-=menulength;
                                if (selection < 0)
                                        selection=0;
                                offset-=menulength;
                                if (offset < 0)
                                        offset=0;
                                break;
                        case KEY_NPAGE:
                                selection+=menulength;
                                if (selection > arraylength-1)
                                        selection=arraylength-1;
                                offset+=menulength;
                                if (offset > arraylength-menulength)
                                        offset=arraylength-menulength;
                                break;
                        case 10: //enter
                                return selection;
                                break;
                        case KEY_F(1): // function key 1
                                return -1;
                        case 27: //esc
                                // esc twice to get out, otherwise eat the chars that don't work
                                //from home or end on the keypad
                                ky=getch();
                                if (ky == 27)
                                        {
                                        curs_set(0);
                                        mvaddstr(9,77,"   ");
                                        return -1;
                                        }
                                else
                                        if (ky=='[')
                                                {
                                                getch();
                                                getch();
                                                }
                                        else
                                                ungetch(ky);
                        }
                }
        return -1;
        }
