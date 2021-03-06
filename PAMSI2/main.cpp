#include <string>
#include "Bellman_Ford_alg.hh"

using namespace std;
using namespace chrono;

class graphs //pomocnicza klasa do przechowywania danych z pliku
{
  elistgraph *graph1;
  nlistgraph *graph2;
  nmatrixgraph *graph3;
  int startV;

public:
  /*!
   * \brief Funkcje umozliwiajace kontrolowany dostep do pol klasy.
   *
   * Funkcje umozliwiajace kontrolowany dostep do pol klasy.
   * \param[in] brak
   *
   * \pre Wskaznik na obiekt typu graphs nie moze miec watosci NULL.
   * \post brak
   * \retval Odpowiednie pole klasy
   */
  elistgraph *getgraph1()    { return graph1; }
  elistgraph *&setgraph1()   { return graph1; }
  nlistgraph *getgraph2()    { return graph2; }
  nlistgraph *&setgraph2()   { return graph2; }
  nmatrixgraph *getgraph3()  { return graph3; }
  nmatrixgraph *&setgraph3() { return graph3; }
  const int getstartV()      { return startV; }
  int &setstartV()           { return startV; }

  /*!
   * \brief Konstruktor parametryczny obiektu typu graphs.
   *
   * Konstruktor parametryczny obiektu typu graphs.
   * \param[in] graph1 - wskaznik na graf typu elistgraph,
   * \param[in] graph2 - wskaznik na graf typu nlistgraph,
   * \param[in] graph3 - wskaznik na graf typu nmatrixgraph,
   * \param[in] startV - wierzcholek startowy.
   * 
   * \pre Wskaznik na obiekt typu elistgraph nie moze miec watosci NULL.
   * \pre Wskaznik na obiekt typu nlistgraph nie moze miec watosci NULL.
   * \pre Wskaznik na obiekt typu nmatrixgraph nie moze miec watosci NULL.
   * \post Tworzy trzy grafy wedlug kazdej z implementacji.
   * \post Ustawia wierzcholek startowy dla tej grupy grafow.
   */
  graphs(elistgraph *graph1, nlistgraph *graph2, nmatrixgraph *graph3, int startV)
      : graph1(graph1), graph2(graph2), graph3(graph3), startV(startV) {}

  /*!
   * \brief Destruktor obiektu typu graphs.
   *
   * Destruktor obiektu typu graphs.
   *
   * \pre Grafy znajdujace sie w tym obiekcie istnieja.
   * \post Usuwa grafy zawarte w obiekcie.
   */
  ~graphs(){ delete graph1; delete graph2; delete graph3;}
};

/*!
 * \brief Sprawdza czy plik do zapisu istnieje.
 *
 * Sprawdza czy plik do zapisu istnieje.
 * \param[in] file - uchwyt do pliku.
 * 
 * \pre brak
 * \post Jezeli plik do zapisu nie istnieje zmyka program (blad krytyczny).
 */
void is_open(ofstream &file)
{
  if (!file.is_open()) // czy otwarty
  {
    cerr << "The write access operation of output file" << endl
         << "has failed." << endl;
    exit(-1);
  }
}

/*!
 * \brief Sprawdza czy plik do odczytu istnieje.
 *
 * Sprawdza czy plik do odczytu istnieje.
 * \param[in] file - uchwyt do pliku.
 * 
 * \pre brak
 * \post Jezeli plik do odczytu nie istnieje zmyka program (blad krytyczny).
 */
void is_open(ifstream &file)
{
  if (!file.is_open()) // czy otwarty
  {
    cerr << "The read access operation of input file" << endl
         << "has failed." << endl;
    exit(-2);
  }
}

/*!
 * \brief Odczytuje dane z pliku i zapisuje je do grafow.
 *
 * Odczytuje dane z pliku i zapisuje je do grafow.
 * \param[in] brak
 * 
 * \pre brak
 * \post Obiekt zawierajacy grafy wskazuje na istniejace dane (nie wskaznik NULL)
 * \retval Obiekt zawierajacy wskazniki na grafy.
 */
