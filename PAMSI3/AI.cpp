#include "AI.hh"

using namespace std;

/*!
 * \brief Wyznacza wartość planszy.
 *
 * Wyznacza wartość planszy. Nie gwarantuje poprawnego dzialania dla parametrow rozgrywki 
 * warunek zwyciestwa < rozmiar planszy !
 * Zrodla:
 * https://pl.wikipedia.org/wiki/Heurystyka_(informatyka)
 * https://www.codeproject.com/Articles/43622/Solve-Tic-Tac-Toe-with-the-MiniMax-algorithm
 * (punktacja wzorowana na akapicie "Heuristic score in Tic Tac Toe")
 * \param[in] Game1 - sytuacja w grze,
 * \param[in] player - gracz wykonujacy ruch.
 * 
 * \pre Wskaznik na obiekt typu TicTacToe nie moze miec watosci NULL.
 * \post brak  
 * \retval Wyznaczona wartosc planszy
 */
int HeuristicScore(TicTacToe *Game1, bool player)
{
    int X = 0, O = 0, score = 0;
    for (int i = 0; i < Game1->getrange(); i++) // dla linii poziomych
    {
        for (int j = 0; j < Game1->getrange(); j++)
        {
            if (Game1->getboard(i, j) == Game1->getplayer(2)) X++; // gdy wykryto 'X'
            if (Game1->getboard(i, j) == Game1->getplayer(1)) O++; // gdy wykryto 'O'
        }
        if (O && X) // gdy wykryto obu graczy w linii
        {
            O = 0; X = 0;
        }
        else if (!O && !X) score += (player ? 1 : -1); // gdy nie wykryto żadnego gracza w linii
        else score += (2 ^ X) - (2 ^ O); // gdy wykryto jednego gracza w linii
    }
    O = 0; X = 0;

    for (int j = 0; j < Game1->getrange(); j++) //dla linii pionowych
    {
        for (int i = 0; i < Game1->getrange(); i++)
        {
            if (Game1->getboard(i, j) == Game1->getplayer(2)) X++; // gdy wykryto 'X'
            if (Game1->getboard(i, j) == Game1->getplayer(1)) O++; // gdy wykryto 'O'
        }
        if (O && X) // gdy wykryto obu graczy w linii
        {
            O = 0; X = 0;
        }
        else if (!O && !X) score += (player ? 1 : -1); // gdy nie wykryto żadnego gracza w linii
        else score += (2 ^ X) - (2 ^ O); // gdy wykryto jednego gracza w linii
    }
    O = 0; X = 0;

    for (int i = 0, j = 0; i < Game1->getrange(); i++, j++) //dla glownej diagonali
    {
        if (Game1->getboard(i, j) == Game1->getplayer(2)) X++; // gdy wykryto 'X'
        if (Game1->getboard(i, j) == Game1->getplayer(1)) O++; // gdy wykryto 'O'
    }
    if (O && X) // gdy wykryto obu graczy w linii
    {
        O = 0; X = 0;
    }
    else if (!O && !X) score += (player ? 1 : -1); // gdy nie wykryto żadnego gracza w linii
    else score += (2 ^ X) - (2 ^ O); // gdy wykryto jednego gracza w linii
    O = 0; X = 0;
 
    for (int i = 0, j = Game1->getrange(); i < Game1->getrange(); i++, j--) //dla drugiej diagonali
    {
        if (Game1->getboard(i, j) == Game1->getplayer(2)) X++; // gdy wykryto 'X'
        if (Game1->getboard(i, j) == Game1->getplayer(1)) O++; // gdy wykryto 'O'
    }
    if (O && X) // gdy wykryto obu graczy w linii
    {
        O = 0; X = 0;
    }
    else if (!O && !X) score += (player ? 1 : -1); // gdy nie wykryto żadnego gracza w linii
    else score += (2 ^ X) - (2 ^ O); // gdy wykryto jednego gracza w linii

    Game1 = NULL;
    return score;
}

/*!
 * \brief Wyznacza najlepszy ruch w otrzymanej sytuacji dla danego gracza.
 *
 * Wyznacza najlepszy ruch w otrzymanej sytuacji dla danego gracza. Funkcja 
 * rozszerzona o mechanizm "alpha beta".
 * Zrodla:
 * https://en.wikipedia.org/wiki/Alpha%E2%80%93beta_pruning
 * \param[in] Game1 - sytuacja w grze,
 * \param[in] depth - pozostala wartosc glebokosci rekurencji,
 * \param[in] ismax - gracz wykonujacy ruch,
 * \param[in] alpha - parametr alfa mechanizmu alfa-beta,
 * \param[in] beta - parametr beta mechanizmu alfa-beta,
 * 
 * \pre Wskaznik na obiekt typu TicTacToe nie moze miec watosci NULL.
 * \post brak  
 * \retval Wartosc najlepszego rozwiazania.
 */
