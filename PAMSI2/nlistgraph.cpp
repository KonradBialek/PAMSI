#include "nlistgraph.hh"

using namespace std;

/*!
 * \brief Wstawia krawedz (jako wskaznik) do listy.
 *
 * Wstawia krawedz (jako wskaznik) do listy.
 * \param[in] arg - wstawiana krawedz.
 *
 * \pre Wskaznik na obiekt typu IncidenceList nie moze miec watosci NULL.
 * \post  Wstawia krawedz do listy.
 */
void IncidenceList::push(IncidenceList *arg)
{
  IncidenceList *tmp = this;
  if (this->edge == NULL) 
  { // gdy z wierzcholka nie wychodza krawedzie
    this->edge = arg->edge;
    this->next = arg->next;
    arg->edge = NULL;
    arg->next = NULL;
  }
  else
  { // gdy juz istnieja jakies krawedzie wychodzace z wierzcholka 
    while (tmp->next != NULL) 
      tmp = tmp->next;
    tmp->next = arg;
    arg = NULL;
  }
  delete arg;
}

/*!
 * \brief Wyswietla graf w terminalu.
 *
 * Wyswietla graf w terminalu.
 * \param[in] brak
 *
 * \pre Wskaznik na obiekt typu nlistgraph nie moze miec watosci NULL.
 * \post Wyswietla graf.
 */
void nlistgraph::printgraph() const //wyswietl graf
{ // inny format niz opis zapisu do pliku w instrukcji
  int istart;
  IncidenceList *tmp;
  for (istart = 0; istart < getVerticles(); istart++)
  {
    cout << setw(5) << fixed << istart << ": "; // kazdy wierzcholek poczatkowy
    tmp = &this->ListOfEdges[istart];
    while (tmp != 0)
    {
      if (tmp->getedge() != NULL)
        if (tmp->getedge()->getstart() == istart) //polaczenia z innymi wierzcholkami i ich waga
          cout << setw(5)  << fixed << tmp->getedge()->getstart() << "-"
               << setw(11) << fixed << tmp->getedge()->getweight() << "-"
               << setw(5)  << fixed << tmp->getedge()->getend() << ";   ";
      tmp = tmp->getnext();
    }
    cout << endl;
  }
  cout << endl;
}

/*!
 * \brief Wstawia krawedz do grafu jako listy sasiedztwa.
 *
 * Wstawia krawedz do grafu jako listy sasiedztwa.
 * \param[in] istart - wierzcholek poczatkowy,
 * \param[in] weight_value - waga krawedzi,
 * \param[in] iend - wierzcholek koncowy,
 * \param[in] iedge - numer krawedzi.
 * 
 * \pre Wskaznik na obiekt typu nlistgraph nie moze miec watosci NULL.
 * \post Wstawia krawedz.
 */
void nlistgraph::insertedge(int istart, int weight_value, int iend, int iedge)
{
  // kazda krawedz musi miec ustawione poczatek, koniec i wartosc
  setedges()[iedge].setstart() = istart;
  setedges()[iedge].setend() = iend;
  setedges()[iedge].setweight() = weight_value;

  // dodanie stworzonego wierzcholka do listy 
  Edge *newedge = &getedges()[iedge];
  IncidenceList *new_edge = new IncidenceList(newedge);
  this->ListOfEdges[istart].push(new_edge);
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
 * \pre Wskaznik na obiekt typu nlistgraph nie moze miec watosci NULL.
 * \post Wypelnia graf.
 */
void nlistgraph::fillgraph(int shift, int range)
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
void nlistgraph::makeInput(int startV) const
{
  ofstream file("InputMadeLIST.txt");
  is_open(file); // zapis zgodnie z instrukcja przy pomocy listy sasiedztwa
  file << setw(5)  << fixed << getEdges() << " "
       << setw(5)  << fixed << getVerticles() << " "
       << setw(11) << fixed << startV << endl;
  IncidenceList *tmp;
  for (int istart = 0; istart < getVerticles(); istart++)
  {
    tmp = &this->ListOfEdges[istart];
    while (tmp != 0)
    {
      if (tmp->getedge()->getstart() == istart) //polaczenia z innymi wierzcholkami i ich waga
        file << setw(5)  << fixed << tmp->getedge()->getstart() << " "
             << setw(5)  << fixed << tmp->getedge()->getend() << " "
             << setw(11) << fixed << tmp->getedge()->getweight() << endl;
      tmp = tmp->getnext();
    }
  }
  file.close();
}

/*!
 * \brief Konstruktor parametryczny obiektu typu nlistgraph.
 *
 * Konstruktor parametryczny obiektu typu nlistgraph.
 * \param[in] nov - ilosc wierzcholkow (number of verticles),
 * \param[in] pod - gestosc grafu (percent of density).
 *
 * \pre brak
 * \post Tworzy graf jako liste sasiedztwa.
 */
nlistgraph::nlistgraph(int nov, double pod) : elistgraph(nov, pod), 
                                              ListOfEdges(new IncidenceList[nov])
{
  for (int i = 0; i < nov; i++)
  { // zerowanie zawartosci listy
    ListOfEdges[i].setedge() = NULL;
    ListOfEdges[i].setnext() = NULL;
  }
}

/*!
 * \brief Konstruktor parametryczny obiektu typu nlistgraph.
 *
 * Konstruktor parametryczny obiektu typu nlistgraph.
 * \param[in] nov - ilosc wierzcholkow (number of verticles),
 * \param[in] noe - ilosc krawedzi (number of edges).
 *
 * \pre brak
 * \post Tworzy graf jako liste sasiedztwa.
 */
nlistgraph::nlistgraph(int nov, int noe) : elistgraph(nov, noe), 
                                           ListOfEdges(new IncidenceList[nov])
{
  for (int i = 0; i < nov; i++)
  { // zerowanie zawartosci listy
    ListOfEdges[i].setedge() = NULL;
    ListOfEdges[i].setnext() = NULL;
  }
}
