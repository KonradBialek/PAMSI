#include <iostream>
#include <fstream>
#include <iomanip>
#include <chrono>
#include "sorting.hh"

// aby uzyc innego typu niz int lub long int (nie tylko calkowitoliczbowe)
// nalezy dodac odpowiednie wywolanie na koncu pliku sorting.cpp
#define data_type int

using namespace std;
using namespace chrono;

/*!
 * \brief Zapisuje tablice danych do pliku.
 *
 * Zapisuje tablice danych do pliku.
 * \param[in] file - strumien do pliku,
 * \param[in] taborig - tablica z danymi,
 * \param[in] number - ilosc elementow tablicy.
 *
 * \pre Plik file musi byc otwarty,
 * \pre Wskaznik na tablice taborig nie moze miec watosci NULL.
 * \post Zapisano tablice taborig do pliku.
 */
template<typename type>
void to_file(ofstream &file, type *taborig, int number)
{
  for(int element = 0; element < number; element++) // wydrukuj tablice
  { 
    if(element%5 == 0) file << endl;
    file << setw(20) << fixed << setprecision(10) << taborig[element];
  }
  file << endl << endl;
}

/*!
 * \brief Wyswietla tablice danych w terminalu.
 *
 * Wyswietla tablice danych w terminalu.
 * \param[in] taborig - tablica z danymi,
 * \param[in] number - ilosc elementow tablicy.
 *
 * \pre Wskaznik na tablice taborig nie moze miec watosci NULL.
 * \post Wyswietlono tablice taborig w terminalu.
 */
template<typename type>
void print(type *taborig, int number)
{
  for(int element = 0; element < number; element++) // wydrukuj tablice
  { 
    if(element%5 == 0) cout << endl;
    cout << setw(20) << fixed << setprecision(10) << taborig[element];
  } 
  cout << endl << endl;
}

/*!
 * \brief Sprawdza czy dane w tablicy sa posortowane.
 *
 * Sprawdza czy dane w tablicy sa posortowane rosnaco lub malejaco w zaleznosci
 * od parametu inverse. Zamyka program, gdy tablica nie jest posortowana.
 * \param[in] taborig - tablica z danymi,
 * \param[in] number - ilosc elementow tablicy,
 * \param[in] inverse - kolejnosc sortowania.
 *
 * \pre Wskaznik na tablice taborig nie moze miec watosci NULL.
 * \post Brak lub zamyka program.
 */
template<typename type>
void is_sorted(type *taborig, int number, bool inverse)
{
  for(int element = 0; element < number-1; element++) // czy posortowana 
  { 
    if((inverse == 0 && taborig[element] > taborig[element+1]) ||
       (inverse == 1 && taborig[element] < taborig[element+1]))
    { 
      cerr << "Sort error. Elements " << taborig[element] << " and " 
           << taborig[element+1] << " are in wrong order." << endl; 
      exit(-2); 
    }
  } 
}

/*!
 * \brief Sprawdza czy plik zostal otwarty.
 *
 * Sprawdza czy plik zostal otwarty. Zamyka program, gdy plik nie jest
 * otwarty.
 * \param[in] file - strumien do pliku.
 *
 * \pre Brak.
 * \post Brak lub zamyka program.
 */
void is_open(ofstream &file)
{
  if (!file.is_open()) // czy otwarty 
  {
    cerr << "The write access operation of \"" << "results.txt" << "\"" 
	 << endl << "has failed." << endl;
    exit(-1);
  }
}

/*!
 * \brief Sortuje czesciowo tablice.
 *
 * Sortuje czesciowo tablice rosnaco lub malejaco w zaleznosci
 * od parametu inverse. Zakres danych do posortowania okresla parametr percent.
 * \param[in] taborig - tablica z danymi,
 * \param[in] number - ilosc elementow tablicy,
 * \param[in] percent - ilosc elementow tablicy do posortowania,
 * \param[in] inverse - kolejnosc sortowania.
 *
 * \pre Wartosc percent musi byc mniejsza od number,
 * \pre Wskaznik na tablice taborig nie moze miec watosci NULL.
 * \post Tablica danych jest czesciowo posortowana w zaleznosci od parametru
 *       percent.
 */
template<typename type>
void partial_sorting(type *taborig, int number, double percent, bool inverse)
{
  // sortowanie czesciowe
  IntroSort(taborig, (number * percent) / 100, floor(2 * log((number * percent) / 100)/log(2)));
  is_sorted<data_type>(taborig, (number * percent) / 100, 0);

  //Odwracanie kolejnosci danych, parametr inverse nie jest konieczny rownie 
  //dobrze mozna napisac if(percent==100), ale zastosowanie parametru pozwala 
  //uogolnic program.
  if(inverse) 
  {
    for(int element = 0, j = number - 1; element < j; element++, j--)
      change(taborig[element], taborig[j]);
    is_sorted<data_type>(taborig, number, 1);
  }
}

