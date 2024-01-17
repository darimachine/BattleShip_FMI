
#include <iostream>
#include "GameSetup.h"
#include "PlayerActions.h"
#include "GameLogic.h"
using namespace std;
// Implementations for functions related to game setup


void printGameRules();
int chooseOpponent();
int enterBoardSize();
void chooseShipCount(unsigned int& choice);
void setShipCount(int boardSize);
void chooseBoard(std::vector<std::vector<char>>& board);
void StartUp();