

CC=g++
CFLAGS=-g -Wall

all: main
	
main: main.cc util.o
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.cc
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -f main *.o
