#include "Bellman_Ford_alg.hh"

using namespace std;

/*!
 * \brief Algorytm Bellmana-Forda (algorytm szukania najkrotszej sciezki w grafie jako liscie 
 *        krawedzi).
 *
 * Algorytm Bellmana-Forda. Inicjuje odleglosci wierzcholkow od wierzcholka startowego jako
 * numeric_limits<int>::max() / 2 i poprzedników wierzcholkow jako -1. Znajduje najkrotsza sciezke
 * z wierzcholka startowego do kazdego wierzcholka. Sprawdza czy sciezka istnieje dla kazdego
 * wierzcholka. Sprawdza obecnosc cykli o negatywnej wadze. Zwraca dane wynikowe w postaci tablicy.
 * Zrodla:
 * https://en.wikipedia.org/wiki/Bellman%E2%80%93Ford_algorithm
 * https://pl.wikipedia.org/wiki/Algorytm_Bellmana-Forda
 * \param[in] graph - wskaznik na graf typu elistgraph,
 * \param[in] startV - wierzcholek startowy.
 * 
 * \pre Wskaznik na obiekt typu elistgraph nie moze miec watosci NULL.
 * \post Generuje tablice z wynikiem dzialania algoytmu.
 * \retval Tablica z wynikiem dzialania algoytmu
 */
int **Bellman_Ford_alg(elistgraph *graph, int startV) //szukanie sciezki na liscie krawedzi
{
  int **data = new int *[2];
  Edge *tmp;
  data[0] = new int[graph->getVerticles()];
  data[1] = new int[graph->getVerticles()];

  // 1. inicjowanie odleglosci i poprzednikow
  for (int istart = 0; istart < graph->getVerticles(); istart++)
  {
    data[0][istart] = numeric_limits<int>::max() / 2; // odleglosc jako max/2 (nieskonczonosc)
    data[1][istart] = -1;                             // poprzednik jako -1 (nieokreslony)
  }

  data[0][startV] = 0; // dystans zrodla do zrodla = 0

  // 2. szukanie sciezki - relaksacja
  for (int i = 1; i < graph->getVerticles(); i++) // |V|−1 powtorzen
    for (int iedge = 0; iedge < graph->getEdges(); iedge++)
    {
      tmp = &graph->getedges()[iedge];
      if (data[0][tmp->getstart()] + tmp->getweight() < data[0][tmp->getend()])
      { // gdy mozliwa do osiagniecia sciezka jest krotsza od aktualnie ustalonej
        data[0][tmp->getend()] = data[0][tmp->getstart()] + tmp->getweight(); // nowa dlugosc
        data[1][tmp->getend()] = tmp->getstart(); // nowy poprzednik
      }
    }

  // 3. Czy sciezka istnieje
  if (graph->getDensity() != 1)
    for (int i = 0; i < graph->getVerticles(); i++)
      if (data[1][i] < 0 && i != startV) 
        // gdy poprzednik nie istnieje i to nie jest wierzcholek startowy
        cout << "Path from Node " << startV << " to Node " << i << " does not exist." << endl;

  // 4. Czy cykle o negatywnej wadze
  for (int iedge = 0; iedge < graph->getEdges(); iedge++)
  {
    tmp = &graph->getedges()[iedge];
    if (data[0][tmp->getstart()] + tmp->getweight() < data[0][tmp->getend()])
    { // gdy mozliwa do osiagniecia sciezka nadal jest krotsza od aktualnie ustalonej
      cout << "Graph contains a negative-weight cycle" << endl;
      return data; // gdy wystapil cykl o negatywnej wadze nie wyswietla sie wielokrotnie
    }
  }
  return data;
}

