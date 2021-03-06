#ifndef GAME_HH
#define GAME_HH

#include <iostream>

class MoveAI // definicja ruchu komputera
{
    int x, y; // wspolrzedne ruchu

public:
    /*!
     * \brief Funkcje umozliwiajace kontrolowany dostep do pol klasy.            
     *
     * Funkcje umozliwiajace kontrolowany dostep do pol klasy.
     * \param[in] brak
     *
     * \pre brak
     * \post brak
     * \retval Odpowiednie pole klasy
     */
    int getx() const { return x; }
    int gety() const { return y; }

    /*!
     * \brief Ustawia ruch komputera.
     *
     * Ustawia ruch komputera.
     * \param[in] i - rzedna planszy,
     * \param[in] j - odcieta planszy.
     * 
     * \pre brak
     * \post Ustawia ruch.
     */
    void setmove(int i, int j) { x = j; y = i; }

    /*!
     * \brief Konstruktor bezparametryczny obiektu typu MoveAI.
     *
     * Konstruktor bezparametryczny obiektu typu MoveAI.
     *
     * \pre brak
     * \post Tworzy domyślny ruch.
     */
    MoveAI() : x(-1), y(-1) {}

    // Destruktor z racji statycznego tworzenia obiektów MoveAI w programie jest domyślny. 
};

class TicTacToe // definicja listy sasiedztwa (neighborhood_list graph) 
{
    int range, row, available; // zakres, warunek wygranej i wolne miejsce
    char players[3];           // oznaczeniepustego pola i graczy
    char **board;              // plansza do gry

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
    int getrange() const { return range; }
    char getplayer(int player) const { return players[player]; }
    int getavailable() const { return available; }
    int &setavailable() { return available; }
    char getboard(int y, int x) const { return board[y][x]; }
    char &setboard(int y, int x) { return board[y][x]; }
    int getrow() { return row; }

    /*!
     * \brief Sprawdza czy plansza jest pełna.
     *
     * Sprawdza czy plansza jest pełna.
     * \param[in] brak
     * 
     * \pre Wskaznik na obiekt typu TicTacToe nie moze miec watosci NULL.
     * \post brak
     * \retval Czy plansza jest pelna
     */
    int isFull() { return available == 0; } 

    bool check(int way, int x, int y); // czy spelniony warunek wygranej

    char checkWin(); // czy ktorys z graczy wygral

    void draw_board(); // wyswietl plansze 

    TicTacToe(int range, int row); // Konstruktor bezparametryczny obiektu typu TicTacToe

    ~TicTacToe(); // Destruktor obiektu typu TicTacToe
};

#endif