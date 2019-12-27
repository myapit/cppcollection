CC = g++
OBJS	= list.o main.o
SOURCE	= list.cc main.cc
HEADER	= list.hpp
OUT	= linkedlist.exe
LFLAGS	 = --std=c++17

all: linkedlist.exe

linkedlist.exe: $(OBJS)
	$(CC) -o $@ $^ $(LFLAGS)

%.o: %.c $(HEADER)
	$(CC) -c -o $@ $< $(LFLAGS)

clean:
	rm -f $(OBJS) $(OUT)