/*!
 * \brief Algorytm Bellmana-Forda (algorytm szukania najkrotszej sciezki w grafie jako liscie 
 *        sasiedztwa).
 *
 * Algorytm Bellmana-Forda. Inicjuje odleglosci wierzcholkow od wierzcholka startowego jako
 * numeric_limits<int>::max() / 2 i poprzedników wierzcholkow jako -1. Znajduje najkrotsza sciezke
 * z wierzcholka startowego do kazdego wierzcholka. Sprawdza czy sciezka istnieje dla kazdego
 * wierzcholka. Sprawdza obecnosc cykli o negatywnej wadze. Zwraca dane wynikowe w postaci tablicy.
 * Zrodla:
 * https://en.wikipedia.org/wiki/Bellman%E2%80%93Ford_algorithm
 * https://pl.wikipedia.org/wiki/Algorytm_Bellmana-Forda
 * \param[in] graph - wskaznik na graf typu nlistgraph,
 * \param[in] startV - wierzcholek startowy.
 * 
 * \pre Wskaznik na obiekt typu nlistgraph nie moze miec watosci NULL.
 * \post Generuje tablice z wynikiem dzialania algoytmu.
 * \retval Tablica z wynikiem dzialania algoytmu
 */
int **Bellman_Ford_alg(nlistgraph *graph, int startV) //szukanie scierzki na liscie sasiedztwa
{
  int **data = new int *[2];
  IncidenceList *tmp;
  data[0] = new int[graph->getVerticles()];
  data[1] = new int[graph->getVerticles()];

  // 1. inicjowanie odleglosci i poprzednikow
  for (int istart = 0; istart < graph->getVerticles(); istart++)
  {
    data[0][istart] = numeric_limits<int>::max() / 2; // odleglosc jako max/2 (nieskonczonosc)
    data[1][istart] = -1;                             // poprzednik jako -1 (nieokreslony)
  }

  data[0][startV] = 0; // dystans zrodla do zrodla = 0

  // 2. szukanie sciezki - relaksacja
  for (int j = 1; j < graph->getVerticles(); j++) // |V|−1 powtorzen
    for (int i = 0; i < graph->getVerticles(); i++)
    {
      tmp = &graph->getListOfEdges()[i];
      while (tmp != 0)
      {
        if (tmp->getedge() != NULL)
          if (tmp->getedge()->getstart() != tmp->getedge()->getend())
            if (data[0][tmp->getedge()->getstart()] + tmp->getedge()->getweight() < 
                data[0][tmp->getedge()->getend()])
            { // gdy mozliwa do osiagniecia sciezka jest krotsza od aktualnie ustalonej
              data[0][tmp->getedge()->getend()] = data[0][tmp->getedge()->getstart()] + 
              tmp->getedge()->getweight();
              // nowa dlugosc
              data[1][tmp->getedge()->getend()] = tmp->getedge()->getstart(); // nowy poprzednik
            }
        tmp = tmp->getnext();
      }
    }
  
  // 3. Czy sciezka istnieje
  if (graph->getDensity() != 1)
    for (int i = 0; i < graph->getVerticles(); i++)
      if (data[1][i] < 0 && i != startV)
        // gdy poprzednik nie istnieje i to nie jest wierzcholek startowy
        cout << "Path from Node " << startV << " to Node " << i << " does not exist." << endl;

  // 4. Czy cykle o negatywnej wadze
  for (int i = 0; i < graph->getVerticles(); i++) 
  {
    tmp = &graph->getListOfEdges()[i];
    while (tmp != 0)
    {
      if (tmp->getedge() != NULL)
        if (data[0][tmp->getedge()->getstart()] + tmp->getedge()->getweight() < 
            data[0][tmp->getedge()->getend()])
        { // gdy mozliwa do osiagniecia sciezka nadal jest krotsza od aktualnie ustalonej
          cout << "Graph contains a negative-weight cycle" << endl;
          return data; // gdy wystapil cykl o negatywnej wadze nie wyswietla sie wielokrotnie
        }
      tmp = tmp->getnext();
    }
  }
  return data;
}

