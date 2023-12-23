// BattleShip_FMI.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;
constexpr int BOARD_SIZE = 10;
vector<vector<char>> player1Board(BOARD_SIZE, vector<char>(BOARD_SIZE, '.'));
vector<vector<char>> player2Board(BOARD_SIZE, vector<char>(BOARD_SIZE, '.'));
void printGameRules() {
    cout << "**************************************************\n";
    cout << "              BATTLESHIPS - GAME RULES            \n";
    cout << "**************************************************\n";
    cout << "1. The game is played on two identical square boards.\n";
    cout << "2. Each player (or the computer) has a fleet of ships to place on their board.\n";
    cout << "3. The standard fleet consists of the following ships:\n";
    cout << "   - Patrol Boat (2 cells)\n";
    cout << "   - Submarine (3 cells)\n";
    cout << "   - Destroyer (4 cells)\n";
    cout << "   - Battleship (5 cells)\n";
    cout << "4. Players take turns placing their ships on their own board.\n";
    cout << "   - Ships can be placed vertically or horizontally.\n";
    cout << "   - Ships cannot overlap.\n";
    cout << "5. Once all ships are placed, players take turns firing at the opponent's board.\n";
    cout << "   - A 'hit' is recorded if a cell containing a ship is targeted.\n";
    cout << "   - A 'miss' is recorded if the targeted cell is empty.\n";
    cout << "6. The game continues until all ships of one player are sunk.\n";
    cout << "**************************************************\n";
}
int chooseOpponent() {
    int choice;
    cout << "Choose your opponent:\n";
    cout << "1. Another Player\n";
    cout << "2. Computer\n";
    cout << "5. Exit\n";
    cin >> choice;
    if (choice == 5) exit(0);
    return choice;
}
int chooseBoardSize()
{
    const int MIN_BOARD_SIZE = 6;
    const int MAX_BOARD_SIZE = 10;
    cout << "Choose Board Size Between 6 and 10"<<endl;
    int choice=0;
    cin >> choice;
    while (choice < MIN_BOARD_SIZE || choice>MAX_BOARD_SIZE)
    {
        cout << "Incorrect Size| Enter New Size" << endl;
        
        cin >> choice;
    }
    return choice;
}
void printBoard(const vector<vector<char>> Board)
{
    const char leftLetters[] = { 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O' };
    //cout << "  ";
    
    for (int i = 0; i < Board.size(); i++)
    {
        //cout << i << "  ";
        cout << setw(4) << i+1 ;
    }
    cout << endl;
    for (int i = 0; i < Board.size(); i++)
    {
        cout << leftLetters[i] << " ";
        for (int j = 0; j < Board.size(); j++)
        {
            cout <<"[" << Board[i][j] <<"] ";
        }
        cout << endl;
    }
}
void placeShip(vector<vector<char>> board)
{

}
void placeShipRandom(vector<vector<char>> board)
{

}
bool isShipPlaceAble();
int chooseOpponent();
void playGame()
{
    int choice = chooseOpponent();
    const int BOARD_SIZE = chooseBoardSize();
    vector<vector<char>> player1Board(BOARD_SIZE, vector<char>(BOARD_SIZE, '.'));
    vector<vector<char>> player2Board(BOARD_SIZE, vector<char>(BOARD_SIZE, '.'));
    printBoard(player1Board);
    
}
void StartUp()
{
    while (true)
    {
        cout << ">1. Play: " << endl;
        cout << ">2. Rules:" << endl;
        cout << ">5. Exit:" << endl;
        unsigned int option;
        cin >> option;
        if (option == 5) return;
        else if (option == 2) printGameRules();
        else if (option == 1) break;
        else {
            cout << "Incorrect Choice\n" << endl;
        }
    }
    playGame();
}
int main()
{
    StartUp();

}