graphs *readInput()
{
  ifstream file("Input.txt");
  is_open(file); //czy plik jest otwarty

  int n_Verticles, n_Edges, startV;
  int start, end, weight;
  file >> n_Edges >> n_Verticles >> startV;

  // stworzenie grafow i magazynu na nie
  elistgraph *graph1 = new elistgraph(n_Verticles, n_Edges);
  nlistgraph *graph2 = new nlistgraph(n_Verticles, n_Edges);
  nmatrixgraph *graph3 = new nmatrixgraph(n_Verticles, n_Edges);
  graphs *Obj = new graphs(graph1, graph2, graph3, startV);

  for (int iedge = 0; iedge < n_Edges; iedge++)
  { // wypelnienie grafow
    file >> start >> end >> weight;
    graph1->insertedge(start, weight, end, iedge);
    graph2->insertedge(start, weight, end, iedge);
    graph3->insertedge(start, weight, end, iedge);
  }
  file.close();
  return Obj;
}

/*!
 * \brief Przeprowadza operacje na plikach opisane w instrukcji oraz szukanie najkrotszej sciezki 
 *        w grafie z pliku.
 *
 * Przeprowadza operacje na plikach opisane w instrukcji oraz szukanie najkrotszej sciezki w grafie
 * z pliku. Kolejno dla kazdej implementacji grafu:
 * Wczytanie danych do grafow;
 * Szukanie najkrotszej sciezki od podanego wierzcholka startowwego;
 * Otwieranie pliku do zapisu wyniku algorytmu;
 * Zapis wyniku algorytmu do pliku;
 * Zapis grafu do pliku w sposob umozliwiajacy wprowadzenie zapisanych danych ponownie do pragramu;
 * Usuniecie danych.
 * Na koncu usuwa grafy.
 * \param[in] brak
 * 
 * \pre brak
 * \post Obiekt zawierajacy grafy wskazuje na istniejace dane (nie wskaznik NULL)
 */
void FileManaging()
{
  graphs *Obj = readInput();
  int **data;

  // dla grafu jako listy krawedzi
  //Obj->getgraph1()->printgraph();  // wyswietlanie pozostawione dla prezentacji poprawnosci
  data = Bellman_Ford_alg(Obj->getgraph1(), Obj->getstartV());
  ofstream file0("OutputMadeEDGE.txt");
  is_open(file0);
  Obj->getgraph1()->makeOutput(data, Obj->getstartV(), file0);
  Obj->getgraph1()->makeInput(Obj->getstartV());
  delete[] data[0]; delete[] data[1]; delete[] data;
  cout << endl;

  // dla grafu jako listy sasiedztwa
  //Obj->getgraph2()->printgraph();  // wyswietlanie pozostawione dla prezentacji poprawnosci
  data = Bellman_Ford_alg(Obj->getgraph2(), Obj->getstartV());
  ofstream file1("OutputMadeLIST.txt");
  is_open(file1);
  Obj->getgraph2()->makeOutput(data, Obj->getstartV(), file1);
  Obj->getgraph2()->makeInput(Obj->getstartV());
  delete[] data[0]; delete[] data[1]; delete[] data;
  cout << endl;

  // dla grafu jako macierzy sasiedztwa
  //Obj->getgraph3()->printgraph();  // wyswietlanie pozostawione dla prezentacji poprawnosci
  data = Bellman_Ford_alg(Obj->getgraph3(), Obj->getstartV());
  ofstream file2("OutputMadeMATRIX.txt");
  is_open(file2);
  Obj->getgraph3()->makeOutput(data, Obj->getstartV(), file2);
  Obj->getgraph3()->makeInput(Obj->getstartV());
  delete[] data[0]; delete[] data[1]; delete[] data;
  delete Obj;
  cout << endl;
  cout << "End of Part 2." << endl;

}

/*!
 * \brief Funkcja glowna.
 *
 * Funkcja glowna. Tworzy i otwiera plik na wyniki testow. W pierwszej czesci programu bada 
 * efektywnosc algorytmu Bellmana-Forda dla roznych parametrow wprowadzanych danych. Tworzy i 
 * wypelnia grafy wazone. Wykonuje algorytm szukania najkrotszej sciezki do kazdego wierzcholka
 * w grafie z wierzcholka startowego Usuwa dane wynikowe algorytmu Rejestruje czasy minimalne i 
 * maksymalne oraz wyznacza czas sredni poszczegolnych testow i zapisuje je do otwartego pliku. 
 * Wywoluje wykonanie drugiej czesci programu - operacje na grafie z pliku. Zamyka program.
 * \param[in] brak
 *
 * \pre Brak.
 * \post Generuje plik z wynikami testow oraz pliki z wynikami algorytmu i grafami dla kazdej z 
 *       implementacji grafu.
 * \retval 0 (gdy program przebiegnie pomyslnie), kod bledu -3 gdy program zostanie przerwany.
 */
