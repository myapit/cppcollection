#include <conio.h>
#include <stdio.h>
#include <string.h>

int main()
{
  char users_name[ 100 ];

  printf( "What is your name> " );
  fgets( users_name, sizeof( users_name ), stdin );
  *strchr( users_name, '\n' ) = '\0';

  /* Here is where we clear the screen */
  clrscr();

  printf( "Greetings and salutations %s!\n", users_name );

  printf( "\n\n\nPress ENTER to quit." );
  fgets( users_name, sizeof( users_name ), stdin );

  return 0;
}
