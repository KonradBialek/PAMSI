#include "sorting.hh"

using namespace std;

/* 
 * Do wszystkich funkcji korzystajacch z argumentow middle, number, last, first,
 * elem i depth: wymienione argumenty musza byc wieksze lub rowne 0.
 * W algorytmach wykorzystano fakt, ze wskaznik moze wskazywac na dowolny element
 * tablicy dynamicznej ulatwiajac traktowanie podtablicy w sortowaniu czesci 
 * tablicy jako niezaleznej tablicy.
 */

/* Mergesort */

/*!
 * \brief Laczy dwie podtablice w jedna jednoczesnie ja sortujac.
 *
 * Kopiuje tablice danych do zapasowej. Porownuje kolejne elementy obu 
 * podtablic pobierajac mniejszy z nich, a wiekszy porownujac z kolejnym 
 * elementem podtablicy mniejszego elementu. Gdy w jednej z podtablic skoncza
 * sie elementy tablice uzupelnia nieprzydzielonymi elementami pozostalej  
 * podtablicy.
 * \param[in] taborig - tablica z danymi,
 * \param[in] tabreserve - tablica na dane w metodzie Mergesort,
 * \param[in] middle - indeks srodkowego elemeentu,
 * \param[in] number - ilosc elementow tablicy.
 *
 * \pre Wskaznik na tablice taborig nie moze miec watosci NULL,
 * \pre Wskaznik na tablice tabreserve nie moze miec watosci NULL.
 * \post Dwie podtablice sa polaczone w tablice danych.
 */
template<typename type>
void Merge(type* taborig, type* tabreserve, int middle, int number)
{
  int j = 0;       //iterator 1. podtablicy (lewej czesci sortowanej części 
                   //tablicy dynamicznej)
  int k = 0;       //iterator oryginalnej tablicy
  int m = middle;  //iterator 2. podtablicy (prawej czesci sortowanej części
                   //tablicy dynamicznej)

  for(int element = 0; element < number; element++)
    tabreserve[element] = taborig[element];  //kopiowanie tablicy

  //względem pierwowzoru zastąpiono iterację 'k' w pętli for iteracją trzech
  //zmiennych wewnątrz pętli while
  while(j < middle && m < number) 
  {
    if(tabreserve[j] < tabreserve[m]) //gdy element 1. podtablicy mniejszy od 
      taborig[k++] = tabreserve[j++]; //elementu 2. podtablicy
    else taborig[k++] = tabreserve[m++];
  }

  // gdy jedna z podtablic sie skonczy
  while(j < middle) taborig[k++] = tabreserve[j++];
  while(m < number) taborig[k++] = tabreserve[m++];
}

/*!
 * \brief Sortuje tablice przy pomocy metody Mergesort.
 *
 * Sortuje tablice przy pomocy metody Mergesort rosnaco. Jezeli elementow
 * tablicy jest wiecej niz 1, wyznacza element srodkowy tablicy i wywoluje 
 * siebie rekurencyjnie dla obu czesci tablicy tj. od elementu zerowego do 
 * elementu srodkowego bez tego elementu i od elementu srodkowego do ostatniego
 * elementu. Nastepnie laczy obie czesci w jedna tablice.
 * Zrodla:
 * https://en.wikipedia.org/wiki/Merge_sort
 * https://algorithmist.com/wiki/Merge_sort
 * \param[in] taborig - tablica z danymi,
 * \param[in] tabreserve - tablica na dane w metodzie Mergesort,
 * \param[in] number - ilosc elementow tablicy.
 *
 * \pre Wskaznik na tablice taborig nie moze miec watosci NULL,
 * \pre Wskaznik na tablice tabreserve nie moze miec watosci NULL.
 * \post Tablica danych (lub jej czesc gdy to wywolanie rekurencyjne) jest 
 *       posortowana.
 */
template<typename type>
void MergeSort(type *taborig, type* tabreserve, int number)
{
  if(number > 1) 
  {
    int middle = (number + 1) / 2; 
    MergeSort(taborig, tabreserve, middle); 
    MergeSort(taborig + middle, tabreserve, number - middle);
    // przesuwanie tabreserve jest zbedne
    Merge(taborig, tabreserve, middle, number);
  }
}

