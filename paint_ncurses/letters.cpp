#include<cstring>
#include<ncurses.h>

//Elements for creating letters.......
void uphorizontal(int height,int row,int col)
{	for(int i=0;i<=height;i++)	mvprintw(row,col+i,"*");}

void uphorizontalhalf1(int height,int row,int col)
{       for(int i=0;i<=height/2;i++)	mvprintw(row,col+i,"*");}


void midhorizontal(int height,int row,int col)
{	for(int i=0;i<=height;i++)	mvprintw(row+((height-1)/2),col+i,"*");}

void midhorizontalhalf1(int height,int row,int col)
{       for(int i=0;i<=height/2;i++)      mvprintw(row+((height-1)/2),col+i,"*");}

void midhorizontalhalf2(int height,int row,int col)
{       for(int i=height/2;i<=height;i++)      mvprintw(row+((height-1)/2),col+i,"*");}

void downhorizontal(int height,int row,int col)
{	for(int i=0;i<=height;i++)	mvprintw(row+height,col+i,"*");}

void downhorizontalhalf1(int height,int row,int col)
{       for(int i=0;i<=height/2;i++)      mvprintw(row+height,col+i,"*");}

void leftdown(int height,int row,int col)
{	for(int i=0;i<=height;i++)	mvprintw(row+i,col,"*");}

void rightdown(int height,int row,int col)
{       for(int i=0;i<=height;i++)	mvprintw(row+i,col+height,"*");}

void middown(int height,int row,int col)
{       for(int i=0;i<=height;i++)	mvprintw(row+i,col+(height/2),"*");}

void middownhalf1(int height,int row,int col)
{       for(int i=0;i<=(height-1)/2;i++)	mvprintw(row+i,col+(height/2),"*");}

void middownhalf2(int height,int row,int col)
{       for(int i=(height-1)/2;i<=height;i++)   mvprintw(row+i,col+(height/2),"*");}

void leftdownhalf1(int height,int row,int col)
{       for(int i=0;i<=(height-1)/2;i++)      mvprintw(row+i,col,"*");}

void rightdownhalf1(int height,int row,int col)
{	for(int i=0;i<=(height-1)/2;i++)	mvprintw(row+i,col+height,"*");}

void rightdownhalf2(int height,int row,int col)
{	for(int i=(height+1)/2;i<=height;i++)	mvprintw(row+i,col+height,"*");}

void leftdiagonal(int height,int row,int col)
{       for(int i=0;i<=height;i++)        mvprintw(row+i,col+i,"*");}

void leftdiagonalhalf1(int height,int row,int col)
{	for(int i=0;i<=(height+1)/2;i++)	mvprintw(row+i,col+i,"*");}

void leftdiagonalhalf2(int height,int row,int col)
{	for(int i=(height+1)/2;i<=height;i++)	mvprintw(row+i,col+i,"*");}

void rightdiagonal(int height,int row,int col)
{       for(int i=0;i<=height;i++)        mvprintw(row+i,col+height-i,"*");}

void rightdiagonalhalf1(int height,int row,int col)
{       for(int i=0;i<=(height+1)/2;i++)	mvprintw(row+i,col+height-i,"*");}

void rightdiagonalhalf2(int height,int row,int col)
{       for(int i=(height+1)/2;i<=height;i++)	mvprintw(row+i,col+height-i,"*");}

