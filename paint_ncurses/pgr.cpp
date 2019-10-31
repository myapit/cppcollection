#include<ncurses.h>
#include"func.h"
#include"letters.h"
#include<cmath>

void firstpreview(int Rowmax,int Colmax,int delay);
void previewrectangle(int Rowmax,int Colmax);
void previewtriangle(int Rowmax,int Colmax);
void previewcircle(int Rowmax,int Colmax);
void allprint(circle *CIR,rectangle *REC,triangle *TRI,int cirCount,int recCount,int triCount);
void colorset(int &forecolor,int &backcolor);


int main()
{
	initscr();
	start_color();
	attron(A_BOLD);
	init_pair(1,7,0);//font white, background black
	init_pair(2,1,1);//red,red
	init_pair(3,3,0);//yellow,black
	init_pair(4,0,0);//black,black
	init_pair(5,2,0);//green,black
	init_pair(6,7,7);//white,white
	init_pair(7,0,7);//green,white

//..Starting_Animation........................................................................
	attrset(COLOR_PAIR(3));
	stratAnime();
	attrset(COLOR_PAIR(2));
	showord("paint1",60000000);
	attrset(COLOR_PAIR(4));
	showord("paint1",10000000);
	attrset(COLOR_PAIR(2));
	showord("ncurses",60000000);
	enter();	clear();

//..Common_declarations.......................................................................
	attrset(COLOR_PAIR(5));
	int Rowmax,Colmax,row,col,height,width,type,NcrsDelay=60000000;
	char shape[10],ch;
        getmaxyx(stdscr,Rowmax,Colmax);
	int triCount=0,recCount=0,cirCount=0,forecolor,backcolor,pairCount=30;
	circle *cir=new circle[100];
	rectangle *rec=new rectangle[100];
	triangle *tri=new triangle[100];

//starting_while..............................................................................
	while(shape[0]!='Q'||shape[0]!='q')
	{
	attrset(COLOR_PAIR(5));
	clear();
	attron(A_BOLD);
	fadeprint(2,(Colmax/2)-10,"PAINT NCURSES",NcrsDelay);
	firstpreview(Rowmax,Colmax,NcrsDelay);NcrsDelay=0;
	attron(A_NORMAL);
	mvprintw(Rowmax-1,(Colmax-58)/2,"enter a/b/c     p:print drawing     n:new drawing    q:quit");
	attron(A_BOLD);
	fadeprint(24,(Colmax/8)*3,"Enter the Shape you want...",10000000);
	move(25,(Colmax/8)*3);		getstr(shape);

	if(shape[0]=='A'||shape[0]=='a')//rectangle..................................................
	{
		do{
			attron(A_BOLD);	
			clear();
			fadeprint(2,(Colmax/2)-10,"PAINT NCURSES",0);
			previewrectangle(Rowmax,Colmax);
			attron(A_NORMAL);
			mvprintw(Rowmax-1,(Colmax-32)/2,"y:yes       n:no      q:main menu");
			attron(A_BOLD);
			fadeprint(20,(Colmax/8)*3,"Enter the Height of the Rectangle...",10000000);
			move(21,(Colmax/8)*3);	getstr(shape);
			if(shape[0]=='Q'||shape[0]=='q')continue;
			height=integer(shape);
			if(height>Rowmax-2 || height<0)continue;
			fadeprint(22,(Colmax/8)*3,"Enter the Width of the Rectangle...",10000000);
			move(23,(Colmax/8)*3);	getstr(shape);
			if(shape[0]=='Q'||shape[0]=='q')continue;
			width=integer(shape);
			if(width>Colmax-2 || width<0)continue;
			fadeprint(24,(Colmax/8)*3,"Enter the Character you want to fill...",10000000);
                	move(25,(Colmax/8)*3);  getstr(shape);	ch=shape[0];
			fadeprint(26,(Colmax/8)*3,"Press Enter to choose the cordinates...",10000000);
			enter();	clear();
			allprint(cir,rec,tri,cirCount,recCount,triCount);
			getcordinates(row,col);
			rec[recCount].Rectangle(row,col,width,height,ch);recCount++;
			allprint(cir,rec,tri,cirCount,recCount,triCount);

			enter();//set_color_to_shape
			colorset(forecolor,backcolor);
			rec[recCount-1].setColor(forecolor,backcolor,pairCount);pairCount++;
			clear();
			allprint(cir,rec,tri,cirCount,recCount,triCount);

			enter();	clear();	attrset(COLOR_PAIR(5));
                        attron(A_BOLD);
			fadeprint(2,(Colmax/2)-10,"PAINT NCURSES",0);
			previewrectangle(Rowmax,Colmax);
			attron(A_NORMAL);
                        mvprintw(Rowmax-1,(Colmax-32)/2,"y:yes       n:no      q:main menu");
                        attron(A_BOLD);
			fadeprint(20,(Colmax/8)*3,"Do You want to save current rectangle...",10000000);
			move(21,(Colmax/8)*3);  getstr(shape);
			if(shape[0]=='Q'||shape[0]=='q')continue;
			if(shape[0]!='Y'&& shape[0]!='y')recCount--;
			fadeprint(22,(Colmax/8)*3,"Do you want an another rectangle...",10000000);
			move(23,(Colmax/8)*3);  getstr(shape);
			if(shape[0]=='Q'||shape[0]=='q')continue;
			if(shape[0]!='Y' && shape[0]!='y')break;

		}while(shape[0]=='Y'|| shape[0]=='y');
		continue;	
	}

	else if(shape[0]=='B'|| shape[0]=='b')//triangle.............................................
	{
		do{
			attron(A_BOLD);
			clear();
			fadeprint(2,(Colmax/2)-10,"PAINT NCURSES",0);
			previewtriangle(Rowmax,Colmax);
			attrset(COLOR_PAIR(5));
			attron(A_NORMAL);
                        mvprintw(Rowmax-1,(Colmax-32)/2,"y:yes       n:no      q:main menu");
                        attron(A_BOLD);
			fadeprint(24,(Colmax/8)*3,"Enter the type of the triangle...",10000000);
			move(25,(Colmax/8)*3);  getstr(shape);
			if(shape[0]=='Q'||shape[0]=='q')continue;
			type=tritype(shape);
			fadeprint(26,(Colmax/8)*3,"Enter the height of the triangle...",10000000);
			move(27,(Colmax/8)*3);  getstr(shape);
			if(shape[0]=='Q'||shape[0]=='q')continue;
			height=integer(shape);
			fadeprint(28,(Colmax/8)*3,"Enter the Character you want to fill...",10000000);
                        move(29,(Colmax/8)*3);  getstr(shape);  ch=shape[0];
                        fadeprint(30,(Colmax/8)*3,"Press Enter to choose the cordinates...",10000000);
                        enter();        clear();
			allprint(cir,rec,tri,cirCount,recCount,triCount);
                        getcordinates(row,col);
                        tri[triCount].Triangle(row,col,height,type,ch);triCount++;
                        allprint(cir,rec,tri,cirCount,recCount,triCount);

			enter();//set_color_to_shape
                        colorset(forecolor,backcolor);
                        tri[triCount-1].setColor(forecolor,backcolor,pairCount);pairCount++;
                        clear();
                        allprint(cir,rec,tri,cirCount,recCount,triCount);

                        enter();        clear();	attrset(COLOR_PAIR(5));
			attron(A_BOLD);
                        previewtriangle(Rowmax,Colmax);
			attrset(COLOR_PAIR(5));
			attron(A_NORMAL);
                        mvprintw(Rowmax-1,(Colmax-32)/2,"y:yes       n:no      q:main menu");
                        attron(A_BOLD);
			fadeprint(2,(Colmax/2)-10,"PAINT NCURSES",0);
                        fadeprint(24,(Colmax/8)*3,"Do You want to save current triangle...",10000000);
                        move(25,(Colmax/8)*3);  getstr(shape);
			if(shape[0]=='Q'||shape[0]=='q')continue;
                        if(shape[0]!='Y'&& shape[0]!='y')triCount--;
                        fadeprint(26,(Colmax/8)*3,"Do you want an another triangle...",10000000);
                        move(27,(Colmax/8)*3);  getstr(shape);
			if(shape[0]=='Q'||shape[0]=='q')continue;
                        if(shape[0]!='Y' && shape[0]!='y')break;

		}while(shape[0]=='Y'|| shape[0]=='y');
		continue;
	}
	
	else if(shape[0]=='C'|| shape[0]=='c')//circle...............................................
	{
		do{
			attron(A_BOLD);
			clear();
			fadeprint(2,(Colmax/2)-10,"PAINT NCURSES",0);
			previewcircle(Rowmax,Colmax);
			attrset(COLOR_PAIR(5));
			attron(A_NORMAL);
                        mvprintw(Rowmax-1,(Colmax-32)/2,"y:yes       n:no      q:main menu");
                        attron(A_BOLD);
			fadeprint(24,(Colmax/8)*3,"Enter the radius of the circle...",10000000);
                        move(25,(Colmax/8)*3);  getstr(shape);
			if(shape[0]=='Q'||shape[0]=='q')continue;
			height=integer(shape);
			fadeprint(26,(Colmax/8)*3,"Enter the Character you want to fill...",10000000);
                        move(27,(Colmax/8)*3);  getstr(shape);  ch=shape[0];
			fadeprint(28,(Colmax/8)*3,"Press Enter to choose the cordinates...",10000000);
                        enter();        clear();
                        allprint(cir,rec,tri,cirCount,recCount,triCount);
                        getcordinates(row,col);
                        cir[cirCount].Circle(row,col,height,ch);cirCount++;
                        allprint(cir,rec,tri,cirCount,recCount,triCount);

			enter();//set_color_to_shape
                        colorset(forecolor,backcolor);
                        cir[cirCount-1].setColor(forecolor,backcolor,pairCount);pairCount++;
                        clear();
                        allprint(cir,rec,tri,cirCount,recCount,triCount);

                        enter();        clear();	attrset(COLOR_PAIR(5));
			attron(A_BOLD);
                        fadeprint(2,(Colmax/2)-10,"PAINT NCURSES",0);
                        previewcircle(Rowmax,Colmax);
                        attrset(COLOR_PAIR(5));
			attron(A_NORMAL);
                        mvprintw(Rowmax-1,(Colmax-32)/2,"y:yes       n:no      q:main menu");
                        attron(A_BOLD);
                        fadeprint(24,(Colmax/8)*3,"Do You want to save current circle...",10000000);
                        move(25,(Colmax/8)*3);  getstr(shape);
			if(shape[0]=='Q'||shape[0]=='q')continue;
                        if(shape[0]!='Y'&& shape[0]!='y')cirCount--;
                        fadeprint(26,(Colmax/8)*3,"Do you want an another circle...",10000000);
                        move(27,(Colmax/8)*3);  getstr(shape);
			if(shape[0]=='Q'||shape[0]=='q')continue;
                        if(shape[0]!='Y' && shape[0]!='y')break;

		}while(shape[0]=='Y'|| shape[0]=='y');
	}
	
	else if(shape[0]=='P'|| shape[0]=='p')
	{
		clear();
		allprint(cir,rec,tri,cirCount,recCount,triCount);
		enter();
		continue;
	}

	else if(shape[0]=='Q'|| shape[0]=='q')
	{	
		clear();
		attron(A_BOLD);
		fadeprint(Rowmax/2,(Colmax-21)/2,"Programe shutting down",10000000);
		fadeprint(Rowmax/2+1,(Colmax-21)/2+8,"....",60000000);
		break;
	}
	
	else if(shape[0]=='N'|| shape[0]=='n')
	{
		clear();
		attron(A_BOLD);
                fadeprint(Rowmax/2,(Colmax-48)/2,"Are you sure you want to create a new drawing...",10000000);
		move(Rowmax/2+1,(Colmax-48)/2);
		getstr(shape);
		if(shape[0]=='Y'|| shape[0]=='y')
		{recCount=0;triCount=0;cirCount=0,NcrsDelay=60000000;}
		continue;
	}	

	else 
	{
		clear();
		attron(A_BOLD);
		mvprintw(1,(Colmax-18)/2,"emadhura@gmail.com");
		fadeprint(Rowmax/2,(Colmax-36)/2,"You have entered an invalid choise...",10000000);
		for(int h=0;h<60000000;h++);
		continue;
	}

	}
//close_while.................................................................................

	endwin();
	delete []cir;
	delete []rec;
	delete []tri;
	
	return 0;
}