/*!
 * \brief Sortuje tablice.
 *
 * Sortuje tablice rosnaco. Metode sortowania okresla parametr method.
 * \param[in] taborig - tablica z danymi,
 * \param[in] tabreserve - tablica na dane w metodzie Mergesort,
 * \param[in] number - ilosc elementow tablicy,
 * \param[in] method - metoda sortowania.
 *
 * \pre Wskaznik na tablice taborig nie moze miec watosci NULL,
 * \pre Wskaznik na tablice tabreserve nie moze miec watosci NULL.
 * \post Tablica danych jest posortowana lub zamyka program.
 * \retval Czas trwania sortowania.
 */
template<typename type>
double sort(type *taborig, type *tabreserve, int number, char method)
{
  time_point<system_clock> begin, end;
  switch(method)
  {
    case 'm':
      begin = high_resolution_clock::now(); //wlacz zegar
      MergeSort<data_type>(taborig, tabreserve, number); //metoda Mergesort
      end = high_resolution_clock::now(); //zatrzymaj zegar
      break;
    case 'q':
      begin = high_resolution_clock::now(); //wlacz zegar
      QuickSort<data_type>(taborig, number); //metoda Quicksort
      end = high_resolution_clock::now(); //zatrzymaj zegar
      break;
    case 'i':
      begin = high_resolution_clock::now(); //wlacz zegar
      IntroSort<data_type>(taborig, number, floor(2 * log(number) / log(2)));
      //metoda Introsort
      end = high_resolution_clock::now(); //zatrzymaj zegar
      break;
    default: // gdy metoda jest zle oznaczona
      cerr << "Wrong method of sorting." << endl;
      exit(-2);
  }
  return duration<double, milli>(end-begin).count(); 
}

/*!
 * \brief Funkcja glowna.
 *
 * Funkcja glowna. Tworzy i otwiera plik na wyniki testow. Generuje i wypelnia 
 * tablice danch. Sortuje tablice danych czesciowo i w pelni. Rejestruje czasy 
 * minimalne i maksymalne oraz wyznacza czas sredni poszczegolnych testow i 
 * zapisuje je do otwartego pliku. Usuwa tablice danych. Zamyka program.
 *
 * \pre Brak.
 * \post Generuje plik z wynikami testow.
 * \retval 0.
 */
int main()
{
  int number_of_tables = 100, index_of_method = 0;
  double timetmp=0, timesum=0, timemax=0, timemin=numeric_limits<double>::max();
  //timemin dobrany na poczatku jako najwieksza liczba typu double
  int number_of_elements[5] = {10000, 50000, 100000, 500000, 1000000};
  double percent_of_sorting[8] = {0, 25, 50, 75, 95, 99, 99.7, 100};
  char sorting_method[3] = {'m','q','i'};
  string name_of_method[3] = {"mergesort", "quicksort", "introsort"};
  // m-mergesort, q-quicksort, i-introsort
  bool inverse = 0; 

  ofstream  file("results.txt");  is_open(file);  srand(time(NULL));
  for(char method : sorting_method)  //1. sposób sortowania
  {  
    cout << "Method: " << name_of_method[index_of_method++] << "." << endl;
    for(double percent : percent_of_sorting)  //2. procent posortowania
    { 
      if(percent == 100) inverse = 1;
      cout << "Case: " << percent << "% pre-sorted " 
           << (inverse?"inversely ":"") << endl;
      for(int number : number_of_elements)  //3. liczba elementow w tablicy
      {   
        if(number <= 0)
        {
          cerr << "Wrong number of elements." << endl;  exit(-3);
        } 
        // stworzenie dwóch tablic (zapasowa dla sortowania przez scalanie)
        data_type* taborig =    new data_type[number];
        data_type* tabreserve = new data_type[number];    

        for(int noftab=0; noftab<number_of_tables; noftab++)  //4. liczba tablic
        {  
          // uzupelnienie tablicy losowymi liczbami typu calkowitoiczbowego
          for(int element = 0; element < number; element++) 
            taborig[element] = (rand() + 1)/100; 
          partial_sorting<data_type>(taborig, number, percent, inverse); 
          timetmp = sort<data_type>(taborig, tabreserve, number, method);
          is_sorted<data_type>(taborig, number, 0);
	      if(timetmp > timemax) timemax = timetmp;
	      if(timetmp < timemin) timemin = timetmp;
          timesum += timetmp;
        }
        file << (timesum / number_of_tables) << " " << timemax << " "
             << timemin << endl;
        timesum = 0; timemax = 0; timemin = numeric_limits<double>::max();
        delete[] taborig;    delete[] tabreserve; // usuniecie tablic 
        cout << "Number of elements: " << number << " - sorted." << endl;
      }
      inverse = 0;
    }
  }
  cout << "End of sorting." << endl;  file.close();
  return 0;
}