//Main Function starts..........
void showord(char text[],int delay)
{	int row,col,Rowmax,Colmax,height;
	//self positioning and sizing acording to screen size...
//..............................................................................
        getmaxyx(stdscr,Rowmax,Colmax);
	row=(Rowmax/4)+(Rowmax/8);	height=(Rowmax/4);
	while(Colmax-((strlen(text))*(height+4)) <= 0)
	{	height=height-1;	}
	col=(Colmax-(strlen(text))*(height+4))/2;
//..............................................................................
        for(int pp=0;pp<strlen(text);pp++)
        {
                if(text[pp]=='A'||text[pp]=='a')
                        {       leftdown(height,row,col);
                                rightdown(height,row,col);
                                uphorizontal(height,row,col);
                                midhorizontal(height,row,col);
                        }
		else if(text[pp]=='B'||text[pp]=='b')
			{
				rightdownhalf2(height,row,col);
				middownhalf1(height,row,col);
				uphorizontalhalf1(height,row,col);
				midhorizontal(height,row,col);
				downhorizontal(height,row,col);
				leftdown(height,row,col);
			}
		else if(text[pp]=='C'||text[pp]=='c')
			{
				leftdown(height,row,col);
				uphorizontal(height,row,col);
				downhorizontal(height,row,col);
			}
		else if(text[pp]=='D'||text[pp]=='d')
			{
				rightdown(height,row,col);
				middown(height,row,col);
				uphorizontal(height,row,col);
				downhorizontal(height,row,col);
			}
		else if(text[pp]=='E'||text[pp]=='e')
			{
				leftdown(height,row,col);
				uphorizontal(height,row,col);
				midhorizontalhalf1(height,row,col);
				downhorizontal(height,row,col);
			}
		else if(text[pp]=='F'||text[pp]=='f')
			{
                                leftdown(height,row,col);
                                uphorizontal(height,row,col);
                                midhorizontalhalf1(height,row,col);
			}
		else if(text[pp]=='G'||text[pp]=='g')
			{
				leftdown(height,row,col);
                                uphorizontal(height,row,col);
				downhorizontal(height,row,col);
				rightdownhalf2(height,row,col);
				midhorizontalhalf2(height,row,col);
			}
		else if(text[pp]=='H'||text[pp]=='h')
			{	
				leftdown(height,row,col);
				rightdown(height,row,col);
				midhorizontal(height,row,col);
			}
		else if(text[pp]=='I'||text[pp]=='i')
			{
				middown(height,row,col);
				uphorizontal(height,row,col);
                                downhorizontal(height,row,col);
			}
		else if(text[pp]=='J'||text[pp]=='j')
			{
				middown(height,row,col);
                                uphorizontal(height,row,col);
                                downhorizontalhalf1(height,row,col);
			}	
		else if(text[pp]=='K'||text[pp]=='k')
                        {
				middown(height,row,col-((height-1)/2));
				rightdiagonalhalf1(height,row,col-((height-1)/2));
				leftdiagonalhalf2(height,row,col-((height-1)/2));
				col=col+(height/2)+4;
			        for(int pop=0;pop<delay;pop++);
        			refresh();
				continue;
                        }
		else if(text[pp]=='L'||text[pp]=='l')
                        {
                                downhorizontal(height,row,col);
				leftdown(height,row,col);
                        }
		else if(text[pp]=='M'||text[pp]=='m')
                        {
                                leftdown(height,row,col);
				rightdown(height,row,col);
				rightdiagonalhalf1(height,row,col);
                                leftdiagonalhalf1(height,row,col);
                        }
		else if(text[pp]=='N'||text[pp]=='n')
                        {
                                leftdown(height,row,col);
                                rightdown(height,row,col);
                                leftdiagonal(height,row,col);
                        }
		else if(text[pp]=='O'||text[pp]=='o')
                        {
                                leftdown(height,row,col);
                                rightdown(height,row,col);
				uphorizontal(height,row,col);
                                downhorizontal(height,row,col);
                        }
		else if(text[pp]=='P'||text[pp]=='p')
                        {
                                leftdown(height,row,col);
				uphorizontal(height,row,col);
				rightdownhalf1(height,row,col);
				midhorizontal(height,row,col);
                        }
		else if(text[pp]=='Q'||text[pp]=='q')
                        {
                                leftdown(height,row,col);
                                rightdown(height,row,col);
                                uphorizontal(height,row,col);
                                downhorizontal(height,row,col);
				leftdiagonalhalf2(height,row,col);
                        }
		else if(text[pp]=='R'||text[pp]=='r')
                        {
                                leftdown(height,row,col);
                                uphorizontal(height,row,col);
                                rightdownhalf1(height,row,col);
                                midhorizontal(height,row,col);
				leftdiagonalhalf2(height,row,col);
                        }
		else if(text[pp]=='S'||text[pp]=='s')
                        {
				uphorizontal(height,row,col);
				leftdownhalf1(height,row,col);
				midhorizontal(height,row,col);
				rightdownhalf2(height,row,col);
				downhorizontal(height,row,col);
                        }
		else if(text[pp]=='T'||text[pp]=='t')
                        {
                                uphorizontal(height,row,col);
				middown(height,row,col);
                        }
		else if(text[pp]=='U'||text[pp]=='u')
                        {
                                leftdown(height,row,col);
                                rightdown(height,row,col);
                                downhorizontal(height,row,col);

                        }
		else if(text[pp]=='V'||text[pp]=='v')
                        {
                                leftdown(height,row,col);
				rightdiagonal(height,row,col);

                        }
		else if(text[pp]=='W'||text[pp]=='w')
                        {
                                leftdown(height,row,col);
                                rightdown(height,row,col);
				leftdiagonalhalf2(height,row,col);
				rightdiagonalhalf2(height,row,col);

                        }
		else if(text[pp]=='X'||text[pp]=='x')
                        {
                                leftdiagonal(height,row,col);
				rightdiagonal(height,row,col);
                        }
		else if(text[pp]=='Y'||text[pp]=='y')
                        {
                                leftdiagonalhalf1(height,row,col);
                                rightdiagonalhalf1(height,row,col);
				middownhalf2(height,row,col);
                        }
		else if(text[pp]=='Z'||text[pp]=='z')
                        {
                                uphorizontal(height,row,col);
				downhorizontal(height,row,col);
				rightdiagonal(height,row,col);
                        }
		else if(text[pp]==' ')
                        {
 
                        }

	col=col+height+4;
	for(int pop=0;pop<delay;pop++);
	refresh();	

        }
}

