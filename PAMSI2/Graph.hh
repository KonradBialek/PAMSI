#ifndef GRAPH_HH
#define GRAPH_HH

class Edge  // definicja wierzcholka jako magazynu na dane
{
  int start, end, weight;

public: 
  /*!
   * \brief Funkcje umozliwiajace kontrolowany dostep do pol klasy.            
   *
   * Funkcje umozliwiajace kontrolowany dostep do pol klasy.
   * \param[in] brak
   *
   * \pre Wskaznik na obiekt typu Edge nie moze miec watosci NULL.
   * \post brak
   * \retval Odpowiednie pole klasy
   */
  const int getstart()  const { return start; }
  int &setstart()             { return start; }
  const int getend()    const { return end; }
  int &setend()               { return end; }
  const int getweight() const { return weight; }
  int &setweight()            { return weight; }

  /*!
   * \brief Konstruktor parametryczny obiektu typu Edge.
   *
   * Konstruktor parametryczny obiektu typu Edge.
   * \param[in] istart - wierzcholek poczatkowy,
   * \param[in] iend - wierzcholek koncowy,
   * \param[in] weight_value - waga krawedzi.
   *
   * \pre brak
   * \post Tworzy wierzcholek.
   */
  explicit Edge(int istart, int iend, double weight_value) 
          : start(istart), end(iend), weight(weight_value) {}

  /*!
   * \brief Konstruktor bezparametryczny obiektu typu Edge.
   *
   * Konstruktor bezparametryczny obiektu typu Edge.
   *
   * \pre brak
   * \post Tworzy wierzcholek.
   */
  Edge() {}

  /*!
   * \brief Destruktor obiektu typu Edge.
   *
   * Destruktor obiektu typu Edge.
   *
   * \pre brak
   * \post Niszczy wierzcholek.
   */
  ~Edge() {}
};

/*!
 * Zrodla:
 * https://www.khanacademy.org/computing/computer-science/algorithms/graph-representation/a/representing-graphs
 * https://stackabuse.com/graphs-in-java-representing-graphs-in-code/
 */
class Graph // definicja szkieletu grafu (tylko parametry pojemosciowe grafu)
{ 
  int n_Verticles, n_Edges;
  double v_Density;

public:
  /*!
   * \brief Funkcje umozliwiajace kontrolowany dostep do pol klasy.
   *
   * Funkcje umozliwiajace kontrolowany dostep do pol klasy.
   * \param[in] brak
   *
   * \pre Wskaznik na obiekt typu Graph nie moze miec watosci NULL.
   * \post brak
   * \retval Odpowiednie pole klasy
   */
  const int getVerticles()  const { return n_Verticles; }
  int &setVerticles()             { return n_Verticles; }
  const int getEdges()      const { return n_Edges; }
  int &setEdges()                 { return n_Edges; }
  const double getDensity() const { return v_Density; }
  double &setDensity()            { return v_Density; }

  /*!
   * \brief Funkcje wirualne umozliwiajace operacje na obiekcie.
   *
   * Funkcje wirualne umozliwiajace operacje na obiekcie.
   * Dokladny opis funkcji przy ich zawartosci w klassach pochodnych
   */
  virtual void printgraph() const = 0; // wyswietla graf
  virtual void insertedge(int istart, int weight_value, int iend, int iedge) = 0; 
  //wstawia krawedz
  virtual bool connection_exist(int start, int end) const = 0; // sprawdza czy istnieje polaczenie
  virtual void fillgraph(int shift, int range) = 0; // wypelnia graf
  virtual void is_open(std::ofstream &file) const = 0; // otwiera plik do zapisu
  virtual void makeInput(int startV) const = 0; // zapisuje graf do pliku
  virtual void makeOutput(int **data, int startV, std::ofstream &file) const = 0; 
  // zapisuje wynik algorytmu do pliku

  /*!
   * \brief Konstruktor parametryczny obiektu typu Graph.
   *
   * Konstruktor parametryczny obiektu typu Graph.
   * \param[in] nov - ilosc wierzcholkow (number of verticles),
   * \param[in] noe - ilosc krawedzi (number of edges),
   * \param[in] vod - gestosc grafu (value of density).
   *
   * \pre brak
   * \post Tworzy graf.
   */
  explicit Graph(int nov, int noe, double vod) : n_Verticles(nov), n_Edges(noe), v_Density(vod) {} 
                                                   // number of verticles, edges; value of density

  /*!
   * \brief Konstruktor bezparametryczny obiektu typu Graph.
   *
   * Konstruktor bezparametryczny obiektu typu Graph.
   *
   * \pre brak
   * \post Tworzy graf.
   */
  Graph(){}   

  /*!
   * \brief Destruktor obiektu typu Graph.
   *
   * Destruktor obiektu typu Graph.
   *
   * \pre brak
   * \post Usuwa graf.
   */
  virtual ~Graph(){} // destruktor obiektu
                          
};

#endif
