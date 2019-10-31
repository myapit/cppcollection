#include <iostream>
#include <vector>
#include <algorithm>

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

          print(picture) ;

             for( int i=0 ; i<5 ; ++i ) print( shift_right(picture,8) ) ;
}
