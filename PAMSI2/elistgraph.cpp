#include "elistgraph.hh"
using namespace std;

/*!
 * \brief Wyswietla graf w terminalu.
 *
 * Wyswietla graf w terminalu.
 * \param[in] brak
 *
 * \pre Wskaznik na obiekt typu elistgraph nie moze miec watosci NULL.
 * \post Wyswietla graf.
 */
void elistgraph::printgraph() const //wyswietl graf
{ // inny format niz opis zapisu do pliku w instrukcji
  int istart, iedge;
  for (istart = 0; istart < getVerticles(); istart++)
  {
    cout << setw(5) << fixed << istart << ": "; // kazdy wierzcholek poczatkowy
    for (iedge = 0; iedge < getEdges(); iedge++)
      if (edges[iedge].getstart() == istart) //polaczenia z innymi wierzcholkami i ich waga
        cout << setw(5)  << fixed << edges[iedge].getstart() << "-"
             << setw(11) << fixed << edges[iedge].getweight() << "-"
             << setw(5)  << fixed << edges[iedge].getend() << ";   ";
    cout << endl;
  }
  cout << endl;
}

/*!
 * \brief Wstawia krawedz do grafu jako listy krawedzi.
 *
 * Wstawia krawedz do grafu jako listy krawedzi.
 * \param[in] istart - wierzcholek poczatkowy,
 * \param[in] weight_value - waga krawedzi,
 * \param[in] iend - wierzcholek koncowy,
 * \param[in] iedge - numer krawedzi.
 * 
 * \pre Wskaznik na obiekt typu elistgraph nie moze miec watosci NULL.
 * \post Wstawia krawedz.
 */
void elistgraph::insertedge(int istart, int weight_value, int iend, int iedge)
{
  // kazda krawedz musi miec ustawione poczatek, koniec i wartosc
  edges[iedge].setstart() = istart;
  edges[iedge].setweight() = weight_value;
  edges[iedge].setend() = iend;
}

/*!
 * \brief Sprawdza czy istnieje polaczenie miedzy podanymi wierzcholkami.
 *
 * Sprawdza czy istnieje polaczenie miedzy podanymi wierzcholkami.
 * \param[in] start - wierzcholek poczatkowy,
 * \param[in] end - wierzcholek koncowy.
 * 
 * \pre Wskaznik na obiekt typu elistgraph nie moze miec watosci NULL.
 * \post brak
 * \retval Czy polaczenie istnieje?
 */
bool elistgraph::connection_exist(int start, int end) const
{
  for (int iedge = 0; iedge < getEdges(); iedge++) //czy istnieje polaczenie miedzy wierzcholkami
    if (edges[iedge].getstart() == start && edges[iedge].getend() == end)
      return true;
  return false;
}

/*!
 * \brief Wypelnia graf krawedziami o losowych parametrach.
 *
 * Wypelnia graf krawedziami o losowych parametrach (gdy gestosc grafu wynosi 
 * 100% tylko waga krawedzi jset losowa). Nie dopuszcza wagi rownej 0 ani petli.
 * \param[in] shift -przesuniecie zakresu losowania w strone liczb ujemnych,
 * \param[in] range - zakres losowania (od 0).
 * 
 * \pre Wskaznik na obiekt typu elistgraph nie moze miec watosci NULL.
 * \post Wypelnia graf.
 */
void elistgraph::fillgraph(int shift, int range)
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
 * \brief Sprawdza czy plik do zapisu istnieje.
 *
 * Sprawdza czy plik do zapisu istnieje.
 * \param[in] file - uchwyt do pliku.
 * 
 * \pre Wskaznik na obiekt typu elistgraph nie moze miec watosci NULL.
 * \post Jezeli plik do zapisu nie istnieje zmyka program (blad krytyczny).
 */
void elistgraph::is_open(ofstream &file) const
{
  if (!file.is_open()) // czy otwarty
  {
    cerr << "The write access operation of output file" << endl
         << "has failed." << endl;
    exit(-4);
  }
}

/*!
 * \brief Zapisuje graf do pliku w postaci wejscioej do programu (zgodnie z instrukcja).
 *
 * Zapisuje graf do pliku w postaci wejscioej do programu (zgodnie z instrukcja).
 * \param[in] startV - wierzcholek startowy.
 * 
 * \pre Wskaznik na obiekt typu elistgraph nie moze miec watosci NULL.
 * \post Tworzy plik wejsciowy (o innej nazwie, aby nie nadpisac aktualnego pliku wejsciowego).
 */
void elistgraph::makeInput(int startV) const
{
  ofstream file("InputMadeEDGE.txt");
  is_open(file); // zapis zgodnie z instrukcja przy pomocy listy krawedzi
  file << setw(5)  << fixed << getEdges() << " "
       << setw(5)  << fixed << getVerticles() << " "
       << setw(11) << fixed << startV << endl;
  for (int iedge = 0; iedge < getEdges(); iedge++) //polaczenia z innymi wierzcholkami i ich waga
    file << setw(5)  << fixed << edges[iedge].getstart() << " "
         << setw(5)  << fixed << edges[iedge].getend() << " "
         << setw(11) << fixed << edges[iedge].getweight() << endl;
  file.close();
}

/*!
 * \brief Zapisuje wynik dzialania algorytmu zgodnie z instrukcja.
 *
 * Zapisuje wynik dzialania algorytmu zgodnie z instrukcja.
 * \param[in] data - tablica z wynikiem dzialania algoytmu,
 * \param[in] startV - wierzcholek startowy sciezki,
 * \param[in] file - uchwyt do pliku.
 * 
 * \pre Wskaznik na obiekt typu elistgraph nie moze miec watosci NULL.
 * \pre Uchwyt do pliku musi istniec.
 * \post Tworzy plik wyjsciowy o podanej w uchwycie do pliku nazwie.
 */
void elistgraph::makeOutput(int **data, int startV, ofstream &file) const
{
  // zapis w formie czaytelnej dla innych programow
  // wierzcholek startowy
  // nr. wierzcholka    waga sciezki     wierzcholki sciezki od startu do konca
  // gdy wierzcholek startowy to dlugosc sciezki wynosi 0, a gdy brak polaczenia odleglosc wynosi
  // numeric_limits<int>::max() / 2   (czyli 1073741823)

  int *tab = new int[getVerticles()]; 
  // getVerticles() na wypadek gdyby najkrotsza sciezka prowadzila przez wszystkie wierzcholki
  int j = 0, k = 0;

  //file << setw(5) << fixed << startV << endl; // Insrukcja nie mowi o osobnym zapisie wierzcholka
                                                // startowego, ale zachowalem polecenie zapisujace.
  for (int i = 0; i < getVerticles(); i++) // dla kazdego wierzcholka
  {
    file << setw(5) << fixed << i << setw(11) << fixed << data[0][i]; // wierzcholek i waga sciezki
    if (data[1][i] >= 0 || i == startV) //gdy poprzednik istnieje lub wierzcholek startowy
    {
      j = i;
      file << "        ";
      while (j != startV)
      {
        tab[k++] = j;
        j = data[1][j];
      }
      tab[k] = j;
      while (k >= 0) file << setw(5) << fixed << tab[k--]; // zapis sciezki
      k = 0;
    }
    file << endl;
  }
  file << endl;
  file.close();
  delete[] tab;
}