/* Quicksort */

/*!
 * \brief Zamienia wartosci dwoch elementow tablicy.
 *
 * Zamienia wartosci dwoch elementow tablicy. (Formalnie zamienia dwa elementy
 * miejscami.)
 * \param[in] elem1 - pierwszy z elementow do zamiany,
 * \param[in] elem2 - drugi z elementow do zamiany.
 *
 * \pre Parametr elem1 musi odnosic sie do istniejacej wartosci,
 * \pre Parametr elem2 musi odnosic sie do istniejacej wartosci.
 * \post Wartosci dwoch elementow sa zamienione.
 */
template<typename type>
void change(type &elem1, type &elem2)
{
  type tymczas = elem1;
  elem1 = elem2;
  elem2 = tymczas;
}

/*!
 * \brief Wybiera najmniejszy element sposrod pierwszego, srodkowego i 
 *        ostatniego.
 *
 * Wybiera najmniejszy element sposrod pierwszego, srodkowego i ostatniego oraz
 * ustawia je w kolejnosci rosnacej na ich miejscach.
 * \param[in] taborig - tablica z danymi,
 * \param[in] last - ostatni element tablicy.
 *
 * \pre Wskaznik na tablice taborig nie moze miec watosci NULL.
 * \post Ustawia elementy pierwszy, srodkowy i ostatni w kolejnosci rosnacej na
 *       ich miejscach.
 * \retval Srodkowy element tablicy danych.
 */
template<typename type>
type median_of_3(type *taborig, int last)
{
  int middle = (last + 1) / 2;

  // wybor elementu osiowego
  if(taborig[last] < taborig[0])
     change(taborig[last], taborig[0]);
  if(taborig[middle] < taborig[0])
     change(taborig[middle], taborig[0]);
  if(taborig[last] < taborig[middle])
     change(taborig[last], taborig[middle]);
  return taborig[middle];
}

/*!
 * \brief Wyznacza element osiowy i dzieli tablice danych na dwie podtablice.
 *
 * Przy pomocy mediany z trzech wyznacza element osiowy i dzieli tablice danych
 * na dwie podtablice: elementow mniejszych od elementu osiowego i elementow 
 * wiekszych od elementow osiowego przy pomocy schematu podziału Hoare.
 * \param[in] taborig - tablica z danymi,
 * \param[in] number - ilosc elementow tablicy.
 *
 * \pre Wskaznik na tablice taborig nie moze miec watosci NULL.
 * \post Dzieli tablice danych na dwie podtablice.
 * \retval Indeks koncowy.
 */
template<typename type>
int Division(type *taborig, int number)
{
  type axis;
  int leftside = 0, rightside = number - 1;
  if(number >= 3) axis = median_of_3(taborig, number - 1);
  else axis = taborig[number - 1];

  while(true)// segregowanie elementow
  {
    while(taborig[leftside] < axis)  leftside++;
    while(taborig[rightside] > axis) rightside--;

    if(leftside < rightside) 
      change(taborig[leftside++], taborig[rightside]);
    else return leftside;
  }
}

/*!
 * \brief Sortuje tablice przy pomocy metody Quicksort.
 *
 * Sortuje tablice przy pomocy metody Quicksort rosnaco. Jezeli elementow
 * tablicy jest wiecej niz 1, wyznacza element osiowy tablicy i wywoluje 
 * siebie rekurencyjnie dla obu czesci tablicy tj. od elementu zerowego do 
 * elementu osiowego bez tego elementu i od elementu osiowego do ostatniego
 * elementu. Dzieki dzialaniu w miejscu obie podtablice sa polaczone podczas 
 * dzialania algorytmu.
 * Zrodlo:
 * https://en.wikipedia.org/wiki/Quicksort
 * \param[in] taborig - tablica z danymi,
 * \param[in] number - ilosc elementow tablicy.
 *
 * \pre Wskaznik na tablice taborig nie moze miec watosci NULL.
 * \post Tablica danych (lub jej czesc gdy to wywolanie rekurencyjne) jest 
 *       posortowana przy pomocy metody Quicksort.
 */
