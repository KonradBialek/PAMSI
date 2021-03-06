#ifndef ELISTGRAPH_HH
#define ELISTGRAPH_HH

#include <iomanip>
#include <iostream>
#include <fstream>
#include "Graph.hh"

/*!
 * Zrodla:
 * https://en.wikipedia.org/wiki/Edge_list
 * https://www.khanacademy.org/computing/computer-science/algorithms/graph-representation/a/representing-graphs
 * https://stackabuse.com/graphs-in-java-representing-graphs-in-code/
 */
class elistgraph : public Graph // definicja listy krawedzi (edge_list graph)
{
  Edge *edges;

public:
  /*!
   * \brief Funkcje umozliwiajace kontrolowany dostep do pol klasy.
   *
   * Funkcje umozliwiajace kontrolowany dostep do pol klasy.
   * \param[in] brak
   *
   * \pre Wskaznik na obiekt typu elistgraph nie moze miec watosci NULL.
   * \post brak
   * \retval Odpowiednie pole klasy
   */
  Edge *getedges()  const { return edges; }
  Edge *&setedges()       { return edges; }

  void printgraph() const; // wyswietl graf
  void insertedge(int istart, int weight_value, int iend, int iedge); // wstawia krawedz
  bool connection_exist(int start, int end) const; // sprawdza czy istnieje polaczenie
  void fillgraph(int shift, int range); // wypelnia graf
  void is_open(std::ofstream &file) const; // otwiera plik do zapisu
  void makeInput(int startV) const; // zapisuje graf do pliku
  void makeOutput(int **data, int startV, std::ofstream &file) const; 
  // zapisuje wynik algorytmu do pliku

  /*!
   * \brief Konstruktor bezparametryczny obiektu typu elistgraph.
   *
   * Konstruktor bezparametryczny obiektu typu elistgraph.
   *
   * \pre brak
   * \post Tworzy graf jako liste krawedzi.
   */
  elistgraph() {}

  /*!
   * \brief Konstruktor parametryczny obiektu typu elistgraph.
   *
   * Konstruktor parametryczny obiektu typu elistgraph.
   * \param[in] nov - ilosc wierzcholkow (number of verticles),
   * \param[in] pod - gestosc grafu (percent of density).
   *
   * \pre brak
   * \post Tworzy graf jako liste krawedzi.
   */
  explicit elistgraph(int nov, double pod) : Graph(nov, static_cast<int>(pod * nov * (nov - 1)), pod),
                                             edges(new Edge[getEdges()]) {}

  /*!
   * \brief Konstruktor parametryczny obiektu typu elistgraph.
   *
   * Konstruktor parametryczny obiektu typu elistgraph.
   * \param[in] nov - ilosc wierzcholkow (number of verticles),
   * \param[in] noe - ilosc krawedzi (number of edges).
   *
   * \pre brak
   * \post Tworzy graf jako liste krawedzi.
   */
  explicit elistgraph(int nov, int noe) : Graph(nov, noe, static_cast<int>(noe / (nov * (nov - 1)))),
                                          edges(new Edge[getEdges()]) {}

  /*!
   * \brief Destruktor obiektu typu elistgraph.
   *
   * Destruktor obiektu typu elistgraph.
   *
   * \pre Graf istnieje.
   * \post Usuwa graf.
   */
  ~elistgraph() { delete[] edges; } // destruktor obiektu
};

#endif
