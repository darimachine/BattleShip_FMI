
#include <iostream>
#include <vector> // vector
#include <iomanip>
#include <ctime>

#include <fstream>

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
/*Saving Game*/
void saveMatrix(ofstream& outFile, const vector<vector<char>>& matrix)
{
    int rows = matrix.size();
    // Save matrix elements
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < rows; ++j) {
            outFile << matrix[i][j] << " ";
        }
        outFile << endl;
    }
}
void loadMatrix(ifstream& inFile, vector<vector<char>>& matrix)
{
    // Read matrix dimensions
    int rows = matrix.size();
    // Read matrix elements
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < rows; ++j) {
            inFile >> matrix[i][j];
        }
    }
}
void saveGame(const vector<vector<char>>& player1Board,
    const vector<vector<char>>& player2Board,
    const vector<vector<char>>& player1AttackedBoard,
    const vector<vector<char>>& player2AttackedBoard,
    bool isPlayer1Turn, bool isPlayingToComputer)
{
    // Open the file for writing
    ofstream outFile("saved_game.txt");

    // Save information about the game state
    outFile << isPlayer1Turn << std::endl;
    outFile << isPlayingToComputer << std::endl;
    int rows = player1Board.size();
    outFile << rows << endl;

    // Save the matrices
    saveMatrix(outFile, player1Board);
    saveMatrix(outFile, player2Board);
    saveMatrix(outFile, player1AttackedBoard);
    saveMatrix(outFile, player2AttackedBoard);

    // Close the file
    outFile.close();
}

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
    while (true)
    {
        cout << "Choose your opponent:\n";
        cout << "1. Another Player\n";
        cout << "2. Computer\n";
        cout << "5. Exit\n";
        cin >> choice;
        if (choice == 5) exit(0);
        if (choice == 1 || choice == 2) break;
        else {
            cout << "Incorrect Input" << endl;
        }
    }

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
    cout << "Choose Board Size Between 6 and 10" << endl;
    int choice = 0;
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
void printBoard(const vector<vector<char>> board)
{
    cout << "    ";
    for (int i = 0; i < board.size(); i++)
    {
        //cout << i << "  ";
        if (i < 8) cout << i + 1 << "   ";
        else cout << i + 1 << "  ";
    }
    cout << endl;
    for (int i = 0; i < board.size(); i++)
    {
        if (i < 9) cout << i + 1 << "  ";
        else cout << i + 1 << " ";
        for (int j = 0; j < board.size(); j++)
        {
            if (board[i][j] == 'X') {
                // Print 'X' in red
                cout << "\033[1;31m" << "[" << "X" << "] " << "\033[0m";
            }
            else if (board[i][j] == 'O')
            {
                cout << "\033[1;32m" << "[" << "O" << "] " << "\033[0m";
            }
            else {
                cout << "[" << board[i][j] << "] ";
            }

        }
        cout << endl;
    }
    cout << endl;
}
/**
 * @brief Gets the total number of remaining ships.
 *
 * @param ships An array representing the number of ships of each type.
 * @return The total number of remaining ships.
 */
