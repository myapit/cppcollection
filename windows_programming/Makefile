# Author: myapit
# Windows makefile using nmake command.
# No need to compile .h as .cpp will include it.

# Specify Compiler
CC=cl.exe
# Linker
LINK=link.exe
# Objects
OBJ=*.obj
#Output Program Name
OUTPUT=myprogram.exe
#Compiler Flags
FLAGS=/EHsc /c

#Building 
mybuild: $(OBJ)
	$(LINK)  /OUT:$(OUTPUT) $(OBJ)

#Compile all .cpp to object with depedencies
*.obj: *.cpp
	$(CC) $(FLAGS)  $**

clean:
	del *.exe *.obj