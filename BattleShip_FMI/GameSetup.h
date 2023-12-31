#ifndef GAME_SETUP_H
#define GAME_SETUP_H
#include <fstream>
#include <vector>
void printGameRules();
int chooseOpponent();
int enterBoardSize();
void setShipCount(int boardSize);
void chooseBoard(std::vector<std::vector<char>>& board);
void StartUp();

#endif  // GAME_SETUP_H
