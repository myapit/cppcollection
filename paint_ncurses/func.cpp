#include<ncurses.h>
#include<cstring>
#include<cmath>
#include"func.h"

void stratAnime()
{
	int Rowmax,Colmax;
	getmaxyx(stdscr,Rowmax,Colmax);
	//screen wiping two rectangles from left and right
	for(int z=0;  z<((Colmax+2)/2);  z++)
	{
		for(int y=0;  y<Rowmax;  y++)
		{
			mvprintw(y,z,"#");
			mvprintw(y,Colmax-z,"#");
		}	
		for(int k=0;k<10000000;k++);	refresh();
	}
	//screen wipint half rectangles from up and bottom
       for(int z=((Rowmax+1)/2);  z<(((Rowmax+1)/4)*3); z++)
	{
		for(int y=0;  y<Colmax;  y++)
		{
			mvprintw(z,y," ");
			mvprintw(Rowmax-z,y," ");
		}
		for(int k=0;k<10000000;k++);	refresh();
	}
}
//============================================================================================

void fadeprint(int FProw, int FPcol,char text[],int delay)
{
	for(int fp1=0;fp1<strlen(text);fp1++)
	{
		mvprintw(FProw,FPcol+fp1,"%c",text[fp1]);
		refresh();
		for(int fp2=0;fp2<delay;fp2++);
	}
}
//============================================================================================

void getcordinates(int &Zrow,int &Zcol)
{
	int Rowmax,Colmax;
        getmaxyx(stdscr,Rowmax,Colmax);		attrset(COLOR_PAIR(5));
	mvprintw(Rowmax-1,(Colmax-44)/2,"...move curser & press P to put the shape...");
	noecho();
	keypad(stdscr,TRUE);
	Zrow=Rowmax/2;Zcol=Colmax/2;
	move(Zrow,Zcol);
//	getyx(stdscr,Zrow,Zcol);
	int  CH;	CH=getch();
	while(CH!='p'&& CH!='P')
	{
		if(CH==KEY_LEFT)	Zcol--;
		else if(CH==KEY_RIGHT)	Zcol++;
		else if(CH==KEY_DOWN)	Zrow++;
		else if(CH==KEY_UP)	Zrow--;
		if(Zcol<0)	Zcol=0;
		if(Zcol>Colmax)	Zcol=Colmax-1;
		if(Zrow<0)	Zrow=0;
		if(Zrow>Rowmax)	Zrow=Rowmax-1;

		mvprintw(Rowmax-1,Colmax-8,"%i",Zrow);
		mvprintw(Rowmax-1,Colmax-5,",");
		mvprintw(Rowmax-1,Colmax-4,"%i",Zcol);

		move(Zrow,Zcol);
		CH=getch();
	}
	echo();
}
//============================================================================================

void RECTANGLE(int Rrow,int Rcol,int Rheight,int Rwidth,char Rch)
{
        for(int Ri=0;Ri<Rwidth;Ri++)
        {       for(int Rj=0;Rj<Rheight;Rj++)
                        mvprintw(Rrow+Ri,Rcol+Rj,"%c",Rch);
        }

}
//============================================================================================

void TRIANGLE(int Trow,int Tcol,int Theight,int Ttype,char Tch)
{
                int TT1,TT2,II1,II2;
        for(int Ti=0;Ti<Theight;Ti++)
        {
                for(int Tj=Theight;Tj>Ti;Tj--)
                {
                        if(Ttype==1 || Ttype==5 || Ttype==6) { TT1=TT2=Tj; II1=II2=Ti; }
                        if(Ttype==3 || Ttype==7 || Ttype==8) { TT1=TT2=-Tj; II1=II2=Ti; }
                        if(Ttype==2) { TT1=-Ti; TT2=Ti; II1=Tj; II2=-Tj; }
                        if(Ttype==4) { TT1=-Ti; TT2=Ti; II1=-Tj; II2=Tj; }

                        if(Ttype==1 || Ttype==5 || Ttype==3 || Ttype==7 || Ttype==2 || Ttype==4)
                        {
                                mvprintw(Trow+TT1,Tcol-II1,"%c",Tch);
                        }
                        if(Ttype==1 || Ttype==6 || Ttype==3 || Ttype==8 || Ttype==2 || Ttype==4)
                        {
                                mvprintw(Trow+TT2,Tcol+II2,"%c",Tch);
                        }
                }
        }

}
//============================================================================================

void CIRCLE(int Crow,int Ccol,int Cradius,char Cch)
{
        int y;
        for(int x=0;x<Cradius;x++)
        {
                y=sqrt(pow(Cradius,2)-pow(x,2));
                for(int i=-y;i<y;i++)
                {
                        mvprintw(Crow+i,Ccol+x,"%c",Cch);
                        mvprintw(Crow+i,Ccol-x,"%c",Cch);
                }
        }
}
//============================================================================================

void enter()
{	int ch;
	keypad(stdscr,TRUE);
	ch=getch();
	while(ch != 10)
	{
	move(0,0);
	ch=getch();
	}
}
//============================================================================================

