#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <vector>

bool isGameOver(const std::vector<std::vector<char>>& playerBoard, const std::vector<std::vector<char>>& attackedBoard);
void sunkedShips(const std::vector<std::vector<char>>& playerBoard, std::vector<std::vector<char>>& attackedBoard, int* copyAvailableShips);
void playPlayerVsPlayer(std::vector<std::vector<char>>& player2Board, std::vector<std::vector<char>>& player2AttackedBoard, std::vector<std::vector<char>>& player1Board, std::vector<std::vector<char>>& player1AttackedBoard);
void playGame();

#endif  // GAME_LOGIC_H
