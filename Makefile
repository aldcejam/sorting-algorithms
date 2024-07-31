PROG = run
CC = g++
CPPFLAGS = -O0 -g -std=c++11 -Wall -pedantic
OBJS = main.o

$(PROG): $(OBJS)
	$(CC) -o $(PROG) $(OBJS)

main.o: main.cpp
	$(CC) $(CPPFLAGS) -c main.cpp

clean:
	rm -f $(PROG) $(OBJS)
