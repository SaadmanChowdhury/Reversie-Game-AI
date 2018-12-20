
/*
 * S1:
 *      Implemented: Board() constructors
 *      Implemented: update(), trackRec()
 *      Tested: Board() constructors
 * S2:
 *      Tested: Update(),trackRec() - working
 * S4:
 *      BugFixed: ~Board();
 *      Added: boardValid;
 */

/** TO DO:
 ** (2) Heuristics value calculator
 **/

#include <bits/stdc++.h>
using namespace std;

#ifndef BOARD_H
#define BOARD_H

class Board{

private:
    int board[9][9];
    int** ark;
    int fitnessValue;
    bool boardValid; // Set to true if a valid move was made
    void update(int row, int col, int player);
    bool trackRec(int row, int col, int seekPlayer, int direction);

public:
    Board(); // WORKING
    Board(Board* parent, int row, int col, int player);
    ~Board();
    int** getBoard();
    bool isBoardValid();
    void printBoard();
    int defineHeuristics(int player);
};

#endif // BOARD_H

