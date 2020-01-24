OBJS	= libmycode.o mainprog.o
SOURCE	= libmycode.c mainprog.c
HEADER	= libmycode.h
OUT	= mainprog libmycode.so runtime_mainprog libstaticmycode.a static_mainprog runtime2
LFLAGS	= -Wall -g 
CC      = gcc 


all: $(OUT)

mainprog: mainprog.c libmycode.o
		$(CC) -o $@ $^ $(LFLAGS)


libmycode.so: libmycode.c libmycode.h
	$(CC) $(LFLAGS) -fPIC -shared -o $@ libmycode.c -lc


runtime_mainprog: mainprog.c
	$(CC) $(LFLAGS) -o $@ $^ -L. -lmycode

libstaticmycode.a: libmycode.o
	ar rcs  libstaticmycode.a libmycode.o

static_mainprog: mainprog.c
	$(CC) $(LFLAGS) -o $@ $^ -L. -lstaticmycode
	
runtime2: mainprog.c
	$(CC) $(LFLAGS) -o $@ $^ -L /usr/local/lib -lmycode
#%.o: %.c $(HEADER)
#		$(CC) -c -o $@ $< $(LFLAGS)

clean:
		rm -f $(OBJS) $(OUT)