template<typename type>
void QuickSort(type *taborig, int number)
{
  if(number > 1)
  {
    int axis = Division(taborig, number); // element osiowy
    QuickSort(taborig, axis);
    QuickSort(taborig + axis, number - axis);
  }
}

/* Heapsort */

/*
//Uwaga! Ponizsze funkcje znajdują się w pliku naglowkowym sorting.hh
inline int iParent(int elem)     { return floor((elem - 1) / 2); }
inline int iLeftChild(int elem)  { return 2 * elem + 1;          }  
inline int iRightChild(int elem) { return 2 * elem + 2;          }          
*/

/*!
 * \brief Schodzi w dol kopca wybierajac wieksze z dzieci, a gdy na dole jest
 *        jedno dziecko wybiera je.
 *
 * Schodzi w dol kopca wybierajac wieksze z dzieci, a gdy na dole jest jedno
 * dziecko wybiera je.
 * \param[in] taborig - tablica z danymi,
 * \param[in] first - pierwszy element tablicy,
 * \param[in] last - ostatni element tablicy.
 *
 * \pre Wskaznik na tablice taborig nie moze miec watosci NULL.
 * \post Brak.
 */
template<typename type>
int FindChild(type *taborig, int first, int last)
{
  int to_choose = first;
  while(iRightChild(to_choose) <= last)
  {
    if(taborig[iRightChild(to_choose)] > taborig[iLeftChild(to_choose)])
      to_choose = iRightChild(to_choose);
    else
      to_choose = iLeftChild(to_choose);
  }
  if(iLeftChild(to_choose) <= last)
    to_choose = iLeftChild(to_choose);
  return to_choose;
}

/*!
 * \brief Przywraca wlasnosci kopca.
 *
 * Wybiera poczatkowe dziecko. Wchodzi w gore kopca po rodzicu danego elementu 
 * dopoki rodzic elementu jest wiekszy od danego elementu. W przeciwnym wypadku
 * pobiera wartosc elementu, a w jego miejsce wstawia wartosc korzenia badanego 
 * poddrzewa. Zamienia pobrany element z kolejnymi rodzicami dopoki nie dojdzie
 * do korzenia.
 * \param[in] taborig - tablica z danymi,
 * \param[in] first - pierwszy element tablicy,
 * \param[in] last - ostatni element tablicy.
 *
 * \pre Wskaznik na tablice taborig nie moze miec watosci NULL.
 * \post Przywraca wlasnosci kopca.
 */
template<typename type>
void RepairHeap(type *taborig, int first, int last)
{
  int child = FindChild(taborig, first, last);
  while(taborig[first] > taborig[child])
    child = iParent(child);
  type tmp = taborig[child];
  taborig[child] = taborig[first];
  while(child > first)
  {
    change(tmp, taborig[iParent(child)]);
    child = iParent(child);
  }
}

/*!
 * \brief Buduje kopiec.
 *
 * Naprawia kolejne poddrzewa wchodzac w gore struktury drzewa.
 * \param[in] taborig - tablica z danymi,
 * \param[in] number - ilosc elementow tablicy.
 *
 * \pre Wskaznik na tablice taborig nie moze miec watosci NULL.
 * \post Przywraca wlasnosci kopca.
 */
template<typename type>
void BuildHeap(type *taborig, int number) 
{
  int ActiveParent = iParent(number - 1);   

  // wchodzenie w górę kopca (w coraz mniejsze indeksy tablicy)
  while(ActiveParent >= 0) 
  {      
    RepairHeap(taborig, ActiveParent, number - 1);
    ActiveParent--;
  }
}

/*!
 * \brief Sortuje tablice przy pomocy metody Heapsort.
 *
 * Sortuje tablice przy pomocy metody Heapsort rosnaco. Buduje kopiec, a 
 * nastepnie zamienia wartosc elementu korzenia z wartoscia ostatniego elementu
 * kopca i przywraca wlasnosci kopca ignorujac ostatni element kopca, czyli 
 * zmniejszajac ilosc elementow w kopcu o 1. 
 * Zrodlo:
 * https://en.wikipedia.org/wiki/Heapsort
 * \param[in] taborig - tablica z danymi,
 * \param[in] number - ilosc elementow tablicy.
 *
 * \pre Wskaznik na tablice taborig nie moze miec watosci NULL.
 * \post Tablica danych (lub jej czesc) jest posortowana przy pomocy metody
 *       Heapsort.
 */
