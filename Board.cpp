#include "Board.h"

#ifndef __BOARD_H__
#define __BOARD_H__

/***** CONSTRUCTORS / DESTROCTORS *****/

Board::Board(){
    for(int i=1;i<9;i++)
        for(int j=1;j<9;j++)
            board[i][j]=0;

    board[4][4]=2;
    board[5][5]=2;
    board[4][5]=1;
    board[5][4]=1;

    ark = new int*[9];
    for(int i=0;i<9;i++)
        ark[i]= board[i];

    boardValid = true;
}

Board::Board(Board* parent, int row, int col, int player){
    int** pos;
    pos = parent->getBoard();

    for(int i=1;i<9;i++){
        for(int j=1;j<9;j++)
            board[i][j]=pos[i][j];
    }

    boardValid = false;

    board[row][col] = player;
    update(row,col,player);

    ark = new int*[9];
    for(int i=0;i<9;i++)
        ark[i]=board[i];
}

//Board::Board()

Board::~Board(){

    for(int i=0;i<9;i++)
        ark[i] = NULL;

    delete[](ark);

}


/***** PROCESSESS *****/
void Board::update(int row, int col, int player){

    /** Direction type **/
    /* Resembles faces of a clock
     * 3 - to East
     * 6 - to South
     * 9 - to West
     * 12 - to North
     * 1 - North East
     * 5 - South East
     * 7 - South West
     * 11 - North West
     */

    //Check Left to Right
    trackRec(row,col+1,player,3);
    trackRec(row,col-1,player,9);

    //Check Top to Bottom
    trackRec(row+1,col,player,6);
    trackRec(row-1,col,player,12);

    //Check Diagonal y = x
    trackRec(row-1,col+1,player,1);
    trackRec(row+1,col-1,player,7);

    //Check Diagonal y = -x
    trackRec(row+1,col+1,player,5);
    trackRec(row-1,col-1,player,11);
}

bool Board::trackRec(int row, int col, int seekPlayer, int direction){
    if(row < 1 || row > 8 || col < 1 || col > 8)
        return false;

    if(board[row][col]==seekPlayer)
        return true;

    if(board[row][col]==0)
        return false;

    int prevRow = row;
    int prevCol = col;

    switch(direction){
        case 3: col++;
            break;
        case 6: row++;
            break;
        case 9: col--;
            break;
        case 12: row--;
            break;
        case 1: row--; col++;
            break;
        case 5: row++; col++;
            break;
        case 7: row++;col--;
            break;
        case 11: row--;col--;
            break;
    }

    if(trackRec(row,col,seekPlayer,direction)==true){
        boardValid = true;
        board[prevRow][prevCol] = (board[prevRow][prevCol])%2 +1;
        return true;
    }
    else return false;
}

int Board:: defineHeuristics(int player){
    int sum[3];
    for(int i=1;i<9;i++)
        for(int j=1;j<9;j++)
            sum[ark[i][j]]++;


    sum[ark[1][1]]+=4;
    sum[ark[1][8]]+=4;
    sum[ark[8][1]]+=4;
    sum[ark[8][8]]+=4;

    for(int i=1;i<9;i++)
        sum[ark[1][i]]++;

    for(int i=1;i<9;i++)
        sum[ark[8][i]]++;

    for(int i=1;i<9;i++)
        sum[ark[i][1]]++;

    for(int i=1;i<9;i++)
        sum[ark[i][8]]++;

    if(player==1)
        return sum[1]-sum[2];
    else return sum[2]-sum[1];
}

int** Board::getBoard(){
    return ark;
}

bool Board:: isBoardValid(){
    return boardValid;
}

void Board::printBoard(){
    char widget;

    cout <<"       a     b     c     d     e     f     g     h"<<endl;
    cout <<"     _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _"<<endl;
    for(int i=1;i<9;i++){
        cout <<"    |     |     |     |     |     |     |     |     |"<<endl;
        widget = i+'0';
        cout <<"  "<<widget<< " |";
        for(int j=1;j<9;j++){
            if(ark[i][j]==1)
                cout <<  " [B] ";
            else if(ark[i][j]==2)
                cout <<  " (_) ";
            else cout << "     ";
            cout << "|";
        }
        cout <<" "<<widget <<endl<<"    |_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|"<<endl;
    }
    cout <<endl<<"       a     b     c     d     e     f     g     h"<<endl;
    cout << endl<<endl;
    /*
       a     b     c     d     e     f     g     h
     _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    |     |     |     |     |     |     |     |     |
  A |     |     |     |     |     |     |     |     |
    |_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|
    |     |     |     |     |     |     |     |     |
  B |     |     |     | (_) |     |     |     |     |
    |_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|
    |     |     |     |     |     |     |     |     |
  C |     |     | (X) | (_) | (X) |     |     |     |
    |_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|
    |     |     |     |     |     |     |     |     |
  D |     |     | (X) | (X) | (_) |     |     |     |
    |_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|
    |     |     |     |     |     |     |     |     |
    |     |     |     | (_) | (_) | (_) |     |     |
    |_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|
    |     |     |     |     |     |     |     |     |
    |     |     |     |     |     |     |     |     |
    |_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|
    |     |     |     |     |     |     |     |     |
    |     |     |     |     |     |     |     |     |
    |_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|
    |     |     |     |     |     |     |     |     |
    |     |     |     |     |     |     |     |     |
    |_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|
    */
}

#endif // __BOARD_H__