int main()
{
  // pierwsza czesc programu
  int number_of_graphs = 100, index_of_method = 0, shift = 0, range = 500, startV, **data = NULL;
  // Nie nalezy ustawiac parametru range na wartosc 1073741823 lub wyzsza ani mniejszej od 0 z 
  // uwagi na ograniczenia systemu zapisowego.
  double timetmp = 0, timesum = 0, timemax = 0, timemin = numeric_limits<double>::max();
  //timemin dobrany na poczatku jako najwieksza liczba typu double
  time_point<system_clock> begin, end;
  int number_of_vertex[5] = {10, 20, 50, 100, 200};
  double percent_of_density[4] = {0.25, 0.5, 0.75, 1};
  char implementation_method[3] = {'e', 'l', 'm'};
  string name_of_method[3] = {"edge_list", "neighborhood_list", "neighborhood_matrix"};
  // e-edge_list, l-neighborhood_list, m-neighborhood_matrix
  ofstream file("results.txt");
  is_open(file);
  srand(time(NULL));

  for (char method : implementation_method) //1. sposób implementacji
  {
    cout << "Method: " << name_of_method[index_of_method++] << "." << endl;
    for (double percent : percent_of_density) //2. procent gestosci grafu
    {
      cout << "Case: " << percent * 100 << "%" << endl;
      for (int number : number_of_vertex) //3. liczba wierzcholkow w grafie
      {
        if (number <= 0)
        {
          cerr << "Wrong number of elements." << endl;
          exit(-3);
        }

        for (int nofgraphs = 0; nofgraphs < number_of_graphs; nofgraphs++) //4. liczba grafow
        {
          // nofgraphs jako number_of_graphs
          startV = rand() % number; //losowanie wierzcholka startowego
          switch (method)
          {
          case 'e':
          { //lista krawedzi
            elistgraph *graph = new elistgraph(number, percent);
            graph->fillgraph(shift, range); // graph->printgraph();  // wyswietlanie pozostawione 
            begin = high_resolution_clock::now(); //wlacz zegar      // dla prezentacji poprawnosci
            data = Bellman_Ford_alg(graph, startV);
            end = high_resolution_clock::now(); //zatrzymaj zegar
            delete[] data[0]; delete[] data[1]; delete[] data;
            delete graph; // usun dane i graf 
            break;
          }
          case 'l':
          { //lista sasiedztwa
            nlistgraph *graph = new nlistgraph(number, percent);
            graph->fillgraph(shift, range); // graph->printgraph();  // wyswietlanie pozostawione 
            begin = high_resolution_clock::now(); //wlacz zegar      // dla prezentacji poprawnosci
            data = Bellman_Ford_alg(graph, startV);
            end = high_resolution_clock::now(); //zatrzymaj zegar
            delete[] data[0]; delete[] data[1]; delete[] data;
            delete graph; // usun dane i graf 
            break;
          }
          case 'm':
          { //macierz sasiedztwa
            nmatrixgraph *graph = new nmatrixgraph(number, percent);
            graph->fillgraph(shift, range); // graph->printgraph();  // wyswietlanie pozostawione 
            begin = high_resolution_clock::now(); //wlacz zegar      // dla prezentacji poprawnosci
            data = Bellman_Ford_alg(graph, startV);
            end = high_resolution_clock::now(); //zatrzymaj zegar
            delete[] data[0]; delete[] data[1]; delete[] data;
            delete graph; // usun dane i graf 
            break;
          }
          default:
            cout << "It is not a method." << endl;
          }

          timetmp = duration<double, milli>(end - begin).count();
          if (timetmp > timemax) timemax = timetmp;
          if (timetmp < timemin) timemin = timetmp;
          timesum += timetmp;
        }
        file << (timesum / number_of_graphs) << " " << timemax << " "
             << timemin << endl;
        timesum = 0;
        timemax = 0;
        timemin = numeric_limits<double>::max();
        cout << "Number of vertex: " << number << " - path found." << endl;
      }
    }
  }
  cout << "End of Part 1." << endl << endl;
  file.close();

  // druga czesc programu
  FileManaging();
  cout << "End of Program." << endl;

  return 0;
}