int MiniMax(TicTacToe *Game1, int depth, bool ismax, int alpha, int beta)
{
    int value = (ismax ? -1 : 1) * numeric_limits<int>::max() / 2; // dla max -inf, dla min inf
    char winner = Game1->checkWin(); // wyznacz zwyciezce
    if (winner == Game1->getplayer(2)) // jezeli wygral komputer
        return max(0, numeric_limits<int>::max() / 2 - 2 * depth);

        // Symboliczny wplyw glebokosci w sytuacjach rownych wartosci planszy wybiera szybsza wersje.

    if (winner == Game1->getplayer(1)) // jezeli wygral czlowiek 
        return min(0, -numeric_limits<int>::max() / 2 + 2 * depth);

    if (Game1->isFull() == 1) return 0; // jezeli nastapil remis
    if (!depth) // Jezeli osiagnieto graniczna glebokosc nalezy zwrocic wartosc planszy 
    {           // zgodnie z zasadami powyzej.
        if(Game1->getrange() == Game1->getrow()) 
            return max(0, HeuristicScore(Game1, ismax) - 2 * depth);
        else return 0;  // dla negatywnego wyniku warunku nie udalo sie napisac funkcji 
                        // odpowiedzialnej za okreslenie wartosci planszy
    }

    for (int i = 0; i < Game1->getrange(); i++)
    {
        for (int j = 0; j < Game1->getrange(); j++)
            if (Game1->getboard(i, j) == Game1->getplayer(0)) // jezeli pole jest wolne
            {
                Game1->setboard(i, j) = Game1->getplayer(ismax+1); // zajmij pole 
                Game1->setavailable()--;                            // odpowiednim graczem
                int score = MiniMax(Game1, depth - 1, !ismax, alpha, beta); // wywolaj rekurencje
                Game1->setboard(i, j) = Game1->getplayer(0); // cofnij zajecie pola
                Game1->setavailable()++;

                // Rozszerzenie alpha-beta
                if (ismax) // jezeli maksymalizuje
                {
                    value = max(score, value); // zaktualizuj wartosc najlepszego ruchu
                    alpha = max(alpha, score); // zaktualizuj alpha
                }
                else
                {
                    value = min(score, value); // zaktualizuj wartosc najlepszego ruchu
                    beta = min(beta, score);   // zaktualizuj beta
                }
                if (alpha >= beta) break; // jezeli spelniony warunek przerwij petle
            }
        if (alpha >= beta) break; // jezeli spelniony warunek przerwij petle
    }
    Game1 = NULL;
    return value;
}

/*!
 * \brief Ustawia parametry MiniMax(), wybiera najlepsze rozwiązanie i wykonuje ruch komputera.
 *
 * Ustawia parametry MiniMax(), wybiera najlepsze rozwiązanie i wykonuje ruch komputera.
 * Zrodla:
 * https://en.wikipedia.org/wiki/Minimax 
 * \param[in] Game1 - sytuacja w grze.
 * 
 * \pre Wskaznik na obiekt typu TicTacToe nie moze miec watosci NULL.
 * \post Wykonuje ruch komputera.  
 */
void AiMove(TicTacToe *Game1)
{
    int value = -numeric_limits<int>::max() / 2; // poczatkowa wartosc najlepszego rozwiazania
    MoveAI move1;
    int depth; //, x, y;
    if (Game1->getrange() <= 3) depth = 10; // ustalenie wartosci glebokosci
    else depth =100/sqrt(8*Game1->getavailable());
    if (depth > 10) depth = 10;

    for (int i = 0; i < Game1->getrange(); i++)
        for (int j = 0; j < Game1->getrange(); j++)
            if (Game1->getboard(i, j) == Game1->getplayer(0))
            {
                Game1->setboard(i, j) = Game1->getplayer(2); // zajmij pole 
                Game1->setavailable()--;
                // wywolaj rekurencje 
                int score = MiniMax(Game1, depth, false, -numeric_limits<int>::max() / 2, numeric_limits<int>::max() / 2); 
                Game1->setboard(i, j) = Game1->getplayer(0); // cofnij zajecie pola
                Game1->setavailable()++;
                if (score > value) // jezeli spelniony warunek ustaw wspolrzedne ruchu
                {
                    value = score;
                    move1.setmove(i, j);
                }
            }

    if(move1.gety()!=-1) 
    {
        Game1->setboard(move1.gety(), move1.getx()) = Game1->getplayer(2); // zajmij pole (wykonaj ruch)
        Game1->setavailable()--; Game1 = NULL;
    }
    else
    {   // Wyjatek, gdy komputer nie znalazl optymalnego ruchu np. z powodu gwarantowanego zwyciestwa gracza poddaje sie.
        // Ta część kodu nie zostanie wywołana, ponieważ komputer przyjmuje pierwszy zbadany ruch jako najlepszy a 
        // następnie porównuje go z pozostałymi możliwościami wybierając najlepszy ruch.
        cout << "AI can not find optimal move due to guarranted win for opponent. Game is lost. User won." <<endl;
        delete Game1; exit(0);

        /*
        // Inny sposob rozwiazania problemu (niezalecane): zajmij losowe pole
        do
        {
            x = rand() % Game1->getrange();
            y = rand() % Game1->getrange();
        } while (Game1->getboard(y, x) != Game1->getplayer(0));
        Game1->setboard(y, x) = Game1->getplayer(2); // zajmij pole (wykonaj ruch)
        Game1->setavailable()--; Game1 = NULL;
        */
    }
}