void firstpreview(int Rowmax,int Colmax,int delay)
{	move(0,0);
	if(delay>1000000)
	for(int i=0;i<60000000;i++);
        TRIANGLE(6,(Colmax-68)/2+35,12,1,'*');
        mvprintw(20,(Colmax-68)/2+35,"B");
	refresh();
	for(int i=0;i<delay;i++);
	RECTANGLE(7,(Colmax-68)/2,10,12,'*');
	mvprintw(20,(Colmax-68)/2+5,"A");

	CIRCLE(13,(Colmax-68)/2+65,6,'*');
	mvprintw(20,(Colmax-68)/2+65,"C");
	refresh();
}

void previewrectangle(int Rowmax,int Colmax)
{
	RECTANGLE(6,(Colmax/2)-12,16,10,'*');
	attrset(COLOR_PAIR(3));
	mvprintw(6,(Colmax/2)-12,"*");
	mvprintw(5,(Colmax/2)-18,"(start)");
	for(int i=0;i<16;i++)
	{	mvprintw(16,(Colmax/2)-12+i,"_");}
	mvprintw(17,(Colmax/2)-4,"width");
	for(int i=0;i<10;i++)
	{	mvprintw(6+i,(Colmax/2)+5,"|");}
	mvprintw(11,(Colmax/2)+6,"height");

	attrset(COLOR_PAIR(5));
}

