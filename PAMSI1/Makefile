CC=g++
CFLAGS=-pedantic -Wall

all: a.out

sorting.o:sorting.cpp sorting.hh
	$(CC) -c $(CFLAGS) sorting.cpp -std=c++11

main.o: main.cpp sorting.hh
	$(CC) -c $(CFLAGS) main.cpp -std=c++11

a.out:main.o sorting.o
	$(CC) main.o sorting.o

