// BattleShip_FMI.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <iomanip>
#include <ctime>
using namespace std;

constexpr int ALL_SHIPS = 4;
constexpr int ships[ALL_SHIPS] = { 2,3,4,5 }; // on index 0 equals ship 1 which is Boat and etc..
int howManyShips[ALL_SHIPS] = { 1,1,1,1 };
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
int enterOpponent() {
    int choice;
    cout << "Choose your opponent:\n";
    cout << "1. Another Player\n";
    cout << "2. Computer\n";
    cout << "5. Exit\n";
    cin >> choice;
    if (choice == 5) exit(0);
    return choice;
}
//
int enterBoardSize()
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
    //cout << "  ";
    for (int i = 0; i < Board.size(); i++)
    {
        //cout << i << "  ";
        cout << setw(4) << i+1 ;
    }
    cout << endl;
    for (int i = 0; i < Board.size(); i++)
    {
        cout << i+1 << " ";
        for (int j = 0; j < Board.size(); j++)
        {
            cout <<"[" << Board[i][j] <<"] ";
        }
        cout << endl;
    }
}
void enterNumberOfShips(int numberShips[], int boardSize)
{
    cout << "Which Ship";
}
/**
 * @brief Calculates the total number of remaining ships.
 *
 * This function takes an array representing the number of ships of each type
 * and returns the total number of remaining ships.
 *
 * @param ships An array representing the number of ships of each type.
 * @return The total number of remaining ships.
 */
int shipsLeft(int ships[])
{
    int sum = 0;
    for (int i = 0; i < ALL_SHIPS; i++)
    {
        sum += ships[i];
    }
    return sum;
}
/**
 * @brief Prints information about available ships.
 *
 * This function prints information about the available ships based on the
 * number of each ship type specified in the input array.
 *
 * @param howManyShips An array representing the number of each ship type.
 */
