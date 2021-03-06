CC=g++
CFLAGS=-c -g -pedantic -Wall

all: a.out

Game.o:Game.cpp Game.hh
	$(CC) $(CFLAGS) Game.cpp -std=c++11

AI.o:AI.cpp AI.hh Game.hh
	$(CC) $(CFLAGS) AI.cpp -std=c++11

main.o: main.cpp AI.hh
	$(CC) $(CFLAGS) main.cpp -std=c++11

a.out:main.o AI.o Game.o
	$(CC) main.o AI.o Game.o

