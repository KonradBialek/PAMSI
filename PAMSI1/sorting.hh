#ifndef SORTING_HH
#define SORTING_HH

#include <cmath>

/* Mergesort */

template<typename type>
void Merge(type* taborig, type* tabreserve, int middle, int number);

template<typename type>
void MergeSort(type *taborig, type* tabreserve, int number);

/* Quicksort */

template<typename type>
void change(type &elem1, type &elem2);

template<typename type>
type median_of_3(type *taborig, int last);

template<typename type>
int Division(type *taborig, int number);

template<typename type>
void QuickSort(type *taborig, int number);
     
/* Heapsort */

/*!
 * \brief Wyznacza rodzica danego elementu kopca.
 *
 * Wyznacza rodzica danego elementu kopca.
 * \param[in] elem - indeks elementu tablicy.
 *.
 * \retval Indeks rodzica danego elementu.
 */
inline int iParent(int elem)     { return floor((elem - 1) / 2); }

/*!
 * \brief Wyznacza lewe dziecko danego elementu kopca.
 *
 * Wyznacza lewe dziecko danego elementu kopca.
 * \param[in] elem - indeks elementu tablicy.
 *
 * \retval Indeks lewego dziecka danego elementu.
 */
inline int iLeftChild(int elem)  { return 2 * elem + 1;          }   

/*!
 * \brief Wyznacza prawe dziecko danego elementu kopca.
 *
 * Wyznacza prawe dziecko danego elementu kopca.
 * \param[in] elem - indeks elementu tablicy.
 *
 * \retval Indeks prawego dziecka danego elementu.
 */
inline int iRightChild(int elem) { return 2 * elem + 2;          }   

template<typename type>
int FindChild(type *taborig, int first, int last);

template<typename type>
void RepairHeap(type *taborig, int first, int last);

template<typename type>
void BuildHeap(type *taborig, int number);

template<typename type>
void HeapSort(type *taborig, int number);

/* Insertionsort */

template<typename type>
void InsertionSort(type *taborig, int number);

/* Introsort */

template<typename type>
void IntroSort(type* taborig, int number, int depth);

#endif