void printShips(const int howManyShips[])
{
    if (howManyShips[0] != 0)
    {
        cout << "1) - Patrol Boat (2) Spaces (P)" << endl;
    }
    if (howManyShips[1] != 0)
    {
        cout << "2) - Submarine (3) Spaces (S)" << endl;
    }
    if (howManyShips[2] != 0)
    {
        cout << "3) - Destroyer (4) Spaces (D)" << endl;
    }
    if (howManyShips[3] != 0)
    {
        cout << "4) - Aircraft carrier (5) Spaces (A)" << endl;
    }
}
bool isShipPlaceAble(const vector<vector<char>> board,int choice, unsigned int x, unsigned int y, unsigned int direction)
{
    int size = board.size()-1;
    if (x > size  || y > size) return false;
    for (int i = 0; i < ships[choice]; i++)
    {
        if (direction == 1)
        {
            if (y + i > size || board[x][y + i] != '.' ) return false;
        }
        else if (direction == 2)
        {
            if (x + i > size ||board[x+i][y] != '.') return false;
        }
    }
    return true;

    
}
void addShip(vector<vector<char>> &board, int choice, unsigned int x, unsigned int y, unsigned int direction)
{
    char shipName = ' ';
    if (choice == 0) shipName = 'P';
    if (choice == 1) shipName='S';
    if (choice == 2) shipName='D';
    if (choice == 3) shipName = 'A';
    if (direction == 1)
    {
        for (int i = 0; i < ships[choice]; i++)
        {
            board[x][y + i] = shipName;
        }
    }
    else if (direction == 2)
    {
        for (int i = 0; i < ships[choice]; i++)
        {
            board[x+i][y] = shipName;
        }
    }

}
void placeShip(vector<vector<char>>& board, int choice)
{
    
    while (true)
    {
        cout << "Will your ship be HORIZONTAL or VERCITAL from your starting point?" << endl;
        cout << "1) HORIZONTAL" << endl;
        cout << "2) VERTICAL" << endl;
        unsigned int shipDirection = 0;
        cin >> shipDirection;
        unsigned int x = 0;
        unsigned int y = 0;
        cout << "Enter Starting Point (x, y) ("<<1<<", "<< board.size() << ")" << endl;
        cin >> x;
        cin >> y;
        x--;
        y--;
        if (isShipPlaceAble(board, choice, x, y, shipDirection)) 
        {
            addShip(board, choice, x, y, shipDirection);
            break;
        }
        else {
            cout << "You cannot place ship there!!!"<<endl;
            continue;

        }
    }
}
void placeAllShips(vector<vector<char>> &board)
{
    
    while (shipsLeft(howManyShips) != 0)
    {
        cout << "Which ship would you like to place?" << endl;
        printShips(howManyShips);
        unsigned int choice = 0;
        cin >> choice;
        choice--; // I remove 1 because i dont want player to enter 0 as an choice of ship
        if (choice > 3 || howManyShips[choice]==0)
        {
            cout << "Incorrect Choice!!"<<endl;
            continue;
        }
        howManyShips[choice]--;
        placeShip(board, choice);
        printBoard(board);
    }
    

}
/* @brief Generate a random number between minand max
* @param Takes Min And Max
* @return Return Random Number Between Min And Max
*/ 
int getRandomNumber(int min, int max) {
    return min + rand() % (max - min + 1);
}
// Checking if Game is Over
bool isGameOver(vector<vector<char>> playerBoard, vector<vector<char>> attackedBoard)
{
    for (int i = 0; i < playerBoard.size(); i++)
    {
        for (int j = 0; j < playerBoard.size(); j++)
        {
            if (!(playerBoard[i][j] != '.') && (attackedBoard[i][j] != 'X'))
                return false;
        }
    }
    return true;
}
void placeRandomShip(vector<vector<char>>& board, int choice)
{
    int size = board.size() - 1;
    while (true)
    {
        unsigned int shipDirection = getRandomNumber(1, 2);
        unsigned int x;
        unsigned int y;
        //horizontal
        if (shipDirection == 1)
        {
            x = getRandomNumber(0, size);
            y = getRandomNumber(0, size - choice);
        }
        else if (shipDirection == 2)
        {
            x = getRandomNumber(0, size-choice);
            y = getRandomNumber(0, size);
        }
        // x = getRandomNumber(0,size-1)
        // y = getRandomNumber(0,(size-1)-choice)
        if (isShipPlaceAble(board, choice, x, y, shipDirection))
        {
            addShip(board, choice, x, y, shipDirection);
            break;
        }
        else {
            continue;
        }
    }
}
/**
 * @brief Validates the maximum number of ships based on the size of the game board.
 *
 * This function checks if the total number of ships selected by the user
 * does not exceed a specified limit based on the size of the game board.
 *
 * @param board The game board represented as a 2D vector.
 * @return Returns true if the number of ships is within the allowed limit;
 *         otherwise, returns false.
 */
bool numberOfShipsLimit(vector<vector<char>> board)
{
    const int LIMIT = board.size() * board.size(); /** < Maximum allowed number of ships is related to the total number of squares on the game board. */
    unsigned totalShips = 0; //** Accumulator for the total number of ships */.
    for (int i = 0; i < ALL_SHIPS; i++)  // Loop through each ship type and count the total number of ships.
    {
        for (int j = 0; j < howManyShips[i]; j++)
        {
            totalShips += ships[i]; // Add the size of each ship to the total.
        }
    }
    cout << totalShips;

    // Check if the total number of ships exceeds half of the available squares on the board.
    // If it does, return false indicating that the user has exceeded the allowed limit for ships.
    // Otherwise, return true, indicating that the user can add more ships.
    return (totalShips <= (LIMIT / 2));
}
void placeAllShipsRandom(vector<vector<char>> board)
{
    srand(time(0));
    while (shipsLeft(howManyShips) != 0)
    {

        unsigned int choice = getRandomNumber(0, 3);
        if (howManyShips[choice] == 0)
        {
            continue;
        }
        howManyShips[choice]--;
        placeRandomShip(board, choice);
        printBoard(board);
    }
}
void playGame()
{
    int choice = enterOpponent();
    const int BOARD_SIZE = enterBoardSize();
    vector<vector<char>> player1Board(BOARD_SIZE, vector<char>(BOARD_SIZE, '.'));
    vector<vector<char>> player2Board(BOARD_SIZE, vector<char>(BOARD_SIZE, '.'));
    printBoard(player1Board);
    placeAllShipsRandom(player1Board);
   
    
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

