

CC=gcc
CFLAGS=-g -Wall

all: main
	
main: main.c util.o
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $^ -o $@

clean:
	rm -f main *.o