int getTotalRemainingShips(const int ships[])
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
        cout << "1) - Patrol Boat (2) Spaces (P)" << setw(2) << "(" << howManyShips[0] << " left)" << endl;
    }
    if (howManyShips[1] != 0)
    {
        cout << "2) - Submarine (3) Spaces (S)" << setw(2) << "(" << howManyShips[1] << " left)" << endl;
    }
    if (howManyShips[2] != 0)
    {
        cout << "3) - Destroyer (4) Spaces (D)" << setw(2) << "(" << howManyShips[2] << " left)" << endl;
    }
    if (howManyShips[3] != 0)
    {
        cout << "4) - Aircraft carrier (5) Spaces (A)" << setw(2) << "(" << howManyShips[3] << " left)" << endl;
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
bool canPlaceShip(const vector<vector<char>> board, int choice, unsigned int x, unsigned int y, unsigned int direction)
{
    int size = board.size() - 1;
    if (x > size || y > size) return false;
    for (int i = 0; i < ships[choice]; i++)
    {
        if (direction == 1)
        {
            if (y + i > size || board[x][y + i] != '.') return false;
        }
        else if (direction == 2)
        {
            if (x + i > size || board[x + i][y] != '.') return false;
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
void addShipToBoard(vector<vector<char>>& board, int choice, unsigned int x, unsigned int y, unsigned int direction)
{
    char shipName = ' ';
    if (choice == 0) shipName = 'P';
    if (choice == 1) shipName = 'S';
    if (choice == 2) shipName = 'D';
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
            board[x + i][y] = shipName;
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
        if (shipDirection != 1 && shipDirection != 2)
        {
            cout << "Incorrect Choice" << endl;
            continue;
        }
        unsigned int x = 0;
        unsigned int y = 0;
        cout << "Enter Starting Point (x, y) (" << 1 << ", " << board.size() << ")" << endl;
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
            cout << "You cannot place ship there!!!" << endl;
            continue;

        }
    }
}
void copyAvaibleShips(int* copy)
{
    for (int i = 0; i < NUM_SHIP_TYPES; i++)
    {
        copy[i] = availableShips[i];
    }
}
/**
 * @brief Places all ships on the game board.
 *
 * @param board The game board represented as a 2D vector.
 */
void placeAllShipsOnBoard(vector<vector<char>>& board)
{
    int copy[NUM_SHIP_TYPES];
    copyAvaibleShips(copy);
    while (getTotalRemainingShips(copy) != 0)
    {

        cout << "Which ship would you like to place?" << endl;
        printBoard(board);
        displayAvailableShips(copy);
        unsigned int choice = 0;
        cin >> choice;
        choice--; // I remove 1 because i dont want player to enter 0 as an choice of ship
        if (choice > 3 || copy[choice] == 0)
        {
            cout << "Incorrect Choice!!" << endl;
            continue;
        }
        copy[choice]--;
        placeShipWithUserInput(board, choice);
    }
    printBoard(board);


}
/**
 * @brief Checks if the specified coordinates are valid for an attack on the given attacked board.
 *
 * @param attackedBoard The board representing the attacked state.
 * @param x The x-coordinate of the attack.
 * @param y The y-coordinate of the attack.
 * @return True if the coordinates are valid (not out of bounds and not already attacked), false otherwise.
 *
 * This function ensures that the attack coordinates (x, y) are within the bounds of the attacked board.
 * Additionally, it checks whether the specified square has not been attacked before, i.e., it is not marked
 * as 'X' (hit) or 'O' (missed). The function returns true if the coordinates are valid for an attack and false otherwise.
 */
bool isValidCoordinates(vector<vector<char>> attackedBoard, unsigned int x, unsigned int y)
{
    int size = attackedBoard.size() - 1;
    if (x > size || y > size) return false;
    if (attackedBoard[x][y] == 'X' || attackedBoard[x][y] == 'O') return false;
    return true;
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
            if ((playerBoard[i][j] != '.') && (attackedBoard[i][j] != 'X'))
                return false;
        }
    }
    return true;
}

/* @brief Generate a random number between minand max
* @param Takes Min And Max
* @return Return Random Number Between Min And Max
*/
int getRandomNumber(int min, int max) {
    return min + rand() % (max - min + 1);
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
            x = getRandomNumber(0, size - choice);
            y = getRandomNumber(0, size);
        }
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
 * @brief Places all ships randomly on the game board for a player.
 *
 * This function randomly selects ships and places them on the board until all ships are placed.
 * It uses the placeRandomShip function and updates the available ships accordingly.
 *
 * @param board The game board represented as a 2D vector.
 */
