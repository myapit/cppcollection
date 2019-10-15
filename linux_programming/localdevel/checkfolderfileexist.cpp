#include <fstream>
#include <iostream>
#include <string>
/* Linux POSIX */
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define RST "\x1B[0m"
//printf(WHT "putih\n" RST)

using namespace std;

int main( int argc, char *argv[] )
{
  const string dirName = "/kambing";
  bool dirCheck;// = ifstream( dirName.c_str() ).good();
  struct stat filestat;
   
  if ( argc != 2 )  {
     cerr << "usage: " << argv[0] << " <directory full path>. \n";
  } else {
    dirCheck = ifstream( argv[1] ).good();
    if ( !dirCheck )
       cerr << RED <<  "Failed: Dir @ File " << argv[1] << " Not Exists." << RST << endl;
    else 
      cerr << GRN << "Success: Dir @ File " << argv [1] << " Exists." << RST << endl;
  }
   
  if ( stat( argv[1], &filestat) == 0)
	if ( filestat.st_mode & S_IFDIR )
           cout << "Type: Directory\n";
        else 
           cout << "Type: File\n";  
  
  return 0;
}
