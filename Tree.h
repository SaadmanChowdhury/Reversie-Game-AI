/*
 * S3:
 *      Created the Tree Class
 *      Added: generateChildren(), Suggest/Accept Move From Player();
 * S4:
 *      Added: destructor();
 *      Implemented: ~Tree(), destructor();
 *      Implemented: generateChildren(), nextPlayer();
 *      Implemented: suggestMovesToPlayer(),acceptNextMove();
 *      Added: makeMoveAsComputer();
 * S5:
 *      Tested: generateChildren(), nextPlayer();
 *      Tested: suggestMovesToPlayer(),acceptNextMove();
 *      Implemented: printLastBoardPosition();
 * S6:
 *      Implemented: makeMoveAsComputer(), heuRec();
 *      Tested: makeMoveAsComputer(), heuRec();
 * S7:
 *      Edited makeMoveAsComputer() and heuRec() -
 *      They have A-B-Pruning now *MAJOR*CHANGE*
 */


 /** TO DO**/
 /** (1) Implement makeMoveAsComputer() - MINIMAX!
     **/

#include "Board.h"

#ifndef TREE_H
#define TREE_H


class Tree{

private:
    struct item{
        string name;
        Board* board;
        vector<item*> children;
        int player;
    };
    int AIPlayer;
    item* root;
    item* lastMove;
    void generateChildren(item* parent); // Working
    void destructor(item* board); // Working?
    int nextPlayer(item* board); // Working
    int heuRec(item* now, int depth,string Type, int alpha, int beta);


public:
    Tree(Board* root, int AIPlayerNumber);
    ~Tree();
    string makeMoveAsComputer(int depth); // (!)INVOLVES MINIMAX(!)
    string suggestMovesToPlayer(); // Working
    bool acceptNextMove(string nextMove); // Working
    Board* getCurrentBoard(); // Working
    int getCurrentPlayer();
    void printLastBoardPosition();
};


#endif // TREE_H
