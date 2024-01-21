
# Battleships Game

Battleships is a classic strategy game where players take turns to attack each other's fleets. This project implements the Battleships game in C++.

## Features

- Player vs. Player gameplay
- Player vs. Computer gameplay
- Customizable board size
- Random and manual ship placement options
- Save and load game functionality
- Informative game feedback
- ...

## Instructions
  1. When you start the game you will have an Options to choose:
     <details>
       <summary> Click to see the Picture</summary>
       
       ![image](https://github.com/darimachine/BattleShip_FMI/assets/67830778/392c0706-0a0c-4fde-9957-a2d119e0fc26)
     </details>
## Getting Started

To start the Battleships game, follow the steps below:

## Play Game

### Entering the Game

- **After Choosing to Play:** You will be prompted to enter the board size (let's assume it is 8):
  <details>
       <summary> Click to see the Picture</summary>
    
  ![Board Size](https://github.com/darimachine/BattleShip_FMI/assets/67830778/41ab4b3d-8a65-491e-817e-06cc8693a734)
  </details>
- **Manual Ship Configuration:** It will inquire whether you want to manually set the number of ships for the game:

   <details>
       <summary> Click to see the Picture</summary>
   
    ![Number of Ships](https://github.com/darimachine/BattleShip_FMI/assets/67830778/c828bef0-143d-4907-9b3b-41264ee73a55)
  </details>
  
- **Choosing 'Yes':**  If you choose 'Yes,' it will display the current count of each ship you have and then ask you to increase the count of the chosen ship:
  <details>
       <summary> Click to see the Picture</summary>
    
        ![Ship Count](https://github.com/darimachine/BattleShip_FMI/assets/67830778/170ca9a0-d096-47bf-87ea-daed60b60278)
  </details>

  <details>
       <summary> Click to see the Picture</summary>
    
    ![Increase Ship Count](https://github.com/darimachine/BattleShip_FMI/assets/67830778/3847e0d0-061c-405c-bfde-afaed9e4409c)
  </details>

### Choosing the Opponent

- **Choose Your Opponent:** Decide whether to play against another player or the computer:
  <details>
       <summary> Click to see the Picture</summary>
    
      ![Choose Opponent](https://github.com/darimachine/BattleShip_FMI/assets/67830778/d3f3f4a9-9b0e-4b62-b354-8296dda76513)
  </details>
  
- **Automatic Board Generation:** After choosing, it asks you whether to generate the board automatically:

 <details>
       <summary> Click to see the Picture</summary>
   
    ![Generate Board](https://github.com/darimachine/BattleShip_FMI/assets/67830778/5668c329-71c9-4bd0-bc7f-e76cb2e05bd4)
    
  </details>  

- **Ships and Board Overview:** View available ships and the current state of the board:
  <details>
       <summary> Click to see the Picture</summary>
    
    ![Ships and Board](https://github.com/darimachine/BattleShip_FMI/assets/67830778/3051edfc-1eb9-4365-8ed3-91408e91b9e8)
  </details>

  <details>
       <summary> Click to see the Picture</summary>
    
      ![Board State](https://github.com/darimachine/BattleShip_FMI/assets/67830778/948df0eb-afcc-435d-8588-5cbfcdae1bb1)
  </details>

### Playing the Game

- **Game Initialization:** After generating the board, it will display the player's board (for informational purposes) and ask Player 1 to start striking:
  <details>
       <summary> Click to see the Picture</summary>
    
      ![Player's Board](https://github.com/darimachine/BattleShip_FMI/assets/67830778/77cdcc4c-c787-411c-829c-488d755dae1a)
  </details>

- **Game Moves:** When Player 1 makes a move and hits, it provides information on whether it's a hit or miss and changes the color to red for a hit and green for a miss:

  <details>
       <summary> Click to see the Picture</summary>
    
      ![Hit Move](https://github.com/darimachine/BattleShip_FMI/assets/67830778/99a42107-4940-48e8-974c-af46562fbc1f)
  </details>

  <details>
       <summary> Click to see the Picture</summary>
    
      ![Miss Move](https://github.com/darimachine/BattleShip_FMI/assets/67830778/3024ca37-3e24-4cdc-8f9e-3d414fd6169b)
  </details>

- **Game Continuation:** The game continues until all ships of one player are sunk.

### Load Game

1. **Load Your Previously Played Game:** Resume your previous game instantly.
2. **Save Game Information:** All details about the game board and the current player's turn are saved.



   







## Added Extra Functionalities
```cpp
Player Vs Player
Play Agains Computer
Load Previous Game by knowing which player is on turn.
Automaticly Generate Boards
Dynamicly Set Board Size
Dynamicly Set How Many ships to be in game. And Implemented Limitation to it.
Nice Looking User Interface
Notifies user when some ship is sank

```
## Author

- [@darimachine](https://www.github.com/darimachine)
