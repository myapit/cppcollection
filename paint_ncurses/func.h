

class circle
{
        private:
                int Crow,Ccol,Cradius,colNo,CfontColor,CbackColor;
                char Cch;
        public:
                circle();
                void Circle(int Cprow,int Cpcol,int Cpradius,char Cpch);
                void Print();
                void setColor(int CpfontColor,int CpbackColor,int pcolNo);
};

//============================================================================================
class rectangle
 {
        private:
                int Rrow,Rcol,Rheight,Rwidth,RfontColor,RbackColor,colNo;
                char Rch;
         public:
                rectangle();
                void Rectangle(int Rprow,int Rpcol,int Rpheight,int Rpwidth,char Rpch);
                void Print();
                void setColor(int RpfontColor,int RpbackColor,int pcolNo);
};

//============================================================================================
class triangle
{
        private:
                int Trow,Tcol,Theight,TfontColor,TbackColor,Ttype,colNo;
                char Tch;
        public:
                triangle();
                void Triangle(int Tprow,int Tpcol,int Tpheight,int Tptype,char Tpch);
                void Print();
                void setColor(int RpfontColor,int RpbackColor,int pcolNO);
};
//============================================================================================
//////////////////////////////////////////////////////////////////////////////////////////////

void stratAnime();
void fadeprint(int FProw, int FPcol,char text[],int delay);
void getcordinates(int &Zrow,int &Zcol);
void RECTANGLE(int Rrow,int Rcol,int Rheight,int Rwidth,char Rch);
void TRIANGLE(int Trow,int Tcol,int Theight,int Ttype,char Tch);
void CIRCLE(int Crow,int Ccol,int Cradius,char Cch);
void enter();
int integer(char arr[]);
int tritype(char arr[]);