template<typename type>
void HeapSort(type *taborig, int number) 
{
  int element = number - 1;

  BuildHeap(taborig, number);
  while(element > 0) 
  {
    change(taborig[0], taborig[element]);
    element--;
    RepairHeap(taborig, 0, element);
  }
}

/* Insertionsort */

/*!
 * \brief Sortuje tablice przy pomocy metody Insertionsort.
 *
 * Sortuje tablice przy pomocy metody Insertionsort rosnaco. Pierwszy element 
 * jest juz posortowany (przez oczywistosc). Wybiera element za posortowana
 * czescia tablicy i porownuje z kolejnymi elementami posortowanej czesci
 * tablicy od najwiekszych elementow przesuwajac kolejne elementy. Gdy znajdzie
 * element mniejszy od wybranego wstawia wybrany element na miejsce o indeksie
 * o 1 wiekszym od znalezionego mniejszego elementu.
 * Zrodlo:
 * https://en.wikipedia.org/wiki/Insertion_sort
 * \param[in] taborig - tablica z danymi,
 * \param[in] number - ilosc elementow tablicy.
 *
 * \pre Wskaznik na tablice taborig nie moze miec watosci NULL.
 * \post Tablica danych (lub jej czesc) jest posortowana przy pomocy metody
 *       Insertionsrt.
 */
template<typename type>
void InsertionSort(type *taborig, int number)
{
  type to_change;
  int element = 1, j;

  while(element < number) 
  {
    to_change = taborig[element];
    j = element - 1;

    while(j >= 0 && taborig[j] > to_change) 
    {
      taborig[j + 1] = taborig[j];
      j--;
    }
    taborig[j + 1] = to_change; 
    element++;
  } 
}

/* Introsort */

/*!
 * \brief Sortuje tablice przy pomocy metody Introsort.
 *
 * Sortuje tablice przy pomocy metody Introsort rosnaco. Gdy ilosc elementow
 * tablicy danych jest mniejsza lub rowna 16 wywoluje funkcje Insertionsort, gdy
 * licznik glebokosc wywolania osiagnie wartosc 0 wywoluje funkcje Heapsort, a 
 * gdy zadne z tych nie nastapi wyznacza element osiowy tablicy i wywoluje 
 * siebie rekurencyjnie dla obu czesci tablicy tj. od elementu zerowego do 
 * elementu osiwego bez tego elementu i od elementu osiowego do ostatniego
 * elementu obnizajac wartosc glebokosci wywolania o 1. Dzieki dzialaniu w 
 * miejscu obie podtablice sa polaczone podczas dzialania algorytmu.
 * Zrodlo:
 * https://en.wikipedia.org/wiki/Introsort
 * \param[in] taborig - tablica z danymi,
 * \param[in] number - ilosc elementow tablicy,
 * \param[in] depth - glebokosc wywolania (rekurencji).
 *
 * \pre Wskaznik na tablice taborig nie moze miec watosci NULL.
 * \post Tablica danych (lub jej czesc gdy to wywolanie rekurencyjne) jest 
 *       posortowana przy pomocy metody Introsort.
 */
template<typename type>
void IntroSort(type* taborig, int number, int depth)
{
  if(number <= 16)    InsertionSort(taborig, number);
  else if(depth <= 0) HeapSort(taborig, number);
  else 
  {
    int axis = Division(taborig, number);
    IntroSort(taborig, axis, depth - 1);
    IntroSort(taborig + axis, number - axis, depth - 1);
  }
}

template void MergeSort<int>(int*, int*, int);
template void QuickSort<int>(int*, int);
template void IntroSort<int>(int*, int, int);

template void MergeSort<long int>(long int*, long int*, int);
template void QuickSort<long int>(long int*, int);
template void IntroSort<long int>(long int*, int, int);

