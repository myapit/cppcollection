#Filename: Makefile
#Author : myapit
#E-mail : 9w2xhr@gmail.com
#Purpose: Basic skeleton makefile
# g++ -c = compile and assemble, but do not link.

program: program_stuff.o program_utils.o
	g++ program_stuff.o program_utils.o -o program

program_stuff.o: program_stuff.cpp
	g++ -c program_stuff.cpp

program_utils.o: program_utils.cpp
	g++ -c program_utils.cpp

clean:
	rm *.o program