/*!
 * \brief Algorytm Bellmana-Forda (algorytm szukania najkrotszej sciezki w grafie jako macierzy 
 *        sasiedztwa).
 *
 * Algorytm Bellmana-Forda. Inicjuje odleglosci wierzcholkow od wierzcholka startowego jako
 * numeric_limits<int>::max() / 2 i poprzedników wierzcholkow jako -1. Znajduje najkrotsza sciezke
 * z wierzcholka startowego do kazdego wierzcholka. Sprawdza czy sciezka istnieje dla kazdego
 * wierzcholka. Sprawdza obecnosc cykli o negatywnej wadze. Zwraca dane wynikowe w postaci tablicy.
 * Zrodla:
 * https://en.wikipedia.org/wiki/Bellman%E2%80%93Ford_algorithm
 * https://pl.wikipedia.org/wiki/Algorytm_Bellmana-Forda
 * \param[in] graph - wskaznik na graf typu nmatrixgraph,
 * \param[in] startV - wierzcholek startowy.
 * 
 * \pre Wskaznik na obiekt typu nmatrixgraph nie moze miec watosci NULL.
 * \post Generuje tablice z wynikiem dzialania algoytmu.
 * \retval Tablica z wynikiem dzialania algoytmu
 */
int **Bellman_Ford_alg(nmatrixgraph *graph, int startV) //szukanie scierzki na macierzy sasiedztwa
{
  int **data = new int *[2];
  data[0] = new int[graph->getVerticles()];
  data[1] = new int[graph->getVerticles()];
  IncidenceMatrix *tmp;

  // 1. inicjowanie odleglosci i poprzednikow
  for (int istart = 0; istart < graph->getVerticles(); istart++)
  {
    data[0][istart] = numeric_limits<int>::max() / 2; // odleglosc jako max/2 (nieskonczonosc)
    data[1][istart] = -1;                             // poprzednik jako -1 (nieokreslony)
  }

  data[0][startV] = 0; // dystans zrodla do zrodla = 0

  // 2. szukanie sciezki - relaksacja
  for (int j = 1; j < graph->getVerticles(); j++) // |V|−1 powtorzen
    for (int istart = 0; istart < graph->getVerticles(); istart++)
      for (int iend = 0; iend < graph->getVerticles(); iend++)
      {
        tmp = &graph->getMatrixOfEdges()[istart][iend];
        if (tmp->getedge() != NULL)
        {
          if (data[0][tmp->getedge()->getstart()] + tmp->getedge()->getweight() < 
              data[0][tmp->getedge()->getend()])
          { // gdy mozliwa do osiagniecia sciezka jest krotsza od aktualnie ustalonej
            data[0][tmp->getedge()->getend()] = data[0][tmp->getedge()->getstart()] + 
            tmp->getedge()->getweight();
            // nowa dlugosc
            data[1][tmp->getedge()->getend()] = tmp->getedge()->getstart(); // nowy poprzednik
          }
        }
      }
      
  // 3. Czy sciezka istnieje
  if (graph->getDensity() != 1)
    for (int i = 0; i < graph->getVerticles(); i++)
      if (data[1][i] < 0 && i != startV)
        // gdy poprzednik nie istnieje i to nie jest wierzcholek startowy
        cout << "Path from Node " << startV << " to Node " << i << " does not exist." << endl;

  // 4. Czy cykle o negatywnej wadze
  for (int istart = 0; istart < graph->getVerticles(); istart++)
    for (int iend = 0; iend < graph->getVerticles(); iend++)
    {
      tmp = &graph->getMatrixOfEdges()[istart][iend];
      if (tmp->getedge() != NULL)
        if (data[0][tmp->getedge()->getstart()] + tmp->getedge()->getweight() < 
            data[0][tmp->getedge()->getend()])
        { // gdy mozliwa do osiagniecia sciezka nadal jest krotsza od aktualnie ustalonej
          cout << "Graph contains a negative-weight cycle" << endl;
          return data; // gdy wystapil cykl o negatywnej wadze nie wyswietla sie wielokrotnie
        }
    }
  return data;
}
