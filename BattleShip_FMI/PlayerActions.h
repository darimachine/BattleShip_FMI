
#ifndef PLAYER_ACTIONS_H
#define PLAYER_ACTIONS_H

#include <vector>

void printBoard(const std::vector<std::vector<char>>& board);
void displayAvailableShips(const int howManyShips[]);
bool canPlaceShip(const std::vector<std::vector<char>>& board, int choice, unsigned int x, unsigned int y, unsigned int direction);
void addShipToBoard(std::vector<std::vector<char>>& board, int choice, unsigned int x, unsigned int y, unsigned int direction);
void placeShipWithUserInput(std::vector<std::vector<char>>& board, int choice);
void copyAvailableShips(int* copy);
void placeAllShipsOnBoard(std::vector<std::vector<char>>& board);
bool isValidCoordinates(const std::vector<std::vector<char>>& attackedBoard, unsigned int x, unsigned int y);
int getRandomNumber(int min, int max);
void placeRandomShip(std::vector<std::vector<char>>& board, int choice);
void placeAllShipsRandomly(std::vector<std::vector<char>>& board);
void hitShip(const std::vector<std::vector<char>>& playerBoard, std::vector<std::vector<char>>& attackedBoard, int* copyAvailableShips);

#endif  // PLAYER_ACTIONS_H
