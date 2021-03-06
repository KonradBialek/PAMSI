#include "nmatrixgraph.hh"

using namespace std;

/*!
 * \brief Wstawia krawedz (jako wskaznik) do macierzy.
 *
 * Wstawia krawedz (jako wskaznik) do macierzy.
 * \param[in] arg - wstawiana krawedz.
 *
 * \pre Wskaznik na obiekt typu IncidenceMatrix nie moze miec watosci NULL.
 * \post Wstawia krawedz do macierzy.
 */
void IncidenceMatrix::push(IncidenceMatrix *arg) //wstaw krawedz
{ // wstawia krawedz do macierzy
  this->edge = arg->edge;
  arg->edge = NULL;
  delete arg;
}

/*!
 * \brief Wyswietla graf w terminalu.
 *
 * Wyswietla graf w terminalu.
 * \param[in] brak
 *
 * \pre Wskaznik na obiekt typu nmatrixgraph nie moze miec watosci NULL.
 * \post Wyswietla graf.
 */
void nmatrixgraph::printgraph() const //wyswietl graf
{ // Teoretycznie warto graf w postaci macierzy wyswietlic jako macierz, ale bylo by to rozwiazanie 
  // nieczytelne juz dla 50 wierzcholkow w grafie, zdecydowano sie na prezentacje w postaci listy
  // jak w pozostalych implementacjach.

  // inny format niz opis zapisu do pliku w instrukcji
  int istart, iend;
  IncidenceMatrix *tmp;
  for (istart = 0; istart < getVerticles(); istart++)
  {
    cout << setw(5) << fixed << istart << ": "; // kazdy wierzcholek poczatkowy
    for (iend = 0; iend < getVerticles(); iend++)
    {
      tmp=&this->getMatrixOfEdges()[istart][iend];
      if (tmp->getedge() != NULL) //polaczenia z innymi wierzcholkami i ich waga
        cout << setw(5)  << fixed << tmp->getedge()->getstart() << "-"
             << setw(11) << fixed << tmp->getedge()->getweight() << "-"
             << setw(5)  << fixed << tmp->getedge()->getend() << ";   ";
    }
    cout << endl;
  }
  cout << endl;
}

/*!
 * \brief Wstawia krawedz do grafu jako macierzy sasiedztwa.
 *
 * Wstawia krawedz do grafu jako macierzy sasiedztwa.
 * \param[in] istart - wierzcholek poczatkowy,
 * \param[in] weight_value - waga krawedzi,
 * \param[in] iend - wierzcholek koncowy,
 * \param[in] iedge - numer krawedzi.
 * 
 * \pre Wskaznik na obiekt typu nmatrixgraph nie moze miec watosci NULL.
 * \post Wstawia krawedz.
 */
void nmatrixgraph::insertedge(int istart, int weight_value, int iend, int iedge) //wstaw krawedz
{
  IncidenceMatrix *tmp;
  // kazda krawedz musi miec ustawione poczatek, koniec i wartosc
  setedges()[iedge].setstart() = istart;
  setedges()[iedge].setend() = iend;
  setedges()[iedge].setweight() = weight_value;

  // dodanie stworzonego wierzcholka do macierzy 
  tmp = &this->getMatrixOfEdges()[istart][iend];
  Edge *newedge = &getedges()[iedge];
  IncidenceMatrix *new_edge = new IncidenceMatrix(newedge);
  tmp->push(new_edge);
  new_edge = NULL;
  delete new_edge;
}

/*!
 * \brief Wypelnia graf krawedziami o losowych parametrach.
 *
 * Wypelnia graf krawedziami o losowych parametrach (gdy gestosc grafu wynosi 
 * 100% tylko waga krawedzi jset losowa). Nie dopuszcza wagi rownej 0 ani petli.
 * \param[in] shift - przesuniecie zakresu losowania w strone liczb ujemnych,
 * \param[in] range - zakres losowania (od 0).
 * 
 * \pre Wskaznik na obiekt typu nmatrixgraph nie moze miec watosci NULL.
 * \post Wypelnia graf.
 */