void allprint(circle CIR[],rectangle REC[],triangle TRI[],int cirCount,int recCount,int triCount)
{
	for(int i=0;i<cirCount;i++)
	{
		CIR[i].Print();
	}
	for(int i=0;i<recCount;i++)
	{
		REC[i].Print();
	}
	for(int i=0;i<triCount;i++)
	{
		TRI[i].Print();
	}
}

void previewtriangle(int Rowmax,int Colmax)
{       Colmax=(Colmax-68)/2;
        TRIANGLE(14,(Colmax),8,2,'*');
        TRIANGLE(6,(Colmax)+14,7,5,'*');
        TRIANGLE(22,(Colmax)+14,7,7,'*');
        TRIANGLE(6,(Colmax)+30,7,1,'*');
        TRIANGLE(22,(Colmax)+30,7,3,'*');
        TRIANGLE(6,(Colmax)+46,7,6,'*');
        TRIANGLE(22,(Colmax)+46,7,8,'*');
        TRIANGLE(14,(Colmax)+60,8,4,'*');

        attrset(COLOR_PAIR(3));
        mvprintw(14,Colmax-5,"A");
        mvprintw(11,Colmax+14-2,"B");
        mvprintw(17,Colmax+14-2,"C");
        mvprintw(11,Colmax+30,"D");
        mvprintw(17,Colmax+30,"E");
        mvprintw(11,Colmax+46+2,"F");
        mvprintw(17,Colmax+46+2,"G");
        mvprintw(14,Colmax+60+5,"H");

}

