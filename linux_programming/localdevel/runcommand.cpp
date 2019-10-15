#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>

using namespace std;


int main()
{
  cout << "Test Run using C like pipe command:" << endl;
  string myCMD = "ls -lah";
  
  char buff[BUFSIZ];
   /* http://www.cplusplus.com/reference/cstdio/BUFSIZ/ */
  FILE *fp = popen( myCMD.c_str(), "r" );
  while ( fgets( buff, BUFSIZ, fp ) != NULL ) {
    printf("%s", buff );
  }
  pclose(fp);

   
  return 0;
}
