#ifndef NLISTGRAPH_HH
#define NLISTGRAPH_HH

#include "elistgraph.hh"

class IncidenceList // definicja elementu listy (nie dziedziczy z Edge, to zupelnie inny obiekt)
{
  // ta klasa jest w pelni zalezna od klasy ponizej, dlatego obie sa w jednym pliku
  Edge *edge;
  IncidenceList *next;

public:
  /*!
   * \brief Funkcje umozliwiajace kontrolowany dostep do pol klasy.
   *
   * Funkcje umozliwiajace kontrolowany dostep do pol klasy.
   * \param[in] brak
   *
   * \pre Wskaznik na obiekt typu IncidenceList nie moze miec watosci NULL.
   * \post brak
   * \retval Odpowiednie pole klasy
   */
  const Edge *getedge()     const { return edge; }
  Edge *&setedge()                { return edge; }
  IncidenceList *getnext()  const { return next; }
  IncidenceList *&setnext()       { return next; }

  void push(IncidenceList *arg); // Wstawia krawedz (jako wskaznik) do listy.

  /*!
   * \brief Konstruktor parametryczny obiektu typu IncidenceList.
   *
   * Konstruktor parametryczny obiektu typu IncidenceList.
   * \param[in] newedge - wstawiana krawedz.
   * 
   * \pre newedge nie wskazuje na NULL.
   * \post Tworzy element listy z zawartoscia.
   */
  explicit IncidenceList(Edge *newedge) : edge(newedge), next(NULL) {}

  /*!
   * \brief Konstruktor bezparametryczny obiektu typu IncidenceList.
   *
   * Konstruktor bezparametryczny obiektu typu IncidenceList.
   *
   * \pre brak
   * \post Tworzy element listy jako zbior pustych danych.
   */
  IncidenceList() : edge(NULL), next(NULL) {}

  /*!
   * \brief Destruktor obiektu typu IncidenceList.
   *
   * Destruktor obiektu typu IncidenceList.
   *
   * \pre Element listy istnieje.
   * \post Usuwa element listy.
   */
  ~IncidenceList() { delete next; }
};

/*!
 * Zrodla:
 * https://en.wikipedia.org/wiki/Adjacency_list
 * https://www.khanacademy.org/computing/computer-science/algorithms/graph-representation/a/representing-graphs
 * https://stackabuse.com/graphs-in-java-representing-graphs-in-code/
 */
class nlistgraph : public elistgraph // definicja listy sasiedztwa (neighborhood_list graph)
{
  IncidenceList *ListOfEdges;

public:
  /*!
   * \brief Funkcje umozliwiajace kontrolowany dostep do pol klasy.
   *
   * Funkcje umozliwiajace kontrolowany dostep do pol klasy.
   * \param[in] brak
   *
   * \pre Wskaznik na obiekt typu nlistgraph nie moze miec watosci NULL.
   * \post brak
   * \retval Odpowiednie pole klasy
   */
  IncidenceList *getListOfEdges()  const { return ListOfEdges; }
  IncidenceList *&setListOfEdges()       { return ListOfEdges; }

  void printgraph() const; //wyswietl graf
  void insertedge(int istart, int weight_value, int iend, int iedge); // wstawia krawedz
  void fillgraph(int shift, int range); // wypelnia graf
  void makeInput(int startV) const; // zapisuje graf do pliku
  explicit nlistgraph(int nov, double pod); // Konstruktor parametryczny
  explicit nlistgraph(int nov, int noe); // Konstruktor parametryczny

  /*!
   * \brief Konstruktor bezparametryczny obiektu typu nlistgraph.
   *
   * Konstruktor bezparametryczny obiektu typu nlistgraph.
   *
   * \pre brak
   * \post Tworzy liste krawedzi.
   */
  nlistgraph(){};

  /*!
   * \brief Destruktor obiektu typu nlistgraph.
   *
   * Destruktor obiektu typu nlistgraph.
   *
   * \pre Graf istnieje.
   * \post Usuwa liste sasiedztwa.
   */
  ~nlistgraph() { delete[] ListOfEdges; }

};

#endif
