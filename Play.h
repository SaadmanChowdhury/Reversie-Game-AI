/*
 * S1:
 *      Added displayMessage()
 *      Added printBoard()
 * S6:
 *      printBoard editied to printAndPlay(); *MAJOR*CHANGE*
 */

/** TO DO:
 ** A way of requesting moves from player and AI and adding them - nextMove();
 ** MiniMax implementation
 **/

#include "Board.cpp"
#include "Tree.cpp"

#ifndef PLAY_H
#define PLAY_H

class Play{

private:
    Tree* tree;
    int player=1; //1 == BLACK | 2 == WHITE;
    int moveCounter=4;
    int depth;
    void displayMessage(int type);
    void nextMove();
    void bugTest1();
    void bugTest2(Board* parent);
    void computerFirstMove();

public:
    Play();
    bool printAndPlay();

};


#endif // PLAY_H

