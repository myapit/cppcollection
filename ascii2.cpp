#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int main()
{
       std::vector<std::string> picture =
              {
                  R"(#######################################################)",
                  R"(#           _                                         #)",
                  R"(#         -=\\`\\                                     #)",
                  R"(#     |\\ ____\\_\\__                                 #)",
                  R"(#   -=\\c`""""""" "`)                                 #)",
                  R"(#      `~~~~~/ /~~`\                                  #)",
                  R"(#        -==/ /                                       #)",
                  R"(#                                                     #)",
                  R"(#######################################################)"
          } ;

          //printf(picture) ;
            std::cout << picture;
             //for( int i=0 ; i<5 ; ++i ) 
            std::shift_right(picture.begin(),picture.end(),8);
              for (auto v: picture)
                  std::cout << v;
                //printf( shift_right(picture,8) ) ;
}
