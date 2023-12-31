
#include <iostream>
#include <fstream>
#include "GameSetup.h"
#include "PlayerActions.h"
#include "GameLogic.h"
#include "BattleShip_FMI.h"
using namespace std;
// Implementations for functions related to game setup


void printGameRules();
int chooseOpponent();
int enterBoardSize();
void setShipCount(int boardSize);
void chooseBoard(std::vector<std::vector<char>>& board);
