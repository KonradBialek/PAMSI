#ifndef AI_HH
#define AI_HH

#include <limits>
#include <cmath>

#include "Game.hh"

int HeuristicScore(TicTacToe *Game1, bool player); // Wyznacza wartość planszy.

int MiniMax(TicTacToe *Game1, int depth, bool ismax, int alpha, int beta);
// Wyznacza najlepszy ruch w otrzymanej sytuacji dla danego gracza.

void AiMove(TicTacToe *Game1);
// Ustawia parametry MiniMax(), wybiera najlepsze rozwiązanie i wykonuje ruch komputera.

#endif