void previewcircle(int Rowmax,int Colmax)
{
	CIRCLE(14,(Colmax/2)-4,8,'*');
	attrset(COLOR_PAIR(3));
        mvprintw(14,Colmax/2-4,"*");
        mvprintw(14,Colmax/2-20,"starting");

}

void colorset(int &forecolor,int &backcolor)
{
	int row,col,count=0;
	char shape[24];
	init_pair(20,7,0);//black
        init_pair(21,7,1);//red
        init_pair(22,7,2);//green
        init_pair(23,7,3);//yellow
        init_pair(24,7,4);//blue
	init_pair(25,7,5);//magenta
        init_pair(26,7,6);//cyan
        init_pair(27,7,7);//white
	getmaxyx(stdscr,row,col);
	row=row/2-5;col=col/2-11;
	attrset(COLOR_PAIR(4));
	for(int i=0;i<16;i++)
	{	for(int k=0;k<20000000;k++);
		attrset(COLOR_PAIR(6));
		for(int j=0;j<28;j++)
		{
			mvprintw(row+i,col+j," ");
		}
		refresh();
		
		if((i+1)%2==0 && count<8)
		{attron(A_BOLD);
		attrset(COLOR_PAIR(20+count));
		mvprintw(row+i,col+2,"   ");
		attrset(COLOR_PAIR(7));
		mvprintw(row+i,col+6," = ");	mvprintw(row+i,col+8,"%i",count);

		attrset(COLOR_PAIR(20+count+1));
		mvprintw(row+i,col+16,"   ");
		attrset(COLOR_PAIR(7));
		mvprintw(row+i,col+20," = ");	mvprintw(row+i,col+22,"%i",count+1);
		count=count+2;
		}

	}
	attrset(COLOR_PAIR(7));		attron(A_BOLD);
	fadeprint(row+10,col+1,"Enter character color...",10000000);move(row+11,col+1);
	getstr(shape);	forecolor=integer(shape);
	fadeprint(row+12,col+1,"Enter background color...",10000000);move(row+13,col+1);
	getstr(shape);  backcolor=integer(shape);
	fadeprint(row+14,col+12,"...",40000000);
	attrset(COLOR_PAIR(7));
}
