#include "Game.hh"

using namespace std;

    /*!
     * \brief Sprawdza, czy spelniony zostal warunek wygranej.
     *
     * Sprawdza, czy spelniony zostal warunek wygranej.
     * \param[in] way - sposob wygranej (pion, poziom, przekatna),
     * \param[in] x - rzedna planszy,
     * \param[in] y - odcieta planszy.
     * 
     * \pre Wskaznik na obiekt typu TicTacToe nie moze miec watosci NULL.
     * \post brak
     * \retval Czy warynek zwyciestwa jest spelniony
     */
    bool TicTacToe::check(int way, int x, int y)
    {
        if (way == 0) // sprawdzenie w poziomie
            for (int i = 1; i < row; i++) if (board[y][x] != board[y][x + i]) return false;
        if (way == 1) // sprawdzenie w pionie
            for (int i = 1; i < row; i++) if (board[y][x] != board[y + i][x]) return false;
        if (way == 2) // sprawdzenie na glownej diagonali i rownoleglych ukosnych
            for (int i = 1; i < row; i++) if (board[y][x] != board[y + i][x + i]) return false;
        if (way == 3) // sprawdzenie na drugiej diagonali i rownoleglych ukosnych
            for (int i = 1; i < row; i++) if (board[y][x] != board[y + i][x - i]) return false;
        return true;
    }

    /*!
     * \brief Sprawdza, czy i kto wygral.
     *
     * Sprawdza, czy i kto wygral.
     * \param[in] brak
     * 
     * \pre Wskaznik na obiekt typu TicTacToe nie moze miec watosci NULL.
     * \post brak
     * \retval Czy warynek zwyciestwa jest spelniony
     */
    char TicTacToe::checkWin() 
    {
        for (int i = 0; i < range; i++) // dla calej planszy
            for (int j = 0; j < range; j++)
                if (board[i][j] != players[0]) // gdy to nie jest puste pole
                {
                    if (j < range - row + 1) // gdy odpowiednio daleko od krawedzi planszy
                        if (check(0, j, i)) return board[i][j]; // sprawdz czy wygrana
                    if (i < range - row + 1) // gdy odpowiednio daleko od krawedzi planszy
                    {
                        if (check(1, j, i)) return board[i][j]; // sprawdz czy wygrana
                        if (j < range - row + 1) // gdy odpowiednio daleko od krawedzi planszy
                            if (check(2, j, i)) return board[i][j]; // sprawdz czy wygrana
                        if (j >= row - 1) // gdy odpowiednio daleko od krawedzi planszy
                            if (check(3, j, i)) return board[i][j]; // sprawdz czy wygrana
                    }
                }
        return players[0]; // gdy nikt nie wygral
    }

    /*!
     * \brief Rysuje plansze.
     *
     * Rysuje plansze.
     * \param[in] brak
     * 
     * \pre Wskaznik na obiekt typu TicTacToe nie moze miec watosci NULL.
     * \post Wyswietla plansze z zajetymi polami.
     */
    void TicTacToe::draw_board() // wyswietl plansze 
    {
        // Wykorzystanie biblioteki iomanip jest niewskazane z uwagi na mozliwosc wystapienia dyzych plansz.
        cout << endl;
        for (int i = 0; i < range; ++i)
        {
            for (int j = 0; j < range; ++j)
            {
                cout << board[i][j]; // znak
                if (j != range - 1) cout << "|";
                else cout << endl;
            }
            if (i != range - 1) // miedzy-poziom
                for (int j = 0; j < range; j++) cout << "--";
            cout << endl;
        }
    }

    /*!
     * \brief Konstruktor parametryczny obiektu typu TicTacToe.
     *
     * Konstruktor parametryczny obiektu typu TicTacToe.
     * \param[in] range - rozmiar planszy,
     * \param[in] row - warunek wygranej.
     * 
     * \pre brak
     * \post Tworzy gre w kolko i krzyzyk.
     */
    TicTacToe::TicTacToe(int range, int row) : range(range), row(row), available(range * range), // ustawienie
                                    players{' ', 'O', 'X'}, board(new char *[range])  // parametrow
    {
        for (int i = 0; i < range; i++)
        {
            board[i] = new char[range];
            for (int j = 0; j < range; j++)
                board[i][j] = players[0]; // ustawianie pustej planszy
        }
    }
    /*!
     * \brief Destruktor obiektu typu TicTacToe.
     *
     * Destruktor obiektu typu TicTacToe.
     *
     * \pre Gra istnieje.
     * \post Usuwa gre.
     */
    TicTacToe::~TicTacToe()
    {
        for (int i = 0; i < range; i++)
            delete[] board[i];
        delete[] board;
    }