#include "Tree.h"

#ifndef __TREE_H__
#define __TREE_H__

Tree:: Tree(Board* r, int AIPlayerNumber){

    AIPlayer = AIPlayerNumber;

    root = new item;
    root->name = "root";
    root->board = r;
    root->player = 0;

    lastMove = root;

}

Tree:: ~Tree(){
    destructor(root);
    lastMove = NULL;
}

void Tree:: destructor(item* board){

    if(board->children.size() == 0){
        delete board->board;
        board = NULL;
    }

    else{
        for(int i=board->children.size()-1;i>=0;i--){
            destructor(board->children[i]);
        }
    }

    return;
}

void Tree:: generateChildren(item* parent){

    if(parent->children.size()!=0)
        return;

    int** ark = parent->board->getBoard();

    char c1,c2;
    string s1,s2;
    for(int i=1;i<9;i++){
        for(int j=1;j<9;j++){

            if(ark[i][j]!=0)
                continue;

            Board* tempBoard = new Board(parent->board,i,j,nextPlayer(parent));

            if(tempBoard->isBoardValid()){

                item* newChild = new item;
                c1 = i+'0'; c2 = j+'a'-1; s1=c1; s2=c2;
                newChild->name = s1+s2;

                newChild->board = tempBoard;
                newChild->player = nextPlayer(parent);

                parent->children.push_back(newChild);
            }
            else delete tempBoard;

        }
    }
}

string Tree:: suggestMovesToPlayer(){
    if(lastMove->children.size()==0)
        generateChildren(lastMove);

    int n = lastMove->children.size();

    if(n==0){
        return "No Moves Available";
    }
    string s[n];

    for(int i=0;i<n;i++){
        s[i] = lastMove->children[i]->name;
    }

    string setOfMoves;
    for(int i=0;i<n-1;i++)
        setOfMoves += s[i] + " ";
    setOfMoves += s[n-1];

    return setOfMoves;
}

bool Tree:: acceptNextMove(string nextMove){
    if(nextMove=="No Moves Available"){
        Board* board = new Board(lastMove, 0, 0, 5);
        lastMove = board;
        board-
    }

    else{
        for(int i=0;i<lastMove->children.size();i++){
            if(lastMove->children[i]->name==nextMove){
                lastMove = lastMove->children[i];
                return true;
            }
        }
        return false;
    }
}

string Tree::makeMoveAsComputer(int depth){
    generateChildren(lastMove);

    if(lastMove->children.size()==0){
        acceptNextMove("No Moves Available");
        return "No Moves Available";
    }

    if(lastMove->children.size()==1){
        acceptNextMove(lastMove->children[0]->name);
        return lastMove->children[0]->name;
    }

    string maxMove; int maxVal=INT_MIN; int now;
    // best already explored option along path to the root for MAXIMIZER
    int alpha = INT_MIN;
    // best already explored option along path to the root for MINIMIZER
    int beta = INT_MAX;

    for(int i=0;i<lastMove->children.size();i++){
        if(maxVal > alpha)
            alpha = maxVal;
        now = heuRec(lastMove->children[i],depth-1, "MIN",alpha, beta);
        if(now > maxVal){
            maxVal = now;
            maxMove = lastMove->children[i]->name;
        }
    }
    acceptNextMove(maxMove);
    return maxMove;
}

int Tree:: heuRec(item* now, int depth, string Type, int alpha, int beta){
    if(depth==0)
        return now->board->defineHeuristics(now->player);

    generateChildren(now);

    if(Type=="MIN"){
        if(now->children.size()==0){
            return heuRec(now,depth-1,"MAX",alpha, beta);
        }

        int minVal=INT_MAX; int nowVal;

        for(int i=0;i<now->children.size();i++){
            if(minVal < beta)
                beta = minVal;

            nowVal = heuRec(now->children[i],depth-1, "MAX", alpha,beta);

            if(nowVal < minVal){
                minVal = nowVal;
            }

            if(nowVal < alpha)
                break; /** PRUNING **/
        }

        return minVal;
    }


    else{
        if(now->children.size()==0){
            return heuRec(now,depth-1,"MIN", alpha, beta);
        }

        int maxVal=INT_MIN; int nowVal;

        for(int i=0;i<now->children.size();i++){
            if(maxVal > alpha)
                alpha = maxVal;

            nowVal = heuRec(now->children[i],depth-1, "MIN", alpha, beta);

            if(nowVal > maxVal){
                maxVal = nowVal;
            }

            if(nowVal > beta)
                break; /** PRUNING **/
        }

        return maxVal;
    }
}

Board* Tree:: getCurrentBoard(){
    return lastMove->board;
}

void Tree::printLastBoardPosition(){
    lastMove->board->printBoard();
}

int Tree:: getCurrentPlayer(){
    return nextPlayer(lastMove);
}

int Tree:: nextPlayer(item* board){
    return (board->player % 2) + 1;
}
#endif //__TREE_H__