int integer(char arr[])
{	int tot=0,val;
	int j=strlen(arr)-1;
	for(int i=strlen(arr)-1;i>=0;i--)
	{
		if(arr[i]==49)val=1;
		else if(arr[i]==50)val=2;
		else if(arr[i]==51)val=3;
		else if(arr[i]==52)val=4;
		else if(arr[i]==53)val=5;
		else if(arr[i]==54)val=6;
		else if(arr[i]==55)val=7;
		else if(arr[i]==56)val=8;
		else if(arr[i]==57)val=9;
		else if(arr[i]==48)val=0;
		else {continue;}

		tot=tot+val*pow(10,strlen(arr)-1-j);
		j--;
	}
	return tot;
}
//============================================================================================

int tritype(char arr[])
{
	switch(arr[0])
	{
	case 'A':return 2;	case 'a':return 2;
	case 'B':return 5;	case 'b':return 5;
	case 'C':return 7;	case 'c':return 7;
	case 'D':return 1;	case 'd':return 1;
	case 'E':return 3;	case 'e':return 3;
	case 'F':return 6;	case 'f':return 6;
	case 'G':return 8;	case 'g':return 8;
	case 'H':return 4;      case 'h':return 4;
	default: return 0;
	}
}

//============================================================================================
//////////////////////////////////////////////////////////////////////////////////////////////
circle:: circle()
{
CfontColor=7;
CbackColor=0;
colNo=1;
}
void circle::setColor(int CpfontColor,int CpbackColor,int pcolNo)
{       CfontColor=CpfontColor;         CbackColor=CpbackColor;        colNo=pcolNo; }

void circle::Circle(int Cprow,int Cpcol,int Cpradius,char Cpch)
{
        Crow=Cprow;     Cradius=Cpradius;       Cch=Cpch;
        Ccol=Cpcol;
}
void circle::Print()
{       init_pair(colNo,CfontColor,CbackColor);
        attrset(COLOR_PAIR(colNo));
        int y;
        for(int x=0;x<Cradius;x++)
        {
                y=sqrt(pow(Cradius,2)-pow(x,2));
                for(int i=-y;i<y;i++)
                {
                        mvprintw(Crow+i,Ccol+x,"%c",Cch);
                        mvprintw(Crow+i,Ccol-x,"%c",Cch);
                }
        }
}

//============================================================================================
rectangle::rectangle()
{colNo=1;
}
void rectangle::Rectangle(int Rprow,int Rpcol,int Rpheight,int Rpwidth,char Rpch)
{
        Rrow=Rprow;     Rheight=Rpheight;       Rch=Rpch;       RbackColor=0;
        Rcol=Rpcol;     Rwidth=Rpwidth;         RfontColor=7;
}

void rectangle::setColor(int RpfontColor,int RpbackColor,int pcolNo)
{       RfontColor=RpfontColor;         RbackColor=RpbackColor;      colNo=pcolNo;   }

void rectangle::Print()
{       init_pair(colNo,RfontColor,RbackColor);
        attrset(COLOR_PAIR(colNo));
        for(int Ri=0;Ri<Rwidth;Ri++)
        {       for(int Rj=0;Rj<Rheight;Rj++)
                        mvprintw(Rrow+Ri,Rcol+Rj,"%c",Rch);
        }
}

//============================================================================================
triangle::triangle()
{colNo=1;
}
void triangle::setColor(int TpfontColor,int TpbackColor,int pcolNo)
{       TfontColor=TpfontColor;         TbackColor=TpbackColor;    colNo=pcolNo;     }

void triangle::Triangle(int Tprow,int Tpcol,int Tpheight,int Tptype,char Tpch)
{
        Trow=Tprow;     Theight=Tpheight;       Tch=Tpch;       TbackColor=0;
        Tcol=Tpcol;     TfontColor=7;           Ttype=Tptype;
}
void triangle::Print()
{       init_pair(colNo,TfontColor,TbackColor);
        attrset(COLOR_PAIR(colNo));

                int TT1,TT2,II1,II2;
        for(int Ti=0;Ti<Theight;Ti++)
        {
                for(int Tj=Theight;Tj>Ti;Tj--)
                {
                        if(Ttype==1 || Ttype==5 || Ttype==6) { TT1=TT2=Tj; II1=II2=Ti; }
                        if(Ttype==3 || Ttype==7 || Ttype==8) { TT1=TT2=-Tj; II1=II2=Ti; }
                        if(Ttype==2) { TT1=-Ti; TT2=Ti; II1=Tj; II2=-Tj; }
                        if(Ttype==4) { TT1=-Ti; TT2=Ti; II1=-Tj; II2=Tj; }

                        if(Ttype==1 || Ttype==5 || Ttype==3 || Ttype==7 || Ttype==2 || Ttype==4)
                        {
                                mvprintw(Trow+TT1,Tcol-II1,"%c",Tch);
                        }
                        if(Ttype==1 || Ttype==6 || Ttype==3 || Ttype==8 || Ttype==2 || Ttype==4)
                        {
                                mvprintw(Trow+TT2,Tcol+II2,"%c",Tch);
                        }
                }
        }
}
//////////////////////////////////////////////////////////////////////////////////////////////
