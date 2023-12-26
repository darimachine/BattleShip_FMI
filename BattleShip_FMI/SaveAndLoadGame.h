
#ifndef SaveAndLoadGame_H
#define SaveAndLoadGame_H
#include <vector>
#include <fstream>
#include<iostream>
using namespace std;
void saveGame(const vector<vector<char>>& player2Board, const vector<vector<char>>& player2AttackedBoard,
    const vector<vector<char>>& player1Board, const vector<std::vector<char>>& player1AttackedBoard,
    bool isPlayerTurn,bool isPlayingWithComputer);
void saveMatrix(ofstream& outFile, const vector<vector<char>>& matrix);
void loadGame(std::vector<std::vector<char>>& player2Board, std::vector<std::vector<char>>& player2AttackedBoard,
    std::vector<std::vector<char>>& player1Board, std::vector<std::vector<char>>& player1AttackedBoard,
    bool& isPlayerTurn);
void loadMatrix(std::ifstream& inFile, std::vector<std::vector<char>>& matrix);
#endif // SaveAndLoadGame_H
