CC=g++
CFLAGS=-c -g -pedantic -Wall

all: a.out

nmatrixgraph.o:nmatrixgraph.cpp nmatrixgraph.hh elistgraph.hh
	$(CC) $(CFLAGS) nmatrixgraph.cpp -std=c++11

nlistgraph.o:nlistgraph.cpp nlistgraph.hh elistgraph.hh
	$(CC) $(CFLAGS) nlistgraph.cpp -std=c++11

elistgraph.o:elistgraph.cpp elistgraph.hh Graph.hh
	$(CC) $(CFLAGS) elistgraph.cpp -std=c++11

Bellman_Ford_alg.o:Bellman_Ford_alg.cpp Bellman_Ford_alg.hh nlistgraph.hh nmatrixgraph.hh
	$(CC) $(CFLAGS) Bellman_Ford_alg.cpp -std=c++11

main.o: main.cpp Bellman_Ford_alg.hh
	$(CC) $(CFLAGS) main.cpp -std=c++11

a.out:main.o elistgraph.o nlistgraph.o nmatrixgraph.o Bellman_Ford_alg.o
	$(CC) main.o elistgraph.o nlistgraph.o nmatrixgraph.o Bellman_Ford_alg.o

