#ifndef NMATRIXGRAPH_HH
#define NMATRIXGRAPH_HH

#include "elistgraph.hh"

class IncidenceMatrix // definicja elementu macierzy (nie dziedziczy z Edge, to zupelnie inny obiekt)
{
  // ta klasa jest w pelni zalezna od klasy ponizej, dlatego obie sa w jednym pliku
  Edge *edge;

public:
  /*!
   * \brief Funkcje umozliwiajace kontrolowany dostep do pol klasy.
   *
   * Funkcje umozliwiajace kontrolowany dostep do pol klasy.
   * \param[in] brak
   *
   * \pre Wskaznik na obiekt typu IncidenceMatrix nie moze miec watosci NULL.
   * \post brak
   * \retval Odpowiednie pole klasy
   */
  const Edge *getedge() const { return edge; }
  Edge *&setedge()            { return edge; }

  void push(IncidenceMatrix *arg); // Wstawia krawedz (jako wskaznik) do macierzy.

  /*!
   * \brief Konstruktor parametryczny obiektu typu IncidenceMatrix.
   *
   * Konstruktor parametryczny obiektu typu IncidenceMatrix.
   * \param[in] newedge - wstawiana krawedz.
   * 
   * \pre newedge nie wskazuje na NULL.
   * \post Tworzy element macierzy z zawartoscia.
   */
  explicit IncidenceMatrix(Edge *newedge) { edge = newedge; }

  /*!
   * \brief Konstruktor bezparametryczny obiektu typu IncidenceMatrix.
   *
   * Konstruktor bezparametryczny obiektu typu IncidenceMatrix.
   *
   * \pre brak
   * \post Tworzy element macierzy jako zbior pustych danych.
   */
  IncidenceMatrix() {}

  /*!
   * \brief Destruktor obiektu typu IncidenceMatrix.
   *
   * Destruktor obiektu typu IncidenceMatrix.
   *
   * \pre brak
   * \post Usuwa element macierzy.
   */
  ~IncidenceMatrix() {}
};

/*!
 * Zrodla:
 * https://en.wikipedia.org/wiki/Incidence_matrix
 * https://www.khanacademy.org/computing/computer-science/algorithms/graph-representation/a/representing-graphs
 * https://stackabuse.com/graphs-in-java-representing-graphs-in-code/
 */
class nmatrixgraph : public elistgraph // definicja macierzy sasiedztwa (neighborhood_matrix graph)
{
  IncidenceMatrix **MatrixOfEdges;

public:
  /*!
   * \brief Funkcje umozliwiajace kontrolowany dostep do pol klasy.
   *
   * Funkcje umozliwiajace kontrolowany dostep do pol klasy.
   * \param[in] brak
   *
   * \pre Wskaznik na obiekt typu nmatrixgraph nie moze miec watosci NULL.
   * \post brak
   * \retval Odpowiednie pole klasy
   */
  IncidenceMatrix **getMatrixOfEdges()  const { return MatrixOfEdges; }
  IncidenceMatrix **&setMatrixOfEdges()       { return MatrixOfEdges; }

  void printgraph() const; //wyswietl graf
  void insertedge(int istart, int weight_value, int iend, int iedge); // wstawia krawedz
  void fillgraph(int shift, int range); // wypelnia graf
  void makeInput(int startV) const; // zapisuje graf do pliku
  explicit nmatrixgraph(int nov, double pod); // Konstruktor parametryczny
  explicit nmatrixgraph(int nov, int noe); // Konstruktor parametryczny

  /*!
   * \brief Konstruktor bezparametryczny obiektu typu nlistgraph.
   *
   * Konstruktor bezparametryczny obiektu typu nlistgraph.
   *
   * \pre brak
   * \post Tworzy liste krawedzi.
   */
  nmatrixgraph() {}
  
  
  ~nmatrixgraph(); // Destruktor

};

#endif
