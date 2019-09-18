/***************************************
 * PROJECT BANK MANAGEMENT SYSTEM      *
 * PROGRAMMER JOSHUA REMINISCE         *
 * IDE DEV-C++ 4.9.9.2                 *
 * COMPILER MIN-GW                     *
 * DATE STARTED 03RD/10/2015           *
 * DATE ENDED 06TH/10/2015             *
 * INSTITUTION ST. LAWRENCE UNIVERSITY *
 * EMAIL joshuapark61@gmail.com        *
 * TEL NO. +256-757-446236             * 
 ***************************************/
//==============================================================================
//                           LIBRARIES OR HEADERZ
//==============================================================================
 #include<iostream>
 #include<conio.h>
 #include<fstream>
 #include<math.h>
 #include<string.h>
 #include<stdio.h>
 #include<windows.h>
 #include<iomanip>
 
 using namespace std;
//==============================================================================
//                       FUNCTION FOR THE AXIS (GOTOXY)
//==============================================================================
 void gotoxy(int x, int y){
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
//==============================================================================
//                      FUNCTIONZ TO CLEAR CONSOLE WINDOWZ
//==============================================================================
void clearWindow(){
     int i,j;
     for(i=15; i<65; i++){
           for(j=0; j<25; j++){
                 gotoxy(i,j); printf(" ");
        }
    }
    return;
}
void clearWindowz(){
     int i,j;
     for(i=1; i<80; i++){
           for(j=0; j<25; j++){
                 gotoxy(i,j); printf(" ");
        }
    }
    return;
}
//==============================================================================
//                               MAIN CLASS
//==============================================================================
  class Bank {
        
        public:
               char fname[12], lname[12], nationality[30], accType;
               int openAmt, accNo;
        private:
                int i;
        public:
        // ADMIN FUNCTIONZ
        char openAcc(){
             clearWindow();
             int i;
             srand(time(NULL));
             accNo = rand() % 100 + 10;
             gotoxy(15,3); printf("\xC9"); // Left upper corner 
             for(i=1;i<=48;i++) printf("\xCD"); // Upper horizontal line 
             gotoxy(64,3); printf("\xBB"); // Right upper corner
             gotoxy(15,24); printf("\xC8"); // Lower left corner
             for(i=1;i<=48;i++) printf("\xCD"); // Lower horizontal line 
             gotoxy(64,24); printf("\xBC"); // Lower right corner
             for(i=1;i<21;i++){ gotoxy(15,i+3); printf("\xBA");}// Left vertical
             for(i=1;i<21;i++){ gotoxy(64,i+3); printf("\xBA");}// Right vertical
             
             //=================================================================
             gotoxy(8+19,0); printf("\xC9"); // Upper left corner
             for(i=1;i<=25;i++) printf("\xCD"); // Upper horizontal line 
             gotoxy(52,0); printf("\xBB"); // Upper right corner
             gotoxy(8+19,2); printf("\xC8"); // Lower left corner
             for(i=1;i<=25;i++) printf("\xCD"); // Lower horizontal line 
             gotoxy(52,2); printf("\xBC"); // Lower right corner
             for(i=1;i<2;i++){ gotoxy(27,i+0); printf("\xBA");}// Left vertical
             for(i=1;i<2;i++){ gotoxy(52,i+0); printf("\xBA");}// Right vertical
             
             //=================================================================
             // SMALL BOX
             //=================================================================
             gotoxy(17,4); printf("%c",218); // Left Upper Corner
             gotoxy(62,4); printf("%c",191); // Right Upper Corner 
             gotoxy(17,23); printf("%c",192); // Left Lower Corner
             gotoxy(62,23); printf("%c",217); // Right Lower Corner
             for(i=1;i<=44;i++) { gotoxy(17+i,4); printf("%c",196);}// Upper Horizontal
             for(i=1;i<=44;i++) { gotoxy(17+i,23); printf("%c",196);}// Lower Horizontal
             for(i=1;i<=44;i++) { gotoxy(17+i,19); printf("%c",196);}// Middle horizontal
             for(i=1;i<=18;i++) { gotoxy(17,4+i); printf("%c",179);}// Left Vertical
             for(i=1;i<=18;i++) { gotoxy(62,4+i); printf("%c",179);}// Right VerticaL
             gotoxy(31,1); std::cout<<" OUTLAWZ BANK INC.";
             gotoxy(19,4); std::cout<<" ADD RECORD ";
             gotoxy(18,7); std::cout<<" FIRST NAME : ";
             gotoxy(18,9); std::cout<<" OTHER NAME : ";
             gotoxy(18,11); std::cout<<" NATIONALITY : ";
             gotoxy(18,13); std::cout<<" ACCOUNT TYPE [C/S] : ";
             gotoxy(18,15); std::cout<<" OPENING AMOUNT [C=1000 /S=500] : ";
             gotoxy(18,17); std::cout<<" ACCOUNT NUMBER : ";
             gotoxy(36,19); std::cout<<" NOTE ";
             gotoxy(25,21); std::cout<<" USE UNDERSCORE FOR SPACES... ";
             gotoxy(32,7); std::cin>>fname;
             gotoxy(32,9); std::cin>>lname;
             gotoxy(33,11); std::cin>>nationality;
             gotoxy(40,13); std::cin>>accType;
             accType=toupper(accType);
             gotoxy(52,15); std::cin>>openAmt;
             gotoxy(36,17); std::cout<<accNo;
             gotoxy(25,21); std::cout<<" ACCOUNT OPENED SUCCESSFULLY!";
             getch();
        }
        
        void viewAcc1(){
             gotoxy(18,9); std::cout<<" FIRST NAME : ";
             gotoxy(18,11); std::cout<<" OTHER NAME : ";
             gotoxy(18,13); std::cout<<" NATIONALITY : ";
             gotoxy(18,15); std::cout<<" ACCOUNT TYPE [C/S] : ";
             gotoxy(18,17); std::cout<<" OPENING AMOUNT [C=1000 /S=500] : ";
             //=================================================================
             // SMALL ACCOUNT NUMBER BOX
             //=================================================================
             gotoxy(31,5); printf("%c",218); // Left Upper Corner
             gotoxy(48,5); printf("%c",191); // Right Upper Corner 
             gotoxy(31,7); printf("%c",192); // Left Lower Corner
             gotoxy(48,7); printf("%c",217); // Right Lower Corner
             for(i=1;i<=16;i++) { gotoxy(31+i,5); printf("%c",196);}// Upper Horizontal
             for(i=1;i<=16;i++) { gotoxy(31+i,7); printf("%c",196);}// Lower Horizontal
             for(i=1;i<=1;i++) { gotoxy(30+i,6); printf("%c",179);}// Left Vertical
             for(i=1;i<=1;i++) { gotoxy(48,5+i); printf("%c",179);}// Right Vertical
             gotoxy(32,9); std::cout<<fname;
             gotoxy(32,11); std::cout<<lname;
             gotoxy(33,13); std::cout<<nationality;
             gotoxy(40,15); std::cout<<accType;
             gotoxy(52,17); std::cout<<openAmt;
             gotoxy(33,19); std::cout<<" NOTIFICATION ";
             gotoxy(32,6); std::cout<<" ACCOUNT NO: ";
             gotoxy(44,6); std::cout<<accNo;
        }
            
        void viewAllAcc(){
             int i, n;
             gotoxy(1,3); printf("\xC9"); // Upper left corner
             for(i=1;i<=76;i++) printf("\xCD"); // Upper left right horizontal  
             gotoxy(78,3); printf("\xBB"); // Upper right corner
             gotoxy(1,24); printf("\xC8"); // Lower left corner
             for(i=1;i<=76;i++) printf("\xCD"); // Lower left right horizontal 
             gotoxy(78,24); printf("\xBC"); // Lower right corner
             for(i=1;i<21;i++){ gotoxy(1,i+3); printf("\xBA");}// Left vertical
             for(i=1;i<21;i++){ gotoxy(78,i+3); printf("\xBA");}// Right vertical
             
             //=================================================================
             gotoxy(8+19,0); printf("\xC9"); // Upper left corner
             for(i=1;i<=25;i++) printf("\xCD"); // Upper left right horizontal 
             gotoxy(52,0); printf("\xBB"); // Upper right corner
             gotoxy(8+19,2); printf("\xC8"); // Lower left corner
             for(i=1;i<=25;i++) printf("\xCD"); // Lower left right horizontal  
             gotoxy(52,2); printf("\xBC"); // Lower right corner
             for(i=1;i<2;i++){ gotoxy(27,i+0); printf("\xBA");}// Left vertical 
             for(i=1;i<2;i++){ gotoxy(52,i+0); printf("\xBA");}// Right vertical
             
             //=================================================================
             // SMALL BOX
             //=================================================================
            gotoxy(3,4); printf("%c",218); // Left Upper Corner
            gotoxy(76,4); printf("%c",191); // Right Upper Corner 
            gotoxy(3,23); printf("%c",192); // Left Lower Corner
            gotoxy(76,23); printf("%c",217); // Right Lower Corner
            for(i=1;i<=72;i++) { gotoxy(3+i,4); printf("%c",196);}// Upper Horizontal
            for(i=1;i<=72;i++) { gotoxy(3+i,23); printf("%c",196);}// Lower Horizontal
            for(i=1;i<=72;i++) { gotoxy(3+i,20); printf("%c",196);}// Middle horizontal
            for(i=1;i<=18;i++) { gotoxy(3,4+i); printf("%c",179);}// Left Vertical
            for(i=1;i<=18;i++) { gotoxy(76,4+i); printf("%c",179);}// Right Vertical
            gotoxy(31,1); std::cout<<" OUTLAWZ BANK INC.";
            gotoxy(5,4); std::cout<<" VIEW ALL ACCOUNTS ";
            gotoxy(32,20); std::cout<<" NOTIFICATION ";
            for(i=1;i<=70;i++) { gotoxy(4+i,7); printf("%c",196); }
            gotoxy(4,6); std::cout<<" ACC_NO ";
            gotoxy(13,6); std::cout<<" FIRST_NAME ";
            gotoxy(26,6); std::cout<<" LAST_NAME ";
            gotoxy(38,6); std::cout<<" NATIONALITY ";
            gotoxy(52,6); std::cout<<" ACC_TYPE ";
            gotoxy(63,6); std::cout<<" ACC_BALANCE ";
            gotoxy(20,22); std::cout<<" PRESS ENTER TO GO BACK TO MAIN MENU... ";
            }
            
        void delviewAcc(){
             gotoxy(18,7); std::cout<<" FIRST NAME : ";
             gotoxy(18,9); std::cout<<" OTHER NAME : ";
             gotoxy(18,11); std::cout<<" NATIONALITY : ";
             gotoxy(18,13); std::cout<<" ACCOUNT TYPE [C/S] : ";
             gotoxy(18,15); std::cout<<" OPENING AMOUNT [C=1000 /S=500] : ";
             gotoxy(32,7); std::cout<<fname;
             gotoxy(32,9); std::cout<<lname;
             gotoxy(33,11); std::cout<<nationality;
             gotoxy(40,13); std::cout<<accType;
             gotoxy(52,15); std::cout<<openAmt;
             gotoxy(33,19); std::cout<<" NOTIFICATION ";
             gotoxy(19,21); std::cout<<" DELETE THIS RECORD? [Y/N] : ";
        }
            
        void adminMenuGraphicz(){
             gotoxy(16,5); printf("\xC9"); // Upper left corner
             for(i=1;i<=47;i++) printf("\xCD"); // Upper left right horizontal 
             gotoxy(64,5); printf("\xBB"); // Upper right corner
             gotoxy(16,23); printf("\xC8"); // Lower left corner
             for(i=1;i<=47;i++) printf("\xCD"); // Lower left right horizontal 
             gotoxy(64,23); printf("\xBC"); // Lower right corner
             for(i=1;i<18;i++){ gotoxy(16,i+5); printf("\xBA");}// Left vertical
             for(i=1;i<18;i++){ gotoxy(64,i+5); printf("\xBA");}// Right vertical
             gotoxy(16,19); printf("\xCC"); // Left inside lower corner
             for(i=1;i<=47;i++) printf("\xCD"); // Inside lower left right horizontal 
             gotoxy(64,19); printf("\xB9"); // Right inside lower corner
             
             //=================================================================
             gotoxy(8+19,2); printf("\xC9"); // Upper left corner
             for(i=1;i<=25;i++) printf("\xCD"); // Upper left right horizontal 
             gotoxy(52,2); printf("\xBB"); // Upper right corner
             gotoxy(8+19,4); printf("\xC8"); // Lower left corner
             for(i=1;i<=25;i++) printf("\xCD"); // Lower left to right horizontal 
             gotoxy(52,4); printf("\xBC"); // Lower right corner
             for(i=1;i<2;i++){ gotoxy(27,i+2); printf("\xBA");} // Left vertical
             for(i=1;i<2;i++){ gotoxy(52,i+2); printf("\xBA");}// Right vertical
             
             //=================================================================
             gotoxy(45,7); printf("\xC9"); // Upper left corner
             for(i=1;i<=16;i++) printf("\xCD"); // Upper left right horizontal 
             gotoxy(62,7); printf("\xBB"); // Upper right corner
             gotoxy(45,17); printf("\xC8"); // Lower left corner
             for(i=1;i<=16;i++) printf("\xCD"); // Lower left right horizontal 
             gotoxy(62,17); printf("\xBC"); // Lower right corner
             for(i=1;i<10;i++){ gotoxy(45,i+7); printf("\xBA"); } // Left vertical
             for(i=1;i<10;i++){ gotoxy(62,i+7); printf("\xBA"); }// Right vertical
        }
             
        void deleteRecordGraphicz(){
             gotoxy(15,3); printf("\xC9"); // Upper left corner
             for(i=1;i<=48;i++) printf("\xCD"); // Upper left right horizontal 
             gotoxy(64,3); printf("\xBB"); // Upper right corner
             gotoxy(15,24); printf("\xC8"); // Lower left corner
             for(i=1;i<=48;i++) printf("\xCD"); // Lower left right horizontal 
             gotoxy(64,24); printf("\xBC"); // Lower right corner
             for(i=1;i<21;i++){ gotoxy(15,i+3); printf("\xBA"); } // Left vertical
             for(i=1;i<21;i++){ gotoxy(64,i+3); printf("\xBA"); }// Right vertical
             
             //=================================================================
             gotoxy(8+19,0); printf("\xC9"); // Upper left corner
             for(i=1;i<=25;i++) printf("\xCD"); // Upper left right horizontal 
             gotoxy(52,0); printf("\xBB"); // Upper right corner
             gotoxy(8+19,2); printf("\xC8"); // Lower left corner
             for(i=1;i<=25;i++) printf("\xCD"); // Lower left right horizontal 
             gotoxy(52,2); printf("\xBC"); // Lower right corner
             for(i=1;i<2;i++){ gotoxy(27,i+0); printf("\xBA"); } // Left vertical
             for(i=1;i<2;i++){ gotoxy(52,i+0); printf("\xBA"); }// Right vertical
             
             //=================================================================
             // SMALL BOX
             //=================================================================
             gotoxy(17,4); printf("%c",218); // Left Upper Corner
             gotoxy(62,4); printf("%c",191); // Right Upper Corner 
             gotoxy(17,23); printf("%c",192); // Left Lower Corner
             gotoxy(62,23); printf("%c",217); // Right Lower Corner
             for(i=1;i<=44;i++) { gotoxy(17+i,4); printf("%c",196); } // Upper Horizontal
             for(i=1;i<=44;i++) { gotoxy(17+i,23); printf("%c",196); } // Lower Horizontal
             for(i=1;i<=44;i++) { gotoxy(17+i,19); printf("%c",196); } // Middle horizontal
             for(i=1;i<=18;i++) { gotoxy(17,4+i); printf("%c",179); } // Left Vertical
             for(i=1;i<=18;i++) { gotoxy(62,4+i); printf("%c",179); } // Right Vertical
             
             //=================================================================
             // SMALL BOX
             //=================================================================
             gotoxy(17,4); printf("%c",218); // Left Upper Corner
             gotoxy(62,4); printf("%c",191); // Right Upper Corner 
             gotoxy(17,23); printf("%c",192); // Left Lower Corner
             gotoxy(62,23); printf("%c",217); // Right Lower Corner
             for(i=1;i<=44;i++) { gotoxy(17+i,4); printf("%c",196); } // Upper Horizontal
             for(i=1;i<=44;i++) { gotoxy(17+i,23); printf("%c",196); } // Lower Horizontal
             for(i=1;i<=44;i++) { gotoxy(17+i,19); printf("%c",196); } // Middle horizontal
             for(i=1;i<=18;i++) { gotoxy(17,4+i); printf("%c",179); } // Left Vertical
             for(i=1;i<=18;i++) { gotoxy(62,4+i); printf("%c",179); } // Right Vertical
        }
             
        void displayRecordGraphicz(){
             gotoxy(15,3); printf("\xC9"); // Upper left corner
             for(i=1;i<=48;i++) printf("\xCD"); // Upper left right horizontal
             gotoxy(64,3); printf("\xBB"); // Upper right corner
             gotoxy(15,24); printf("\xC8"); // Lower left corner
             for(i=1;i<=48;i++) printf("\xCD"); // Lower left right horizontal 
             gotoxy(64,24); printf("\xBC"); // Lower right corner
             for(i=1;i<21;i++){ gotoxy(15,i+3); printf("\xBA"); } // Left vertical
             for(i=1;i<21;i++){ gotoxy(64,i+3); printf("\xBA"); }// Right vertical
             
             //=================================================================
             gotoxy(8+19,0); printf("\xC9"); // Upper left corner
             for(i=1;i<=25;i++) printf("\xCD"); // Upper left right horizontal 
             gotoxy(52,0); printf("\xBB"); // Upper right corner
             gotoxy(8+19,2); printf("\xC8"); // Lower left corner
             for(i=1;i<=25;i++) printf("\xCD"); // Lower left right horizontal 
             gotoxy(52,2); printf("\xBC"); // Lower right corner
             for(i=1;i<2;i++){ gotoxy(27,i+0); printf("\xBA"); } // Left vertical
             for(i=1;i<2;i++){ gotoxy(52,i+0); printf("\xBA"); }// Right vertical
             
             //=================================================================
             // SMALL BOX
             //=================================================================
             gotoxy(17,4); printf("%c",218); // Left Upper Corner
             gotoxy(62,4); printf("%c",191); // Right Upper Corner 
             gotoxy(17,23); printf("%c",192); // Left Lower Corner
             gotoxy(62,23); printf("%c",217); // Right Lower Corner
             for(i=1;i<=44;i++) { gotoxy(17+i,4); printf("%c",196); } // Upper Horizontal
             for(i=1;i<=44;i++) { gotoxy(17+i,23); printf("%c",196); } // Lower Horizontal
             for(i=1;i<=44;i++) { gotoxy(17+i,19); printf("%c",196); } // Middle horizontal
             for(i=1;i<=18;i++) { gotoxy(17,4+i); printf("%c",179); } // Left Vertical
             for(i=1;i<=18;i++) { gotoxy(62,4+i); printf("%c",179); } // Right Vertical
             
             //=================================================================
             // SMALL BOX
             //=================================================================
             gotoxy(17,4); printf("%c",218); // Left Upper Corner
             gotoxy(62,4); printf("%c",191); // Right Upper Corner 
             gotoxy(17,23); printf("%c",192); // Left Lower Corner
             gotoxy(62,23); printf("%c",217); // Right Lower Corner
             for(i=1;i<=44;i++) { gotoxy(17+i,4); printf("%c",196); } // Upper Horizontal
             for(i=1;i<=44;i++) { gotoxy(17+i,23); printf("%c",196); } // Lower Horizontal
             for(i=1;i<=44;i++) { gotoxy(17+i,19); printf("%c",196); } // Middle horizontal
             for(i=1;i<=18;i++) { gotoxy(17,4+i); printf("%c",179); } // Left Vertical
             for(i=1;i<=18;i++) { gotoxy(62,4+i); printf("%c",179); } // Right Vertical
        }
             
        void adminLoginGraphicz(){
             gotoxy(20,3); printf("\xC9"); // Upper left corner
             for(i=1;i<=40;i++) printf("\xCD"); // Upper left right horizontal
             gotoxy(61,3); printf("\xBB"); // Upper right corner
             gotoxy(20,22); printf("\xC8"); // Lower left corner
             for(i=1;i<=40;i++) printf("\xCD"); // Lower left right horizontal 
             gotoxy(61,22); printf("\xBC"); // Lower right corner
             for(i=1;i<19;i++) { gotoxy(20,i+3); printf("\xBA"); } // Left vertical
             for(i=1;i<19;i++) { gotoxy(61,i+3); printf("\xBA"); } // Right vertical
             
             //=================================================================
             gotoxy(20,7); printf("\xCC"); // Left inside upper corner
             for(i=1;i<=40;i++) printf("\xCD"); // Inside upper left right horizontal 
             gotoxy(20,17); printf("\xCC"); // Left inside lower corner
             for(i=1;i<=40;i++) printf("\xCD"); // Inside lower left right horizontal
             gotoxy(61,7); printf("\xB9"); // Right inside upper corner
             gotoxy(61,17); printf("\xB9"); // Right inside lower corner
             
             //=================================================================
             gotoxy(28,10); printf("\xC9"); // Upper left corner
             for(i=1;i<=24;i++) printf("\xCD"); // Upper left right horizontal 
             gotoxy(52,10); printf("\xBB"); // Upper right corner
             gotoxy(28,14); printf("\xC8"); // Lower left corner 
             for(i=1;i<=24;i++) printf("\xCD"); // Lower left right horizontal
             gotoxy(52,14); printf("\xBC"); // Lower right corner
             for(i=1;i<4;i++){ gotoxy(28,i+10); printf("\xBA"); } // Left vertical
             for(i=1;i<4;i++){ gotoxy(52,i+10); printf("\xBA"); } // Right vertical
        }
             
        void progressBarGraphicz(){
             gotoxy(27,5); std::cout<<"OUTLAWZ BANK INCORPORATED";
             gotoxy(8,3); printf("\xC9"); // Upper left corner
             for(i=1;i<=61;i++) printf("\xCD"); // Upper left right horizontal 
             gotoxy(70,3); printf("\xBB"); // Upper right corner
             gotoxy(8,22); printf("\xC8"); // Lower left corner
             for(i=1;i<=61;i++) printf("\xCD");// Lower left right horizontal 
             gotoxy(70,22); printf("\xBC"); // Lower right corner
             for(i=1;i<19;i++){ gotoxy(8,i+3); printf("\xBA"); } // Left vertical
             for(i=1;i<19;i++){ gotoxy(70,i+3); printf("\xBA"); }// Right vertical
              
             //=================================================================
             gotoxy(8,7); printf("\xCC"); // Left inside upper corner
             for(i=1;i<=61;i++) printf("\xCD"); // Inside upper left right horizontal 
             gotoxy(8,17); printf("\xCC"); // Left inside lower corner
             for(i=1;i<=61;i++) printf("\xCD"); // Inside lower left right horizontal 
             gotoxy(70,7); printf("\xB9"); // Right inside upper corner
             gotoxy(70,17); printf("\xB9"); // Right inside lower corner
             gotoxy(35,17); std::cout<<" LOADING ";
        }
              
        void aboutProgrammerGraphicz(){
             gotoxy(20,3); printf("\xC9"); // Upper left corner
             for(i=1;i<=40;i++) printf("\xCD"); // Upper left right horizontal 
             gotoxy(61,3); printf("\xBB"); // Upper right corner
             gotoxy(20,22); printf("\xC8"); // Lower left corner
             for(i=1;i<=40;i++) printf("\xCD"); // Lower left right horizontal 
             gotoxy(61,22); printf("\xBC"); // Lower right corner
             for(i=1;i<19;i++) { gotoxy(20,i+3); printf("\xBA"); } // Left vertical
             for(i=1;i<19;i++) { gotoxy(61,i+3); printf("\xBA"); } // Right vertical
             
             //=================================================================
             gotoxy(20,7); printf("\xCC"); // Left inside upper corner
             for(i=1;i<=40;i++) printf("\xCD"); // Inside upper left right horizontal 
             gotoxy(20,17); printf("\xCC"); // Left inside lower corner
             for(i=1;i<=40;i++) printf("\xCD"); // Inside lower left right horizontal
             gotoxy(61,7); printf("\xB9"); // Right inside upper corner
             gotoxy(61,17); printf("\xB9"); // Right inside lower corner
             
             //=================================================================
             gotoxy(25,10); printf("\xC9"); // Upper left corner
             for(i=1;i<=30;i++) printf("\xCD"); // Upper left right horizontal 
             gotoxy(55,10); printf("\xBB"); // Upper right corner
             gotoxy(25,14); printf("\xC8"); // Lower left corner 
             for(i=1;i<=30;i++) printf("\xCD"); // Lower left right horizontal
             gotoxy(55,14); printf("\xBC"); // Lower right corner
             for(i=1;i<4;i++){ gotoxy(25,i+10); printf("\xBA"); } // Left vertical
             for(i=1;i<4;i++){ gotoxy(55,i+10); printf("\xBA"); } // Right vertical
        }
             
        void mainMenuGraphicz(){
             gotoxy(21,5); printf("\xC9"); // Upper left corner
             for(i=1;i<=38;i++) printf("\xCD"); // Upper left right horizontal 
             gotoxy(60,5); printf("\xBB"); // Upper right corner
             gotoxy(21,23); printf("\xC8"); // Lower left corner
             for(i=1;i<=38;i++) printf("\xCD"); // Lower left right horizontal 
             gotoxy(60,23); printf("\xBC"); // Lower right corner
             for(i=1;i<18;i++){ gotoxy(21,i+5); printf("\xBA"); } // Left vertical
             for(i=1;i<18;i++){ gotoxy(60,i+5); printf("\xBA"); }// Right vertical
             gotoxy(21,19); printf("\xCC"); // Left inside lower corner
             for(i=1;i<=38;i++) printf("\xCD"); // Inside lower left right horizontal 
             gotoxy(60,19); printf("\xB9"); // Right inside lower corner
             
             //=================================================================
             gotoxy(8+19,2); printf("\xC9"); // Upper left corner
             for(i=1;i<=25;i++) printf("\xCD"); // Upper left right horizontal 
             gotoxy(52,2); printf("\xBB"); // Upper right corner
             gotoxy(8+19,4); printf("\xC8"); // Lower left corner
             for(i=1;i<=25;i++) printf("\xCD"); // Lower left right horizontal 
             gotoxy(52,4); printf("\xBC"); // Lower right corner
             for(i=1;i<2;i++){ gotoxy(27,i+2); printf("\xBA"); } // Left vertical
             for(i=1;i<2;i++){ gotoxy(52,i+2); printf("\xBA"); }// Right vertical
             
             //=================================================================
             gotoxy(41,7); printf("\xC9"); // Upper left corner
             for(i=1;i<=16;i++) printf("\xCD"); // Upper left right horizontal 
             gotoxy(58,7); printf("\xBB"); // Upper right corner
             gotoxy(41,17); printf("\xC8"); // Lower left corner
             for(i=1;i<=16;i++) printf("\xCD"); // Lower left right horizontal 
             gotoxy(58,17); printf("\xBC"); // Lower right corner
             for(i=1;i<10;i++){ gotoxy(41,i+7); printf("\xBA"); } // Left vertical
             for(i=1;i<10;i++){ gotoxy(58,i+7); printf("\xBA"); }// Right vertical
        }
             
        void modifyRecordGraphicz(){
             int i, n;
             clearWindow();
             gotoxy(1,3); printf("\xC9"); // Upper left corner
             for(i=1;i<=76;i++) printf("\xCD"); // Upper left right horizontal 
             gotoxy(78,3); printf("\xBB"); // Upper right corner
             gotoxy(1,24); printf("\xC8"); // Lower left corner
             for(i=1;i<=76;i++) printf("\xCD"); // Lower left right horizontal 
             gotoxy(78,24); printf("\xBC"); // Lower right corner
             for(i=1;i<21;i++){ gotoxy(1,i+3); printf("\xBA"); } // Left vertical
             for(i=1;i<21;i++){ gotoxy(78,i+3); printf("\xBA"); }// Right vertical
             
             //=================================================================
             gotoxy(8+19,0); printf("\xC9"); // Upper left corner
             for(i=1;i<=25;i++) printf("\xCD"); // Upper left right horizontal 
             gotoxy(52,0); printf("\xBB"); // Upper right corner
             gotoxy(8+19,2); printf("\xC8"); // Lower left corner
             for(i=1;i<=25;i++) printf("\xCD"); // Lower left right horizontal 
             gotoxy(52,2); printf("\xBC"); // Lower right corner
             for(i=1;i<2;i++){ gotoxy(27,i+0); printf("\xBA"); } // Left vertical
             for(i=1;i<2;i++){ gotoxy(52,i+0); printf("\xBA"); }// Right vertical
             
             //=================================================================
             // SMALL BOX
             //=================================================================
             gotoxy(3,4); printf("%c",218); // Left Upper Corner
             gotoxy(76,4); printf("%c",191); // Right Upper Corner 
             gotoxy(3,23); printf("%c",192); // Left Lower Corner
             gotoxy(76,23); printf("%c",217); // Right Lower Corner
             for(i=1;i<=72;i++) { gotoxy(3+i,4); printf("%c",196); } // Upper Horizontal
             for(i=1;i<=72;i++) { gotoxy(3+i,23); printf("%c",196); } // Lower Horizontal
             for(i=1;i<=72;i++) { gotoxy(3+i,19); printf("%c",196); } // Middle horizontal
             for(i=1;i<=18;i++) { gotoxy(3,4+i); printf("%c",179); } // Left Vertical
             for(i=1;i<=18;i++) { gotoxy(76,4+i); printf("%c",179); } // Right Vertical
            
             //=================================================================
             // SMALL BOX
             //=================================================================
             gotoxy(32,4); printf("%c",218); // Left Upper Corner
             gotoxy(47,4); printf("%c",191); // Right Upper Corner 
             gotoxy(32,6); printf("%c",192); // Left Lower Corner
             gotoxy(47,6); printf("%c",217); // Right Lower Corner
             for(i=1;i<=14;i++) { gotoxy(32+i,6); printf("%c",196); } // Lower Horizontal
             for(i=1;i<=1;i++) { gotoxy(32,4+i); printf("%c",179); } // Left Vertical
             for(i=1;i<=1;i++) { gotoxy(47,4+i); printf("%c",179); } // Right Vertical
            
             for(i=1;i<=12;i++) { gotoxy(40,6+i); printf("%c",179); } // Cutting Vertical
            
             gotoxy(31,1); std::cout<<" OUTLAWZ BANK INC.";
             gotoxy(12,4); std::cout<<" CURRENT ";
             gotoxy(57,4); std::cout<<" UPDATED ";
             gotoxy(33,3); std::cout<<" EDIT RECORD ";
             gotoxy(33,5); std::cout<<" ACC NO: ";
        }
        
        void modifyRecordDetailz(){
             gotoxy(4,9); std::cout<<" FIRST NAME : ";
             gotoxy(4,11); std::cout<<" OTHER NAME : ";
             gotoxy(4,13); std::cout<<" NATIONALITY : ";
             gotoxy(4,15); std::cout<<" ACCOUNT TYPE [C/S] : ";
             gotoxy(4,17); std::cout<<" ACCOUNT BALANCE : ";
             gotoxy(18,9); std::cout<<fname;
             gotoxy(18,11); std::cout<<lname;
             gotoxy(19,13); std::cout<<nationality;
             gotoxy(26,15); std::cout<<accType;
             gotoxy(23,17); std::cout<<openAmt;
             gotoxy(41,9); std::cout<<" FIRST NAME : ";
             gotoxy(41,11); std::cout<<" OTHER NAME : ";
             gotoxy(41,13); std::cout<<" NATIONALITY : ";
             gotoxy(41,15); std::cout<<" ACCOUNT TYPE [C/S] : ";
             gotoxy(41,17); std::cout<<" UPGRADING AMOUNT : ";
             gotoxy(55,9); std::cin>>fname;
             gotoxy(55,11); std::cin>>lname;
             gotoxy(56,13); std::cin>>nationality;
             gotoxy(63,15); std::cin>>accType;
             gotoxy(61,17); std::cin>>openAmt;
        }

        void aboutUs(){
             int i, n;
             system("cls");
             gotoxy(1,3); printf("\xC9"); // Upper left corner
             for(i=1;i<=76;i++) printf("\xCD"); // Upper left to right horizontal line 
             gotoxy(78,3); printf("\xBB"); // Upper right corner
             gotoxy(1,24); printf("\xC8"); // Lower left corner
             for(i=1;i<=76;i++) printf("\xCD"); // Lower left to right horizontal line 
             gotoxy(78,24); printf("\xBC"); // Lower right corner
             for(i=1;i<21;i++){ gotoxy(1,i+3); printf("\xBA"); } // Left vertical line
             for(i=1;i<21;i++){ gotoxy(78,i+3); printf("\xBA"); }// Right vertical line
             
             //==========================================================================
             gotoxy(8+19,0); printf("\xC9"); // Upper left corner
             for(i=1;i<=25;i++) printf("\xCD"); // Upper left to right horizontal line 
             gotoxy(52,0); printf("\xBB"); // Upper right corner
             gotoxy(8+19,2); printf("\xC8"); // Lower left corner
             for(i=1;i<=25;i++) printf("\xCD"); // Lower left to right horizontal line 
             gotoxy(52,2); printf("\xBC"); // Lower right corner
             for(i=1;i<2;i++){ gotoxy(27,i+0); printf("\xBA"); } // Left vertical line
             for(i=1;i<2;i++){ gotoxy(52,i+0); printf("\xBA"); }// Right vertical line
             
             //===========================================================================
             // SMALL BOX
             //===========================================================================
            gotoxy(3,4); printf("%c",218); // Left Upper Corner
            gotoxy(76,4); printf("%c",191); // Right Upper Corner 
            gotoxy(3,23); printf("%c",192); // Left Lower Corner
            gotoxy(76,23); printf("%c",217); // Right Lower Corner
            for(i=1;i<=72;i++) { gotoxy(3+i,4); printf("%c",196); } // Upper Horizontal line
            for(i=1;i<=72;i++) { gotoxy(3+i,23); printf("%c",196); } // Lower Horizontal line
            for(i=1;i<=72;i++) { gotoxy(3+i,19); printf("%c",196); } // Middle horizontal line
            for(i=1;i<=18;i++) { gotoxy(3,4+i); printf("%c",179); } // Left Vertical Line
            for(i=1;i<=18;i++) { gotoxy(76,4+i); printf("%c",179); } // Right Vertical Line
            gotoxy(31,1); std::cout<<" OUTLAWZ BANK INC.";
            gotoxy(5,4); std::cout<<" ABOUT US ";
            gotoxy(4,6); std::cout<<" OUTLAWZ BANK INC. WAZ STARTED IN 2010 IN HONOUR OF THE LEGENDARY 2PAC ";
            gotoxy(4,7); std::cout<<" AMARU SHAKUR. THE IDEA STARTED WITH A HOMMIE OF MINE DAVID BUYINZA WHO ";
            gotoxy(4,8); std::cout<<" ALSO DOUBLES AS MY BROTHER. SO I DECIDED TO WRITE A SYSTEM ABOUT A";
            gotoxy(4,9); std::cout<<" A BANK AND NAMED IT OUTLAWZ BANK INCORPORATED. OUTLAWZ WAZ STARTED ON ";
            gotoxy(4,10); std::cout<<" A PARTICULAR PURPOSE TO SERVE ALL THE OUTLAWZ OUT THERE LIVING IN THE";
            gotoxy(4,11); std::cout<<" DIASPORA AND FIND IT HARD MAKING IT IN LIFE. OUTLAWZ BANK INC IS A  ";
            gotoxy(4,12); std::cout<<" PRIVATLEY OWNED COMPANY AND ITS NOT AFFILIATED TO ANY BANK. OUTLAWZ";
            gotoxy(4,13); std::cout<<" BANK IS SITUATED IN THE OUTLAWZ TERRITORY BUT SOON GOING GLOBAL.";
            gotoxy(4,14); std::cout<<" OUTLAWZ BANK INC IS FUNDED BY WELL WISHERZ AND THE PEOPLE IN THE AREA";
            gotoxy(4,15); std::cout<<" IT SERVES. IN SHORT THE JOURNEY TO BUILDING THIZ BANK TO BE WHERE IT IS";
            gotoxy(4,16); std::cout<<" TODAY HAS BEEN A HARD ONE FROM DODGING THE BULLETZ AND THE POLICE TO";
            gotoxy(4,17); std::cout<<" THUGGIN ALL DAY. KNUH'MSAYING. OUTLAW TILL I DROP!! - JOSHUA REMINISCE";
            gotoxy(32,19); std::cout<<" NOTIFICATION ";
            gotoxy(18,21); std::cout<<" PRESS ANY KEY TO GO BACK TO THE MAIN MENU.. ";
            getch();
            }
                     
        int retAccNo(){
            return accNo;
            }
        int returnDeposit(){
            return openAmt;
            }
        char returnAcctype(){
             return accType;
             }
        void dep(int x){
             openAmt+=x;
             }
        void withdraw(int x){
             openAmt-=x;
             }
  };
//==============================================================================
//             CLASS OBJECTS DECLARATION AND FILE STREAM OBJECTS
//==============================================================================
   Bank banky;
   FILE *outFile, *inFile;
//==============================================================================
//             FUNCTION - DEPOSIT AMOUNT
//==============================================================================
   void depositAmountz(){
        int amt, n;
        bool found=false;
        char ch;
        do{
        clearWindow();
        banky.deleteRecordGraphicz();
        gotoxy(31,1); std::cout<<" OUTLAWZ BANK INC.";
        gotoxy(19,4); std::cout<<" DEPOSIT AMOUNT ";
        gotoxy(18,21); std::cout<<" ENTER ACCOUNT NUMBER : ";
        fflush(stdin);
        gotoxy(42,21); std::cin>>n;
        inFile = fopen("ACCOUNTZ.dat","rb+");
        if(inFile == NULL){
        MessageBox(0," FILE COULD NOT BE OPENED! \n OR DOES NOT EXIST!","Error",0);
        getch();
        return;
        }
        while(fread(&banky, sizeof(banky),1,inFile) == 1){
        if(banky.retAccNo()==n){
        banky.viewAcc1();
        gotoxy(18,21); std::cout<<" ENTER AMOUNT TO DEPOSIT: ";
        gotoxy(44,21); std::cin>>amt;
        banky.dep(amt);
        fseek(inFile,-sizeof(banky), SEEK_CUR);
        fwrite(&banky,sizeof(banky), 1, inFile);
        gotoxy(18,21); std::cout<<"UG SHS AMOUNT "<<amt<<" DEPOSITED SUCCESSFULLY!";
        getch();
        gotoxy(18,21); std::cout<<"DO YOU WANT TO DEPOSIT MORE AMOUNT? [Y/N]:";
        gotoxy(60,21); std::cin>>ch;
        found=true;
        break;
        }
        }
        if(banky.retAccNo()!=n){
        gotoxy(18,21); std::cout<<" SORRY! ACCOUNT NUMBER " <<n<<" DOES NOT EXIST!";
        getch();
        gotoxy(18,21); std::cout<<"DO U WISH TO RE-TYPE YO ACCOUNT NO? [Y/N]:";
        gotoxy(60,21); std::cin>>ch;
        }
        fclose(inFile);
        }
        while(ch=='y' || ch=='Y');
        gotoxy(18,21); std::cout<<" PLEASE PRESS ENTER TO GO BACK TO MAIN MENU";
        getch();
		return;
  }
//==============================================================================
//                        FUNCTION - BALANCE CHECK
//==============================================================================
   void balanceCheck(){
        int amt, n, i;
        bool found=false;
        char ch;
        do{
        clearWindow();
        banky.displayRecordGraphicz();
        gotoxy(31,1); std::cout<<" OUTLAWZ BANK INC.";
        gotoxy(19,4); std::cout<<" BALANCE CHECK ";
        gotoxy(18,21); std::cout<<" ENTER ACCOUNT NUMBER : ";
        fflush(stdin);
        gotoxy(42,21); std::cin>>n;
        inFile = fopen("ACCOUNTZ.dat","rb+");
        if(inFile == NULL){
        MessageBox(0," FILE COULD NOT BE OPENED! \n OR DOES NOT EXIST!","Error",0);
        getch();
        return;
        }
        while(fread(&banky, sizeof(banky),1,inFile) == 1){
        if(banky.retAccNo()==n){
        gotoxy(31,5); printf("%c",218); // Left Upper Corner
        gotoxy(48,5); printf("%c",191); // Right Upper Corner 
        gotoxy(31,7); printf("%c",192); // Left Lower Corner
        gotoxy(48,7); printf("%c",217); // Right Lower Corner
        for(i=1;i<=16;i++){ gotoxy(31+i,5); printf("%c",196);}// Upper Horizontal
        for(i=1;i<=16;i++){ gotoxy(31+i,7); printf("%c",196);}// Lower Horizontal
        for(i=1;i<=1;i++){ gotoxy(30+i,6); printf("%c",179);}// Left Vertical
        for(i=1;i<=1;i++){ gotoxy(48,5+i); printf("%c",179);}// Right Vertical     
        gotoxy(33,19); std::cout<<" NOTIFICATION ";
        gotoxy(32,6); std::cout<<" ACCOUNT NO: ";
        gotoxy(44,6); std::cout<<banky.accNo;
        gotoxy(18,9);std::cout<<" NAME : "<<banky.fname;
        gotoxy(18,11);std::cout<<" ACCOUNT TYPE : "<<banky.returnAcctype();
        gotoxy(18,13);std::cout<<" YOUR ACCOUNT BALANCE : "<<banky.returnDeposit();
        gotoxy(18,15);std::cout<<" THANK YOU SO MUCH "<<banky.fname<<" FOR BANKING";
        gotoxy(18,17);std::cout<<" WITH OUTLAWZ BANK INCORPORATED!!";
        getch();
        gotoxy(18,21); std::cout<<"WANT TO CHECK MORE ACCOUNT BALANCE? [Y/N]:";
        gotoxy(60,21); std::cin>>ch;
        found=true;
        break;
        }
        }
        if(banky.retAccNo()!=n){
        gotoxy(18,21); std::cout<<" SORRY! ACCOUNT NUMBER " <<n<<" DOES NOT EXIST!";
        getch();
        gotoxy(18,21); std::cout<<"DO U WISH TO RE-TYPE YO ACCOUNT NO? [Y/N]:";
        gotoxy(60,21); std::cin>>ch;
        }
        fclose(inFile);
        }
        while(ch=='y' || ch=='Y');
        gotoxy(18,21); std::cout<<" PLEASE PRESS ENTER TO GO BACK TO MAIN MENU";
        getch();
		return;
  }
//==============================================================================
//             FUNCTION - WITHDRAW AMOUNT
//==============================================================================
   void withdrawAmountz(){
        int amt, n;
        bool found=false;
        char ch;
        do{
        clearWindow();
        banky.deleteRecordGraphicz();
        gotoxy(31,1); std::cout<<" OUTLAWZ BANK INC.";
        gotoxy(19,4); std::cout<<" WITHDRAW AMOUNT ";
        gotoxy(18,21); std::cout<<" ENTER ACCOUNT NUMBER : ";
        fflush(stdin);
        gotoxy(42,21); std::cin>>n;
        inFile = fopen("ACCOUNTZ.dat","rb+");
        if(inFile == NULL){
        MessageBox(0," FILE COULD NOT BE OPENED! \n OR DOES NOT EXIST!","Error",0);
        getch();
        return;
        }
        while(fread(&banky, sizeof(banky),1,inFile) == 1){
        if(banky.retAccNo()==n){
        banky.viewAcc1();
        gotoxy(18,21); std::cout<<" ENTER AMOUNT TO WITHDRAW : ";
        gotoxy(46,21); std::cin>>amt;
        int bal=banky.returnDeposit()-amt;
        if((bal<=500 && banky.returnAcctype()=='s' || bal<=500 && banky.returnAcctype()=='S') 
        || (bal<=1000 && banky.returnAcctype()=='c' || bal<=1000 && banky.returnAcctype()=='C')){
        gotoxy(18,21); std::cout<<" SORRY! YOUR ACCOUNT BALANCE IS TOO LOW!";
        getch();
        gotoxy(18,21); std::cout<<"DO U WISH TO TRY AGAIN WITHDRAWING? [Y/N]:";
        gotoxy(60,21); std::cin>>ch;
        break;
        }
        if((bal>500 && banky.returnAcctype()=='s' || bal>500 && banky.returnAcctype()=='S') 
        || (bal>1000 && banky.returnAcctype()=='c' || bal>1000 && banky.returnAcctype()=='C')){
        banky.withdraw(amt);
        fseek(inFile,-sizeof(banky), SEEK_CUR);
        fwrite(&banky,sizeof(banky), 1, inFile);
        gotoxy(18,21); std::cout<<"UG SHS AMOUNT "<<amt<<" WITHDRAWN SUCCESSFULLY!";
        getch();
        gotoxy(18,21); std::cout<<"DO YOU WISH TO WITHDRAW MORE CASH? [Y/N]:";
        gotoxy(60,21); std::cin>>ch;
        break;
        }
        }
        }
        if(banky.retAccNo()!=n){
        gotoxy(18,21); std::cout<<" SORRY! ACCOUNT NUMBER " <<n<<" DOES NOT EXIST!";
        getch();
        gotoxy(18,21); std::cout<<"DO U WANT TO RE-TYPE YO ACCOUNT NO? [Y/N]:";
        gotoxy(60,21); std::cin>>ch;
        }
        fclose(inFile);
        }
        while(ch=='y' || ch=='Y');
        gotoxy(18,21); std::cout<<" PLEASE PRESS ENTER TO GO BACK TO MAIN MENU";
        getch();
		return;
  }
//==============================================================================
//                        FUNCTION MAIN BANKER MENU 
//==============================================================================
  void bankerMenu(){
       int i, n;
       do {
           system("cls");
           system("color 09");
           banky.adminMenuGraphicz();
           gotoxy(32,3); std::cout<<"OUTLAWZ BANK INC.";
           gotoxy(18,8); std::cout<<"[1] ABOUT US";
           gotoxy(18,10); std::cout<<"[2] DEPOSIT AMOUNT";
           gotoxy(18,12); std::cout<<"[3] BALANCE CHECK";
           gotoxy(18,14); std::cout<<"[4] WITHDRAW AMOUNT";
           gotoxy(18,16); std::cout<<"[5] LOG OUT";
           gotoxy(19,21); std::cout<<"SELECT FROM [1-5] : ";
           gotoxy(39,21); std::cin>>n;
           
       switch(n){
                 case 1: banky.aboutUs();
                 break;
                 case 2: depositAmountz();
                 break;
                 case 3: balanceCheck();
                 break;
                 case 4: withdrawAmountz();
                 break;
                 default: gotoxy(19,21); std::cout<<" THANK YOU SO MUCH FOR BANKING WITH US!";
                 getch();
                 gotoxy(19,21); std::cout<<" PLEASE PRESS ENTER TO GO BACK TO MAIN MENU";
                 getch();
                 }
                 }
                 while(n!=5); 
  }    
//==============================================================================
//                     FUNCTION - BANKER LOGIN
//==============================================================================
   void bankerLogin(void){        
        int i, j, k, n;
        bool found=false;
        char ch;
        do{
        clearWindow();
        banky.adminLoginGraphicz();
        gotoxy(30,5); std::cout<<"OUTLAWZ BANK INC.";
        gotoxy(30,12); std::cout<<"Account No:__________";
        gotoxy(33,17); std::cout<<" NOTIFICATION ";
        gotoxy(41,12); std::cin>>n;
        inFile = fopen("ACCOUNTZ.dat","rb+");
        if(inFile == NULL){
        MessageBox(0," FILE COULD NOT BE OPENED! \n OR DOES NOT EXIST!","Error",0);
        getch();
        return;
        }
        while(fread(&banky,sizeof(banky),1,inFile) == 1){        
        if(banky.retAccNo()==n){
        for(j=1;j<=1;j++){
        if(j==1){gotoxy(25,21);printf("Loading Banker Menu Please Wait...");}
        for(k=22;k<60;k++){gotoxy(k,20);printf("�");}
        for(k=22;k<60;k++){gotoxy(k,20); putch(10000);
        Sleep(150);
        }
        }
        bankerMenu();
        return;
        }
        found = true;                
        }
        if(banky.retAccNo()!=n){
        gotoxy(21,20); std::cout<<" SORRY ACCOUNT NUMBER "<<n<<" DOESNT EXIST";
        getch();
        gotoxy(21,20); std::cout<<" DO YOU WANT TO TRY RE-ENTERIN? [Y/N]: ";
        gotoxy(59,20); std::cin>>ch;
        }
        fclose(inFile);
        }
        while(ch=='y' || ch=='Y');
        gotoxy(21,20); std::cout<<" PRESS ENTER TO GO BACK TO THE MAIN MENU";
        getch();
        return;
   }
//==============================================================================
//                   FUNCTION TO WRITE RECORDZ TO FILE
//==============================================================================
    void addRecord(){
       char ch;
       do{
       clearWindow();
       outFile = fopen("ACCOUNTZ.dat","ab+");
       if(outFile == NULL){
       MessageBox(0,"ERROR! FILE COULD NOT BE CREATED!","Warning",0);
       }
       else {
       fflush(stdin);
       banky.openAcc();
       fwrite(&banky, sizeof(banky), 1, outFile);
       gotoxy(18,21); std::cout<<" DO U WISH TO OPEN MORE ACCOUNTZ? [Y/N]: ";
       gotoxy(59,21); std::cin>>ch;
       fflush(stdin);
       }
       fclose(outFile);
       }
       while(ch=='y' || ch=='Y');
       gotoxy(18,21); std::cout<<" PLEASE PRESS ENTER TO GO BACK TO MAIN MENU";
       getch();
       return;
       }
//==============================================================================
//           FUNCTION TO SEARCH AND SHOW A SPECIFIC RECORD
//==============================================================================
    void displayRecord(){
       char ch;
       int n, isFound = 0;
       do{
         clearWindow();
         banky.displayRecordGraphicz();
         gotoxy(31,1); std::cout<<" OUTLAWZ BANK INC.";
         gotoxy(19,4); std::cout<<" VIEW RECORD ";
         gotoxy(18,21); std::cout<<" ENTER ACCOUNT NUMBER : ";
         gotoxy(42,21); std::cin>>n;
         fflush(stdin);
         inFile = fopen("ACCOUNTZ.dat","rb");
         if(inFile == NULL){
         MessageBox(0," FILE COULD NOT BE OPENED! \n OR DOES NOT EXIST!","Error",0);
         getch();
         return;
         }
         while(fread(&banky,sizeof(banky),1,inFile)){
         if(banky.retAccNo()==n){
         banky.viewAcc1();
         gotoxy(18,21); std::cout<<"DO YOU WANT TO CHECK MORE ACCOUNTZ? [Y/N]: ";
         gotoxy(60,21); std::cin>>ch;
         isFound = 1;                
         break;
         }
         }
         if(banky.retAccNo()!=n){
         gotoxy(19,21); std::cout<<"SORRY! THE ACCOUNT NUMBER DOESN'T EXIST!";
         getch();
         gotoxy(18,21); std::cout<<"DO YOU WANT TO CHECK MORE ACCOUNTZ? [Y/N]: ";
         gotoxy(60,21); std::cin>>ch;
         }
         fclose(inFile);
         }
         while(ch=='y' || ch=='Y');
         gotoxy(18,21); std::cout<<" PLEASE PRESS ENTER TO GO BACK TO MAIN MENU";
         getch();
         return;
    }
//==============================================================================
//                    FUNCTION TO DISPLAY ALL ACCOUNTZ
//==============================================================================
  void displayAllRecordz(int j=8){
       clearWindow();
       inFile = fopen("ACCOUNTZ.dat","rb");
       if(inFile == NULL){
       MessageBox(0," FILE COULD NOT BE OPENED! \n OR DOES NOT EXIST!","Error",0);
       getch();
       return;
       }
       else {
       fflush(stdin);
       while(fread(&banky,sizeof(banky),1,inFile) == 1){
       banky.viewAllAcc();
       gotoxy(6,j); printf("%d",banky.accNo);
       gotoxy(14,j); printf("%s",banky.fname);
       gotoxy(27,j); printf("%s",banky.lname);
       gotoxy(40,j); printf("%s",banky.nationality);
       gotoxy(56,j); std::cout<<banky.accType;
       gotoxy(66,j); printf("%d",banky.openAmt);
       j=j+1;
       }
       }
       fclose(inFile);
       getch();
       return;
  }
//==============================================================================
//             FUNCTION TO MODIFY RECORD IN FILE [DATABASE]
//==============================================================================
  void editRecord(){
       int n, isFound = 0;
       char ch;
       do{
       clearWindowz();
       banky.modifyRecordGraphicz();
       gotoxy(42,5); std::cin>>n;
       inFile = fopen("ACCOUNTZ.dat","rb+");
       if(inFile == NULL){
       MessageBox(0," FILE COULD NOT BE OPENED! \n OR DOES NOT EXIST!","Error",0);
       getch();
       return;
       }
       while(fread(&banky, sizeof(banky),1,inFile) == 1){
       if(banky.retAccNo()==n){
       fflush(stdin);
       banky.modifyRecordDetailz();
       fseek(inFile,-sizeof(banky), SEEK_CUR);
       fwrite(&banky,sizeof(banky), 1, inFile);
       gotoxy(26,21); std::cout<<" ACCOUNT UPDATED SUCCESSFULLY!";
       getch();
       gotoxy(17,21); std::cout<<"DO YOU WANT TO UPDATE MORE ACCOUNTZ? [Y/N]: ";
       gotoxy(61,21); std::cin>>ch;
       isFound = 1;
       break;
       }
       }
       if(banky.retAccNo()!=n){
       gotoxy(19,21); std::cout<<" SORRY! ACCOUNT NUMBER "<<n<<" DOES NOT EXIST!";
       getch();
       gotoxy(18,21); std::cout<<" DO YOU WANT TO UPDATE MORE ACCOUNTZ? [Y/N]: ";
       gotoxy(63,21); std::cin>>ch;
       }
       fclose(inFile);
       }
       while(ch=='y' || ch=='Y');
       gotoxy(16,21); std::cout<<" PLEASE PRESS ENTER KEY TO GO BACK TO THE MAIN MENU";
       getch();
       return;
  }
//==============================================================================
//          FUNCTION ERASE/ DELETE BANKER DATA FROM FILE [DATABASE]
//==============================================================================
  void deleteRecord(){
       int n;
       char ch;
       clearWindow();
       banky.deleteRecordGraphicz();
       gotoxy(31,1); std::cout<<" OUTLAWZ BANK INC.";
       gotoxy(19,4); std::cout<<" DELETE RECORD ";
       gotoxy(18,21); std::cout<<" ENTER ACCOUNT NUMBER : ";
       fflush(stdin);
       gotoxy(42,21); std::cin>>n;
       inFile = fopen("ACCOUNTZ.dat","rb");
       if(inFile == NULL){
       MessageBox(0," FILE COULD NOT BE OPENED! \n OR DOES NOT EXIST!","Error",0);
       getch();
       return;
       }
       outFile = fopen("TEMP.dat", "wb");
       while(fread(&banky, sizeof(banky),1,inFile) == 1){
       if(banky.retAccNo()!=n){
       fwrite(&banky,sizeof(banky),1,outFile);
       }
       }
       gotoxy(18,21); std::cout<<" ACCOUNT HAS BEEN DELETED SUCCESSFULLY!";
       getch();
       fclose(inFile);
       fclose(outFile);
       remove("ACCOUNTZ.dat");
       rename("TEMP.dat","ACCOUNTZ.dat");
       gotoxy(18,21); std::cout<<" PRESS ENTER KEY TO GO BACK TO THE MAIN MENU";
       getch();   
       return;
  }
//==============================================================================
//                      ADMINISTRATOR MENU GRAPHICZ
//==============================================================================
 void adminMenu(){  
    int i, n;
    do {
    system("cls");
    system("color 09");
    banky.adminMenuGraphicz();
    gotoxy(32,3); std::cout<<"OUTLAWZ BANK INC.";
    gotoxy(18,7); std::cout<<"[1] OPEN ACCOUNT";
    gotoxy(18,9); std::cout<<"[2] VIEW SPEC. ACCOUNT";
    gotoxy(18,11); std::cout<<"[3] VIEW ALL ACCOUNTZ";
    gotoxy(18,13); std::cout<<"[4] MODIFY ACCOUNT";
    gotoxy(18,15); std::cout<<"[5] CLOSE ACCOUNT";
    gotoxy(18,17); std::cout<<"[6] LOG OUT";
    gotoxy(19,21); std::cout<<"SELECT FROM [1-6] : ";
    gotoxy(39,21); std::cin>>n;
    
    switch(n){
              case 1: addRecord();
              break;
              case 2: displayRecord();
              break;
              case 3: displayAllRecordz();
              break;
              case 4: editRecord();
              break;
              case 5: deleteRecord();
              break;
              default: gotoxy(19,21); std::cout<<" BYE BYE ADMIN HOPE TO SEE YOU AGAIN SOON!";
              getch();
              gotoxy(19,21); std::cout<<" PLEASE PRESS ENTER TO GO BACK TO MAIN MENU!";
              getch();
              }
              }
              while(n!=6);
    }   
//==============================================================================
//                         ADMINISTRATOR GRAPHICZ
//==============================================================================
 void adminLogin(void){
      string adminName, pass;
      int i, j, k;
      char ch;
      do{
          clearWindow();
          banky.adminLoginGraphicz();
          gotoxy(30,5); std::cout<<"OUTLAWZ BANK INC.";
          gotoxy(30,11); std::cout<<"Username: ___________ ";
          gotoxy(30,13); std::cout<<"Password: ___________ ";
          gotoxy(33,17); std::cout<<" NOTIFICATION ";
          gotoxy(40,11); std::cin>>adminName;
          gotoxy(40,13); std::cin>>pass;
          if(adminName=="admin" && pass=="123"){
          for(j=1;j<=1;j++){
          if(j==1){gotoxy(28,21);printf("Loading Admin Please Wait...");}
          for(k=22;k<60;k++){gotoxy(k,20);printf("�");}
          for(k=22;k<60;k++){gotoxy(k,20); putch(10000);
          Sleep(150);
          }
          }
          adminMenu();
          return;
          }
          else {
               gotoxy(23,20); std::cout<<"SORRY! WRONG ADMIN NAME OR PASSWORD!";
               getch();
               gotoxy(21,20); std::cout<<" DO YOU WANT TO TRY RE-ENTERIN? [Y/N]: ";
               gotoxy(59,20); std::cin>>ch;
               }     
          }
          while(ch == 'y' || ch == 'Y');
          return;
      }
//==============================================================================
//                       FUNCTION ABOUT THE PROGRAMMER
//==============================================================================
 void aboutProgrammer(void){
      int i, j, k;
      clearWindow();
      banky.aboutProgrammerGraphicz();
      gotoxy(30,5); std::cout<<"OUTLAWZ BANK INC.";
      gotoxy(26,11); std::cout<<"PROGRAMMER: Joshua Reminisce";
      gotoxy(26,13); std::cout<<"EMAIL: joshuapark61@gmail.com";
      gotoxy(33,17); std::cout<<" NOTIFICATION ";
      for(j=1;j<=1;j++){
      if(j==1){gotoxy(30,21);printf("EXITING SYSTEM... BYE!!");}
      for(k=22;k<60;k++){gotoxy(k,20);printf("�");}
      for(k=22;k<60;k++){gotoxy(k,20); putch(10000);
      Sleep(200);
      }
      exit(0);
      }
 } 
//==============================================================================
//               FUNCTION MAIN MENU [ADMINISTRATOR/ BANKER MENU]
//==============================================================================
  void mainMenu(void){
       int i, j;
       system("cls");
       system("color 09");
       banky.mainMenuGraphicz();
       do {
           gotoxy(25,8); std::cout<<"MAIN MENU";
           for(i=1;i<=9;i++) { gotoxy(24+i,9); printf("%c",196); }
           gotoxy(23,11); std::cout<<"[1] CUSTOMER ";
           gotoxy(23,13); std::cout<<"[2] ADMINISTRATOR ";
           gotoxy(23,15); std::cout<<"[3] EXIT ";
           gotoxy(32,3); std::cout<<"OUTLAWZ BANK INC.";
           gotoxy(24,21); std::cout<<"SELECT FROM [1-3] : ";
           gotoxy(44,21); std::cin>>j; 
           
           switch(j){
                     case 1: bankerLogin();
                     break;
                     case 2: adminLogin();
                     break;
                     default: aboutProgrammer();
                     }
                     clearWindow();
                     banky.mainMenuGraphicz();
                     }  
                     while(j>0 && j<=2);
           }
//==============================================================================
//                      FUNCTION WELCOME SCREEN/ PROGRESS BAR
//==============================================================================
 void progressBar(){   
    int i, j, k;
    system("cls");
    system("color 09");
    banky.progressBarGraphicz();
    for(j=1;j<=3;j++){
    if(j==1){gotoxy(32,21);printf("Checking folders...");}
    if(j==2){gotoxy(32,21);printf("Checking files...");}
    if(j==3){gotoxy(32,21);printf("Loading System...");}
    for(k=10;k<69;k++){gotoxy(k,20);printf("�");}
    for(k=10;k<69;k++){gotoxy(k,20); putch(10000);
    Sleep(120);
    }
    }
    system("cls");
    mainMenu();
    getch();
 }
//==============================================================================
//                       FUNCTION MAIN FUNCTION
//==============================================================================
  int main(){
      SetConsoleTitle("OUTLAWZ BANK INC.");
      progressBar();
      }
//==============================================================================
//                       END OF THE PROGRAM/ PROJECT
//==============================================================================
