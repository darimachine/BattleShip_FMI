// BattleShip_FMI.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <iomanip>
#include <ctime>
#include "BattleShip_FMI.h"
using namespace std;

/**
 * @brief The total number of ship types in the game.
 */
constexpr int NUM_SHIP_TYPES = 4;
/**
 * @brief An array representing the size of each ship type.
 *
 * The index corresponds to the ship type:
 *   - Index 0: Patrol Boat (2 cells)
 *   - Index 1: Submarine (3 cells)
 *   - Index 2: Destroyer (4 cells)
 *   - Index 3: Battleship (5 cells)
 */
constexpr int ships[NUM_SHIP_TYPES] = { 2,3,4,5 }; // on index 0 equals ship 1 which is Boat and etc..
/**
 * @brief An array representing the initial number of each ship type available to players.
 */
int availableShips[NUM_SHIP_TYPES] = { 1,1,1,1 };

/**
 * @brief Prints the rules of the Battleships game to the console.
 */
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
/**
 * @brief Prompts the user to choose an opponent (Another Player, Computer, or Exit).
 * @return The user's choice for the opponent.
 */
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
/**
 * @brief Prompts the user to enter the desired board size between 6 and 10.
 * @return The user's choice for the board size.
 */
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
/**
 * @brief Prints the game board to the console.
 * @param Board The game board represented as a 2D vector.
 */
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
 * @brief Gets the total number of remaining ships.
 *
 * @param ships An array representing the number of ships of each type.
 * @return The total number of remaining ships.
 */
int getTotalRemainingShips(int ships[])
{
    int sum = 0;
    for (int i = 0; i < NUM_SHIP_TYPES; i++)
    {
        sum += ships[i];
    }
    return sum;
}
/**
 * @brief Displays information about available ship types.
 *
 * @param availableShips An array representing the number of each ship type.
 */
void displayAvailableShips(const int howManyShips[])
{
    if (howManyShips[0] != 0)
    {
        cout << "1) - Patrol Boat (2) Spaces (P)" << setw(2)<<"(" << howManyShips[0] << " left)" << endl;
    }
    if (howManyShips[1] != 0)
    {
        cout << "2) - Submarine (3) Spaces (S)" <<setw(2) << "(" << howManyShips[1] << " left)" << endl;
    }
    if (howManyShips[2] != 0)
    {
        cout << "3) - Destroyer (4) Spaces (D)" <<setw(2) << "(" << howManyShips[2] << " left)" << endl;
    }
    if (howManyShips[3] != 0)
    {
        cout << "4) - Aircraft carrier (5) Spaces (A)" <<setw(2)<<"(" << howManyShips[3] << " left)" << endl;
    }
}
/**
 * @brief Checks if a ship can be placed at the specified position and direction on the board.
 *
 * @param board The game board represented as a 2D vector.
 * @param shipType The index representing the type of the ship to be placed.
 * @param startX The starting x-coordinate for placing the ship.
 * @param startY The starting y-coordinate for placing the ship.
 * @param direction The direction of the ship (1 for horizontal, 2 for vertical).
 * @return True if the ship can be placed; false otherwise.
 */
bool canPlaceShip(const vector<vector<char>> board,int choice, unsigned int x, unsigned int y, unsigned int direction)
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
/**
 * @brief Adds a ship to the game board at the specified position and direction.
 *
 * @param board The game board represented as a 2D vector.
 * @param shipType The index representing the type of the ship to be added.
 * @param startX The starting x-coordinate for placing the ship.
 * @param startY The starting y-coordinate for placing the ship.
 * @param direction The direction of the ship (1 for horizontal, 2 for vertical).
 */
void addShipToBoard(vector<vector<char>> &board, int choice, unsigned int x, unsigned int y, unsigned int direction)
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
/**
 * @brief Places a ship on the game board with user input.
 *
 * @param board The game board represented as a 2D vector.
 * @param shipType The index representing the type of the ship to be placed.
 */
void placeShipWithUserInput(vector<vector<char>>& board, int choice)
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
        if (canPlaceShip(board, choice, x, y, shipDirection)) 
        {
            addShipToBoard(board, choice, x, y, shipDirection);
            break;
        }
        else {
            cout << "You cannot place ship there!!!"<<endl;
            continue;

        }
    }
}
/**
 * @brief Places all ships on the game board.
 *
 * @param board The game board represented as a 2D vector.
 */