void placeAllShipsRandomly(vector<vector<char>>& board)
{

    int copy[NUM_SHIP_TYPES] = {};
    copyAvaibleShips(copy);
    while (getTotalRemainingShips(copy) != 0)
    {
        unsigned int choice = getRandomNumber(0, 3);
        if (copy[choice] == 0)
        {
            continue;
        }
        copy[choice]--;
        placeRandomShip(board, choice);
        //printBoard(board);
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
    unsigned totalShips = 0;
    for (int i = 0; i < NUM_SHIP_TYPES; i++)
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
 * @brief Allows the player to choose whether to set the number of ships manually.
 *
 * This function prompts the player to decide whether they want to manually set the number of ships or use the default configuration.
 * The default configuration includes 1 Patrol Boat (2 cells), 1 Submarine (3 cells), 1 Destroyer (4 cells), and 1 Aircraft Carrier (5 cells).
 * The player can choose to customize the ship count or proceed with the default configuration.
 *
 * @return An integer representing the player's choice: 1 for manual ship count, 2 for default configuration.
 */
int chooseShipCount()
{
    unsigned choice = 0;
    while (true)
    {
        cout << "Do you want to set mannualy how many ships would be there?" << endl;
        cout << "Default:\n \
        1 - Patrol Boat(2 cells)\n \
        1 - Submarine(3 cells)\n \
        1 - Destroyer(4 cells)\n \
        1 - Aircraft carrier(5 cells) \
        " << endl;
        cout << " 1) Yes\n 2) No\n";

        cin >> choice;
        if (choice != 1 && choice != 2) {
            cout << "Incorrect Choice" << endl;
        }
        else {
            break;
        }
    }
    return choice;
}
/**
 * @brief Allows the player to customize the number of each type of ship on the board.
 *
 * @param boardSize The size of the game board.
 *
 * This function prompts the player whether they want to manually set the number of each ship type on the board.
 * If the player chooses to customize, they can selectively increase the count of each ship type.
 * The available counts for each ship type are displayed, and the player can choose which ship to add more of.
 * The function ensures that the total number of ships does not exceed the limit for the given board size.
 * The process continues until the player decides not to add more ships or reaches the limit.
 */
void setShipCount(int boardSize)
{
    unsigned choice = chooseShipCount();
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
            if (choice == 8) return;
            if (choice > 3)
            {
                cout << "Incorrect Input\n";
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
}
/**
 * @brief Allows the player to choose how to set up their game board.
 *
 * This function prompts the player to decide whether they want to generate their game board automatically or manually.
 * It then calls the appropriate function to place ships on the board based on the player's choice.
 *
 * @param board The game board to be populated with ships.
 */
void chooseBoard(vector<vector<char>>& board)
{
    cout << "Do you want to generate Your Board Automaticly?" << endl;
    cout << "1) Yes" << endl;
    cout << "2) No" << endl;
    unsigned int choice = 0;
    cin >> choice;
    while (true)
    {
        if (choice == 1)
        {
            placeAllShipsRandomly(board);
            break;
        }
        else if (choice == 2)
        {
            placeAllShipsOnBoard(board);
            break;
        }
        else {
            cout << "Incorrect Input" << endl;
            cin >> choice;
        }
    }

}
/**
 * @brief Updates the status of sunk ships based on the player's attacks and updates available ships.
 *
 * This function iterates over the player and attacked boards to check the status of each ship type.
 * It updates the counters for each ship type based on successful attacks and provides feedback if a ship is sunk.
 * The function also updates the available ships array accordingly.
 *
 * @param playerBoard The opponent's game board containing ship locations.
 * @param attackedBoard The board tracking attacks on the opponent's ships.
 * @param copyAvailableShips An array tracking the available ships for the opponent.
 */
void sunkedShips(const vector<vector<char>> playerBoard, vector<vector<char>>& attackedBoard, int* copyAvaibleShips)
{
    int counterPetrolBoat = 0;
    int counterSubMarine = 0;
    int counterDestroyer = 0;
    int counterAircraft = 0;
    int size = playerBoard.size();
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (copyAvaibleShips[0] != 0 && playerBoard[i][j] == 'P' && attackedBoard[i][j] == 'X')
            {
                counterPetrolBoat++;
            }
            if (copyAvaibleShips[1] != 0 && playerBoard[i][j] == 'S' && attackedBoard[i][j] == 'X')
            {
                counterSubMarine++;
            }
            if (copyAvaibleShips[2] != 0 && playerBoard[i][j] == 'D' && attackedBoard[i][j] == 'X')
            {
                counterDestroyer++;
            }
            if (copyAvaibleShips[3] != 0 && playerBoard[i][j] == 'A' && attackedBoard[i][j] == 'X')
            {
                counterAircraft++;
            }
        }
    }
    if (counterPetrolBoat == ships[0])
    {
        cout << "\033[1;31m" << "You Sank Enemy Patrol Boat" << "\033[0m" << endl;
        copyAvaibleShips[0]--;
    }
    if (counterSubMarine == ships[1])
    {
        cout << "\033[1;31m" << "You Sank Enemy Submarine" << "\033[0m" << endl;
        copyAvaibleShips[1]--;
    }
    if (counterDestroyer == ships[2])
    {
        cout << "\033[1;31m" << "You Sank Enemy Destroyer" << "\033[0m" << endl;
        copyAvaibleShips[2]--;
    }
    if (counterAircraft == ships[3])
    {
        cout << "\033[1;31m" << "You Sank Enemy AirCraft" << "\033[0m" << endl;
        copyAvaibleShips[3]--;
    }

}
/**
 * @brief Allows the player to choose coordinates to strike on the opponent's board in Battleships.
 *
 * This function prompts the player to input coordinates (x, y) for their attack.
 * The input is validated, and the function returns true if the player chooses to save the game and exit.
 * After a valid attack position is chosen, the function updates the attacked board and provides feedback
 * on whether the attack resulted in a hit or a miss.
 *
 * @param playerBoard The opponent's game board containing ship locations.
 * @param attackedBoard The board tracking attacks on the opponent's ships.
 * @param copyAvailableShips An array tracking the available ships for the opponent.
 * @return True if the player chooses to save the game and exit, false otherwise.
 */
bool hitShip(const vector<vector<char>> playerBoard, vector<vector<char>>& attackedBoard, int* copyAvailableShips)
{

    int x, y;
    while (true)
    {
        cout << "Choose (x ,y) coordinates to Strike                         !!!Type x=99 and y=99 To Save The Game and EXIT" << endl;
        cin >> x >> y;
        if (x == 99 && y == 99) return true;
        x--;
        y--;
        if (!isValidCoordinates(attackedBoard, x, y))
        {
            cout << "Incorrect square to Strike!! Try Again" << endl;
            continue;
        }
        break;

    }
    if (playerBoard[x][y] == '.') {
        attackedBoard[x][y] = 'O';
        cout << "\033[1;33m" << "You Missed" << "\033[0m" << endl;

    }
    else {
        attackedBoard[x][y] = 'X';
        cout << "\033[1;34m" << "You Hit" << "\033[0m" << endl;

        sunkedShips(playerBoard, attackedBoard, copyAvailableShips);
    }
    return false;
}
/**
 * @brief Simulates a random attack by the computer on the player's board in Battleships.
 *
 * This function randomly selects coordinates on the player's board to launch an attack.
 * It checks if the coordinates are valid and updates the attacked board accordingly.
 * It also provides feedback on whether the attack resulted in a hit or a miss.
 *
 * @param playerBoard The player's game board containing ship locations.
 * @param attackedBoard The board tracking attacks on the player's ships.
 * @param copyAvailableShips An array tracking the available ships for the player.
 */
void hitShipRandomly(const vector<vector<char>> playerBoard, vector<vector<char>>& attackedBoard, int* copyAvailableShips)
{
    int size = playerBoard.size() - 1;
    int x, y;
    while (true)
    {
        x = getRandomNumber(0, size);
        y = getRandomNumber(0, size);
        if (!isValidCoordinates(attackedBoard, x, y))
        {
            continue;
        }
        break;
    }
    if (playerBoard[x][y] == '.') {
        attackedBoard[x][y] = 'O';
        cout << "\033[1;33m" << "Computer Missed" << "\033[0m" << endl;

    }
    else {
        attackedBoard[x][y] = 'X';
        cout << "\033[1;34m" << "Computer Hit" << "\033[0m" << endl;

        sunkedShips(playerBoard, attackedBoard, copyAvailableShips);
    }
}
/**
 * @brief Manages the gameplay for a Player vs. Player match in Battleships.
 *
 * This function handles the turn-by-turn interactions between two players,
 * allowing them to attack each other's boards. It incorporates logic for hitting
 * ships, displaying boards, saving the game, and checking for game-over conditions.
 *
 * @param player2Board The game board for Player 2.
 * @param player2AttackedBoard The attacked board for Player 2.
 * @param player1Board The game board for Player 1.
 * @param player1AttackedBoard The attacked board for Player 1.
 * @param isPlayer1Turn A flag indicating whether it is Player 1's turn.
 */
void playPlayerVsPlayer(vector<vector<char>>& player2Board, vector<vector<char>>& player2AttackedBoard, vector<vector<char>>& player1Board,
    vector<vector<char>>& player1AttackedBoard, bool isPlayer1Turn)
{
    constexpr bool isPlayingWithComputer = false;
    /* Saving the avaible ships in the board. After that keeping track which one was sank*/
    int copyPlayer1Ships[NUM_SHIP_TYPES];
    copyAvaibleShips(copyPlayer1Ships);
    int copyPlayer2Ships[NUM_SHIP_TYPES];
    copyAvaibleShips(copyPlayer2Ships);
    while (true)
    {
        if (isPlayer1Turn)
        {
            cout << "Player 2 Board\n---------------------------------\n";
            printBoard(player2AttackedBoard);
            cout << "Player 1 On Turn" << endl;
            if (hitShip(player2Board, player2AttackedBoard, copyPlayer2Ships))
            {
                saveGame(player1Board, player2Board, player1AttackedBoard, player2AttackedBoard, isPlayer1Turn, isPlayingWithComputer);
                exit(0);
            }
            isPlayer1Turn = false;
            printBoard(player2AttackedBoard);
            cout << "\033[1;31m" << "-----------------------------------" << "\033[0m" << endl;
        }
        else {
            cout << "Player 1 Board\n---------------------------------\n";
            printBoard(player1AttackedBoard);
            cout << "Player 2 On Turn" << endl;
            if (hitShip(player1Board, player1AttackedBoard, copyPlayer1Ships))
            {
                saveGame(player1Board, player2Board, player1AttackedBoard, player2AttackedBoard, isPlayer1Turn, isPlayingWithComputer);
                exit(0);
            }
            isPlayer1Turn = true;
            printBoard(player1AttackedBoard);
            cout << "\033[1;31m" << "-----------------------------------" << "\033[0m" << endl;
        }
        if (isGameOver(player1Board, player1AttackedBoard)) {
            cout << "\033[1;32m" << "Player 2 WON" << "\033[0m";
            exit(0);
        }
        if (isGameOver(player2Board, player2AttackedBoard)) {
            cout << "\033[1;32m" << "Player 1 WON" << "\033[0m";

            exit(0);
        }
    }
}
/**
 * @brief Manages the gameplay for a Player vs. Computer match in Battleships.
 *
 * This function handles the turn-by-turn interactions between the player and
 * the computer, allowing them to attack each other's boards. It incorporates
 * logic for hitting ships, displaying boards, saving the game, and checking for
 * game-over conditions.
 *
 * @param player2Board The computer's game board.
 * @param player2AttackedBoard The computer's attacked board.
 * @param player1Board The player's game board.
 * @param player1AttackedBoard The player's attacked board.
 */
void playPlayerVsComputer(std::vector<std::vector<char>>& player2Board, std::vector<std::vector<char>>& player2AttackedBoard, std::vector<std::vector<char>>& player1Board, std::vector<std::vector<char>>& player1AttackedBoard)
{
    constexpr bool isPlayingWithComputer = true;
    int copyPlayer1Ships[NUM_SHIP_TYPES];
    copyAvaibleShips(copyPlayer1Ships);
    int copyComputerShips[NUM_SHIP_TYPES];
    copyAvaibleShips(copyComputerShips);
    bool isPlayerTurn = true;
    while (true)
    {
        if (isPlayerTurn) {
            cout << "Computer Board\n---------------------------------\n";
            printBoard(player2AttackedBoard);
            cout << "Player On Turn" << endl;
            if (hitShip(player2Board, player2AttackedBoard, copyComputerShips))
            {
                saveGame(player1Board, player2Board, player1AttackedBoard, player2AttackedBoard, isPlayerTurn, isPlayingWithComputer);
                exit(0);
            }
            printBoard(player2AttackedBoard);
            cout << "\033[1;31m" << "-----------------------------------" << "\033[0m" << endl;
            isPlayerTurn = false;
        }
        else {
            /*cout << "Player Board\n--------------------------" << endl;
            printBoard(player1Board);*/
            cout << "Computer On Turn" << endl;
            hitShipRandomly(player1Board, player1AttackedBoard, copyPlayer1Ships);
            printBoard(player1AttackedBoard);
            cout << "\033[1;31m" << "-----------------------------------" << "\033[0m" << endl;
            isPlayerTurn = true;
        }
        if (isGameOver(player1Board, player1AttackedBoard)) {
            cout << "\033[1;32m" << "Computer WON" << "\033[0m";
            exit(0);
        }
        if (isGameOver(player2Board, player2AttackedBoard)) {
            cout << "\033[1;32m" << "Player WON" << "\033[0m";

            exit(0);
        }
    }
}
/**
 * @brief Initiates and manages the execution of the Battleships game.
 *
 * This function handles the flow of the Battleships game, allowing players
 * to either start a new game or load a previously saved one. It manages the
 * game state, boards, and player turns by calling appropriate helper functions.
 *
 * @param isLoadGame A boolean flag indicating whether to load a saved game.
 *                   If true, the function loads the game state from a file.
 *                   If false, it initiates a new game with user inputs.
 */
void playGame(bool isLoadGame)
{
    if (isLoadGame) {
        ifstream inFile("saved_game.txt");
        bool isPlayer1Turn, isPlayingToComputer;
        // Load information about the game state
        inFile >> isPlayer1Turn;
        inFile >> isPlayingToComputer;
        int size;
        inFile >> size;
        vector<vector<char>> player1Board(size, vector<char>(size, '.'));
        vector<vector<char>> player2Board(size, vector<char>(size, '.'));
        vector<vector<char>> player1AttackedBoard(size, vector<char>(size, '.'));
        vector<vector<char>> player2AttackedBoard(size, vector<char>(size, '.'));
        // Load the matrices
        loadMatrix(inFile, player1Board);
        loadMatrix(inFile, player2Board);
        loadMatrix(inFile, player1AttackedBoard);
        loadMatrix(inFile, player2AttackedBoard);

        // Close the file
        inFile.close();
        if (isPlayingToComputer) {
            playPlayerVsComputer(player2Board, player2AttackedBoard, player1Board, player1AttackedBoard);
        }
        else {
            playPlayerVsPlayer(player2Board, player2AttackedBoard, player1Board, player1AttackedBoard, isPlayer1Turn);
        }

    }
    else {
        const int BOARD_SIZE = enterBoardSize();
        vector<vector<char>> player1Board(BOARD_SIZE, vector<char>(BOARD_SIZE, '.'));
        vector<vector<char>> player2Board(BOARD_SIZE, vector<char>(BOARD_SIZE, '.'));
        vector<vector<char>> player1AttackedBoard(BOARD_SIZE, vector<char>(BOARD_SIZE, '.'));
        vector<vector<char>> player2AttackedBoard(BOARD_SIZE, vector<char>(BOARD_SIZE, '.'));
        setShipCount(BOARD_SIZE);
        int choice = chooseOpponent();
        cout << "Player 1:" << endl;
        chooseBoard(player1Board);
        if (choice == 2) {

            placeAllShipsRandomly(player2Board);
            cout << "Player Board" << endl;
            printBoard(player1Board);
            playPlayerVsComputer(player2Board, player2AttackedBoard, player1Board, player1AttackedBoard);
        }
        else if (choice == 1) {
            cout << "Player 2:" << endl;
            chooseBoard(player2Board);
            printBoard(player1Board);
            printBoard(player2Board);
            playPlayerVsPlayer(player2Board, player2AttackedBoard, player1Board, player1AttackedBoard, true);
        }
    }


}

/**
 * @brief Initiates the Battleships game by allowing the player to choose an opponent and board size.
 *
 * This function prompts the user to choose an opponent, provides game rules if requested,
 * and starts the game by initializing the game board and placing all ships randomly.
 */
void StartUp()
{
    srand(time(0));
    bool isLoadGame = false;
    while (true)
    {
        cout << ">1. Play New Game: " << endl;
        cout << ">2. Load Game: " << endl;
        cout << ">3. Rules:" << endl;
        cout << ">5. Exit:" << endl;
        unsigned int option;
        cin >> option;
        if (option == 2)
        {
            isLoadGame = true;
            break;
        }
        if (option == 5) return;
        else if (option == 3) printGameRules();
        else if (option == 1) break;
        else {
            cout << "Incorrect Choice\n" << endl;
        }
    }
    playGame(isLoadGame);
}
int main()
{
    StartUp();
}

