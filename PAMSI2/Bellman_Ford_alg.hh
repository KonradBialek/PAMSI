#ifndef BELLMAN_FORD_HH
#define BELLMAN_FORD_HH

#include <limits>
#include <chrono>
#include "nlistgraph.hh"
#include "nmatrixgraph.hh"

int **Bellman_Ford_alg(elistgraph *graph, int startV);
//algorytm szukania najkrotszej sciezki w grafie jako liscie krawedzi

int **Bellman_Ford_alg(nlistgraph *graph, int startV);
//algorytm szukania najkrotszej sciezki w grafie jako liscie sasiedztwa

int **Bellman_Ford_alg(nmatrixgraph *graph, int startV);
//algorytm szukania najkrotszej sciezki w grafie jako macierzy sasiedztwa

#endif
