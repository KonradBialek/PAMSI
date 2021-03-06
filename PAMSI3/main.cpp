#include <chrono>

#include "AI.hh"

using namespace std;
using namespace chrono;

/*!
 * \brief Wyswietla tablice i odczytuje z wejscia ruch gracza.
 *
 * Wyswietla tablice i odczytuje z wejscia ruch gracza. Ruch ten musi byc zgodny z wymiarami i 
 * sytuacja na planszy.
 * \param[in] Game1 - sytuacja w grze.
 * 
 * \pre Wskaznik na obiekt typu TicTacToe nie moze miec watosci NULL.
 * \post Wykonuje ruch gracza.  
 */
void HumanMove(TicTacToe *Game1)
{
    int moveY, moveX;
    bool moveisgood = false;

    Game1->draw_board();
    while (!moveisgood)
    {
        cout << "Insert move (format \"Y X\" - row column):";
        cin >> moveY >> moveX; // pobierz wspolrzedne ruchu w podanym formacie
        
        // obsluga bledow i wykonanie ruchu
        while (moveY <= 0 || moveY > Game1->getrange() || moveX <= 0 || moveX > Game1->getrange() || cin.fail())
        {
            cin.clear(); cin.ignore(1000, '\n');
            cout << "Unknown or wrong value. Insert data again." << endl;
            cin >> moveY >> moveX;
        }
        if (Game1->getboard(moveY - 1, moveX - 1) == Game1->getplayer(0)) // gdy pole jest puste
        {
            Game1->setboard(moveY - 1, moveX - 1) = Game1->getplayer(1); // zajmij pole (wykonaj ruch)
            Game1->draw_board(); Game1->setavailable()--;
            moveisgood = true;
        }
        else cout << endl << "Wrong move. Insert data again (check the format of the entered data)." << endl;
    }
    Game1 = NULL;
}

/*!
 * \brief Tworzy i nadzoruje gre.
 *
 * Tworzy i nadzoruje gre. Wywoluje ruch kolejnych graczy do momentu wykrycia sytuacji konczacej
 * gre.
 * \param[in] Game1 - sytuacja w grze.
 * 
 * \pre Wskaznik na obiekt typu TicTacToe nie moze miec watosci NULL.
 * \post Wykonuje ruch gracza.  
 */
void Play(int player, int range, int row)
{
    TicTacToe *Game1 = new TicTacToe(range, row);
    MoveAI move1;
    //time_point<system_clock> begin, end; 
    // pomiar czasu pozostawiony dla kontroli czasu ruchu komputera

    while (true)
    {
        if (player == 1) // ruch czlowieka
        {
            HumanMove(Game1);
            if (Game1->checkWin() == Game1->getplayer(1)) // gdy czlowiek wygral
            {
                cout << "User won" << endl;
                delete Game1; return;
            }
            else if (Game1->isFull() == 1) // gdy plansza jest pelna - remis 
            {
                cout << "Draw" << endl;
                delete Game1; return;
            }
            else player = 2; // zmien gracza
        }
        if (player == 2) // ruch komputera
        {
            cout << "AI move" << endl;
            if (Game1->getavailable() == range * range && Game1->getrow() == Game1->getrange())
            {
                Game1->setboard(0, 0) = Game1->getplayer(2); // Ruch komputera na pustej planszy, 
                Game1->setavailable()--;  // gdy rozmiar jest rowny warunkowi zwyciestwa, jest zdefiniowany.
            }
            else
            {
                //begin = high_resolution_clock::now(); // pomiar czasu pozostawiony dla kontroli czasu ruchu komputera
                AiMove(Game1);
                //end = high_resolution_clock::now();
                //cout << duration<double, milli>(end - begin).count() << endl;
            }

            // poza else powyzej poniewaz moze wystapic plansza 1x1
            if (Game1->checkWin() == Game1->getplayer(2)) // gdy komputer wygral
            {
                Game1->draw_board();
                cout << "AI won" << endl;
                delete Game1; return;
            }
            else if (Game1->isFull() == 1) // gdy plansza jest pelna - remis 
            {
                Game1->draw_board();
                cout << "Draw" << endl;
                delete Game1; return;
            }
            player = 1; // zmien gracza
        }
    }
}

/*!
 * \brief Funkcja glowna.
 *
 * Funkcja glowna. Pobiera parametry gry z wejscia i przekazuje do funkcji organizujacej gre.
 * Obsluguje nieprawidlowe podanie parametrow. Zamyka program.
 * \param[in] brak
 *
 * \pre Brak.
 * \post Pobiera parametry gry z wejscia i przekazuje do funkcji organizujacej gre.
 * \retval 0 (gdy program przebiegnie pomyslnie)
 */
int main() //The main function
{
    srand(time(NULL));
    int choice, range, row;
    cout << "TIC TAC TOE" << endl;

    // pobierz parametry gry
    cout << "Select range from 1 to 10: "; cin >> range; // pobierz rozmiar planszy
    while (range <= 0 || range > 10 || cin.fail()) // gdy podano nieprawidlowe dane
    {
        cin.clear(); cin.ignore(1000, '\n');
        cout << "Unknown or wrong value. Insert data again." << endl;
        cin >> range;
    }

    cout << "Select how many signs in row (max - range): "; cin >> row; // pobierz warunek wygranej
    while (row <= 0 || row > range || cin.fail()) // gdy podano nieprawidlowe dane
    {
        cin.clear(); cin.ignore(1000, '\n');
        cout << "Unknown or wrong value. Insert data again." << endl;
        cin >> row;
    }

    cout << "User: 'O'      AI: 'X'" << endl;
    cout << "Select: " << endl << "1: User first " << endl <<"2: AI first " << endl; 
    cin >> choice; // pobierz gracza rozpoczynajacego
    while (choice < 1 || choice > 2 || cin.fail()) // gdy podano nieprawidlowe dane
    {
        cin.clear(); cin.ignore(1000, '\n');
        cout << "Unknown or wrong value. Insert data again." << endl;
        cin >> choice;
    }

    Play(choice, range, row); // rozpocznij gre
    return 0;
}