void placeAllShipsOnBoard(vector<vector<char>> &board)
{
    
    while (getTotalRemainingShips(availableShips) != 0)
    {
        cout << "Which ship would you like to place?" << endl;
        displayAvailableShips(availableShips);
        unsigned int choice = 0;
        cin >> choice;
        choice--; // I remove 1 because i dont want player to enter 0 as an choice of ship
        if (choice > 3 || availableShips[choice]==0)
        {
            cout << "Incorrect Choice!!"<<endl;
            continue;
        }
        availableShips[choice]--;
        placeShipWithUserInput(board, choice);
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
/**
 * @brief Checks if the game is over by determining if all ships on the player's board have been sunk.
 *
 * This function compares the player's board with the attacked board to check if all ship cells have been hit.
 *
 * @param playerBoard The player's game board represented as a 2D vector.
 * @param attackedBoard The opponent's game board with recorded attacks represented as a 2D vector.
 * @return True if all ships on the player's board have been sunk; false otherwise.
 */
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
/**
 * @brief Places a ship randomly on the game board for the computer player.
 *
 * This function randomly generates a starting position and direction for a ship
 * and attempts to place it on the board. It ensures the ship can be placed
 * by calling canPlaceShip and adds the ship using addShipToBoard.
 *
 * @param board The game board represented as a 2D vector.
 * @param choice The index representing the type of the ship to be placed.
 */
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
        if (canPlaceShip(board, choice, x, y, shipDirection))
        {
            addShipToBoard(board, choice, x, y, shipDirection);
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
bool numberOfShipsLimit(int size)
{
    const int LIMIT = size * size; /** < Maximum allowed number of ships is related to the total number of squares on the game board. */
    unsigned totalShips = 0; //** Accumulator for the total number of ships */.
    for (int i = 0; i < NUM_SHIP_TYPES; i++)  // Loop through each ship type and count the total number of ships.
    {
        for (int j = 0; j < availableShips[i]; j++)
        {
            totalShips += ships[i]; // Add the size of each ship to the total.
        }
    }
    //cout << totalShips;
    // Check if the total number of ships exceeds half of the available squares on the board.
    // If it does, return false indicating that the user has exceeded the allowed limit for ships.
    // Otherwise, return true, indicating that the user can add more ships.
    return (totalShips <= (LIMIT / 2));
}
/**
 * @brief Places all ships randomly on the game board for a player.
 *
 * This function randomly selects ships and places them on the board until all ships are placed.
 * It uses the placeRandomShip function and updates the available ships accordingly.
 *
 * @param board The game board represented as a 2D vector.
 */
void placeAllShipsRandomly(vector<vector<char>> board)
{
    srand(time(0));
    while (getTotalRemainingShips(availableShips) != 0)
    {
        unsigned int choice = getRandomNumber(0, 3);
        if (availableShips[choice] == 0)
        {
            continue;
        }
        availableShips[choice]--;
        placeRandomShip(board, choice);
        printBoard(board);
    }
}
void setShipCount(int boardSize)
{
    cout << "Do you want to set mannualy how many ships would be there?" << endl;
    cout << "Default:\n \
        1 - Patrol Boat(2 cells)\n \
        1 - Submarine(3 cells)\n \
        1 - Destroyer(4 cells)\n \
        1 - Aircraft carrier(5 cells) \
        " << endl;
    cout << " 1) Yes\n 2) No\n";
    unsigned choice = 0;
    cin >> choice;
    if (choice == 1)
    {
        while (true)
        {
            
            cout << "Which boat you want to increase\n";
            cout << "1) - Patrol Boat (2) Spaces (P)" << setw(2) << "(" << availableShips[0] << " left)" << endl;
            cout << "2) - Submarine (3) Spaces (S)" << setw(2) << "(" << availableShips[1] << " left)" << endl;
            cout << "3) - Destroyer (4) Spaces (D)" << setw(2) << "(" << availableShips[2] << " left)" << endl;
            cout << "4) - Aircraft carrier (5) Spaces (A)" << setw(2) << "(" << availableShips[3] << " left)" << endl;
            cout << "9) - I Dont Want To Add More" << endl;

            unsigned int choice = 0;
            cin >> choice;
            choice--; // because of 0 index
            if (choice == 9) return;
            if (choice > 3)
            {
                cout << "Incorrect Input";
                continue;
            }
            availableShips[choice]++;
            if (!numberOfShipsLimit(boardSize))
            {
                cout << "You exceeded the LIMIT!!! You cannot add more ships" << endl;
                availableShips[choice]--;
                break;
            }
        }
        
    }

    return;

}
void playGame()
{
    const int BOARD_SIZE = enterBoardSize();
    setShipCount(BOARD_SIZE);
    int choice = chooseOpponent();
    
    vector<vector<char>> player1Board(BOARD_SIZE, vector<char>(BOARD_SIZE, '.'));
    vector<vector<char>> player2Board(BOARD_SIZE, vector<char>(BOARD_SIZE, '.'));
    printBoard(player1Board);
    placeAllShipsOnBoard(player1Board);
}



/**
 * @brief Initiates the Battleships game by allowing the player to choose an opponent and board size.
 *
 * This function prompts the user to choose an opponent, provides game rules if requested,
 * and starts the game by initializing the game board and placing all ships randomly.
 */
void StartUp()
{
    while (true)
    {
        cout << ">1. Play New Game: " << endl;
        cout << ">2. Load Game: " << endl;
        cout << ">3. Rules:" << endl;
        cout << ">5. Exit:" << endl;
        unsigned int option;
        cin >> option;
        if (option == 5) return;
        else if (option == 3) printGameRules();
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