void nmatrixgraph::fillgraph(int shift, int range) //wypelnij graf
{
  // w programie zaklada sie ze nie istnieja wagi 0, ani petle 
  int iedge = 0, weight_value;
  int startV, endV;
  if (getDensity() == 1) // teoretycznie mozna losowac, ale wylosowanie ostatnich
  {                      // polaczen do stworzenia trwa dlugo
    for (int istart = 0; istart < getVerticles(); istart++)
      for (int iend = 0; iend < getVerticles(); iend++)
        if (istart != iend) // gdy to nie jest petla
        {
          weight_value = rand() % range - shift;
          while (!weight_value) //nie dopuszcza się wagi 0
            weight_value = rand() % range - shift;
          insertedge(istart, weight_value, iend, iedge++);
        }
  }
  else
    while (iedge < getEdges())
    {
      startV = rand() % getVerticles(); // losowanie wierzcholkow
      endV = rand() % getVerticles();
      if (!connection_exist(startV, endV) && startV != endV) // gdy to nie jest petla
      {
        weight_value = rand() % range - shift;
        while (!weight_value) //nie dopuszcza się wagi 0
          weight_value = rand() % range - shift;
        insertedge(startV, weight_value, endV, iedge++);
      }
    }
}

/*!
 * \brief Zapisuje graf do pliku w postaci wejscioej do programu (zgodnie z instrukcja).
 *
 * Zapisuje graf do pliku w postaci wejscioej do programu (zgodnie z instrukcja).
 * \param[in] startV - wierzcholek startowy.
 * 
 * \pre Wskaznik na obiekt typu nlistgraph nie moze miec watosci NULL.
 * \post Tworzy plik wejsciowy (o innej nazwie, aby nie nadpisac aktualnego pliku wejsciowego).
 */
void nmatrixgraph::makeInput(int startV) const
{
  ofstream file("InputMadeMATRIX.txt");
  is_open(file); // zapis zgodnie z instrukcja przy pomocy macierzy sasiedztwa 
  IncidenceMatrix *tmp;
  file << setw(5)  << fixed << getEdges() << " "
       << setw(5)  << fixed << getVerticles() << " "
       << setw(11) << fixed << startV << endl;
  for (int istart = 0; istart < getVerticles(); istart++)
    for (int iend = 0; iend < getVerticles(); iend++)
    {
      tmp=&this->getMatrixOfEdges()[istart][iend];
      if (tmp->getedge() != NULL) //polaczenia z innymi wierzcholkami i ich waga
        file << setw(5)  << fixed << tmp->getedge()->getstart() << " "
             << setw(5)  << fixed << tmp->getedge()->getend() << " "
             << setw(11) << fixed << tmp->getedge()->getweight() << endl;
    } // w przeciwienstwie do obu implementacji na listach zapis macierzy jest uszeregowany
      // od wierzcholka koncowego o najmniejszym indeksie do tego o najwiekszym indeksie 
  file.close();
}

/*!
 * \brief Konstruktor parametryczny obiektu typu nmatrixgraph.
 *
 * Konstruktor parametryczny obiektu typu nmatrixgraph.
 * \param[in] nov - ilosc wierzcholkow (number of verticles),
 * \param[in] pod - gestosc grafu (percent of density).
 *
 * \pre brak
 * \post Tworzy graf jako macierz sasiedztwa.
 */
nmatrixgraph::nmatrixgraph(int nov, double pod) : elistgraph(nov, pod), 
                                                  MatrixOfEdges(new IncidenceMatrix *[nov])
{
  for (int i = 0; i < nov; i++)
    MatrixOfEdges[i] = new IncidenceMatrix[nov];

  for (int row = 0; row < nov; row++) // zerowanie zawartosci macierzy
    for (int column = 0; column < nov; column++)
      MatrixOfEdges[row][column].setedge() = NULL;
}

/*!
 * \brief Konstruktor parametryczny obiektu typu nmatrixgraph.
 *
 * Konstruktor parametryczny obiektu typu nmatrixgraph.
 * \param[in] nov - ilosc wierzcholkow (number of verticles),
 * \param[in] noe - ilosc krawedzi (number of edges).
 *
 * \pre brak
 * \post Tworzy graf jako macierz sasiedztwa.
 */
nmatrixgraph::nmatrixgraph(int nov, int noe) : elistgraph(nov, noe), 
                                               MatrixOfEdges(new IncidenceMatrix *[nov])
{
  for (int i = 0; i < nov; i++)
    MatrixOfEdges[i] = new IncidenceMatrix[nov];

  for (int row = 0; row < nov; row++) // zerowanie zawartosci macierzy
    for (int column = 0; column < nov; column++)
      MatrixOfEdges[row][column].setedge() = NULL;
}

/*!
 * \brief Destruktor obiektu typu nlistgraph.
 *
 * Destruktor obiektu typu nlistgraph.
 *
 * \pre Graf istnieje.
 * \post Usuwa macierz sasiedztwa.
 */
nmatrixgraph::~nmatrixgraph()
{
  for (int i = 0; i < getVerticles(); i++)
    delete[] MatrixOfEdges[i];
  delete[] MatrixOfEdges;
}