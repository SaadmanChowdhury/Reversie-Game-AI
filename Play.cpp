#include "Play.h"

#ifndef __PLAY_H__
#define __PLAY_H__

Play::Play(){
    depth = 6;
    displayMessage(1);

    int gameType;
    while(true){
        displayMessage(2);
        cin >> gameType;

        if(gameType==1 || gameType==2)
            break;
    }

    Board* emptyBoard = new Board();
    tree= ne    w Tree(emptyBoard,gameType);

    if(gameType==2){
        computerFirstMove();
    }

    bool flag = true;
    while(flag){
        flag = printAndPlay();
    }


}

void Play::nextMove(){
    player = (player%2)+1;
    moveCounter++;
}


void Play:: displayMessage(int type){
    //Opening Message
    if(type==1){
        cout << endl << endl;
        cout << "  * * * * * * * * * * * * * * * * * * * * * * * * * * *"<<endl;
        cout << "  * * * * * * * * * * * * * * * * * * * * * * * * * * *"<<endl;
        cout << "  * *                                               * *"<<endl;
        cout << "  * *    Welcome to the Othello Game,  Made By:     * *"<<endl;
        cout << "  * *    --------------------------------------     * *"<<endl;
        cout << "  * *                                               * *"<<endl;
        cout << "  * *    Saadman Shahid Chowdhury -- 1320741042     * *"<<endl;
        cout << "  * *    Atiar Talukdar           -- 1320242042     * *"<<endl;
        cout << "  * *                                               * *"<<endl;
        cout << "  * * * * * * * * * * * * * * * * * * * * * * * * * * *"<<endl;
        cout << "  * * * * * * * * * * * * * * * * * * * * * * * * * * *"<<endl;
        return;
    }

    if(type==2){
        cout << endl << endl;
        cout << "  *****************************************************"<<endl;
        cout << "                                                       "<<endl;
        cout << "        This Program Allows for Human vs AI Play       "<<endl;
        cout << "        ----------------------------------------       "<<endl;
        cout << "                                                       "<<endl;
        cout << "          For Human to Play first:     PRESS (1)       "<<endl;
        cout << "             For AI to Play first:     PRESS (2)       "<<endl;
        cout << "                                                       "<<endl;
        cout << "  *****************************************************"<<endl;
        return;
    }
}

void Play::computerFirstMove(){

    Board* board = tree->getCurrentBoard();

    tree->getCurrentBoard()->printBoard();

    string s = tree->makeMoveAsComputer(depth);
    cout << "COMPUTER MAKES MOVE: " << s << endl;
    moveCounter++;

}

bool Play::printAndPlay(){
    Board* board = tree->getCurrentBoard();

    int** ark = board->getBoard();
    string s = tree->suggestMovesToPlayer();

    if(s=="No Moves Available"){
        cout << s << endl;
        tree->getCurrentBoard()->printBoard();

        s = tree->makeMoveAsComputer(depth);
        cout << "COMPUTER MAKES MOVE: " << s << endl;
        moveCounter++;

        return true;
    }

    int row,col;
    for(int i=0;i<s.size();){
        if(s[i]==' ')
            i++;
        if(s[i]=='N')
            i+=2;
        row = s[i]-'0';
        col = s[i+1] - 'a' + 1;
        ark[row][col] = 3;
        i+=2;

    }

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
            else if(ark[i][j]==3)
                cout <<  "  *  ";
            else cout << "     ";
            cout << "|";
        }
        cout <<" "<<widget <<endl<<"    |_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|"<<endl;
    }
    cout <<endl<<"       a     b     c     d     e     f     g     h"<<endl;
    cout <<endl;
    int player[4];
    for(int i=0;i<4;i++)
        player[i]=0;

    for(int i=1;i<9;i++)
        for(int j=1;j<9;j++)
            player[ark[i][j]]++;

    if(player[3]==0){
        cout << "GAME ENDS" << endl;
        cout << "FINAL SCORE -- Black: " << player[1] << " and White: " << player[2] << endl;
        return false;
    }

    cout << "TURN: " << moveCounter << " BLACK: " << player[1] << " and WHITE: " << player[2]<<endl;
    if(tree->getCurrentPlayer()==1)
        cout << "BLACK [B] playable: ";
    else cout <<"WHITE (_) playable: ";
    cout << s << endl;

    cout << "ENTER MOVE: "; string m = s; bool flag = true;
    while(flag){
        cin >> s;
        for(int i=0;i<m.size()-1;i++){
            if(s[0]==m[i])
                if(s[1]==m[i+1]){
                    flag = false;
                }

        }
        if(flag)
        cout << "INVALID MOVE. Please Re-Enter Move: ";
    }
    cout << endl;

    tree->acceptNextMove(s);
    moveCounter++;
    tree->getCurrentBoard()->printBoard();

    s = tree->makeMoveAsComputer(depth);
    cout << "COMPUTER MAKES MOVE: " << s << endl;
    if(s.size()<3)
        moveCounter++;

    return true;
    /*
       a     b     c     d     e     f     g     h
     _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _
    |     |     |     |     |     |     |     |     |
  1 |     |     |  *  |  *  |  *  |     |     |     |
    |_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|
    |     |     |     |     |     |     |     |     |
  2 |     |     |     | (_) |  *  |     |     |     |
    |_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|
    |     |     |     |     |     |     |     |     |
  3 |     |     | (X) | (_) | (X) |     |     |     |
    |_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|
    |     |     |     |     |     |     |     |     |
  4 |     |     | (X) | (X) | (_) |  *  |     |     |
    |_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|
    |     |     |     |     |     |     |     |     |
    |     |     |     | (_) | (_) | (_) |     |     |
    |_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|
    |     |     |     |     |     |     |     |     |
    |     |     |     |  *  |  *  |  *  |     |     |
    |_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|
    |     |     |     |     |     |     |     |     |
    |     |     |     |     |     |     |     |     |
    |_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|
    |     |     |     |     |     |     |     |     |
    |     |     |     |     |     |     |     |     |
    |_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|_ _ _|
    */
}

void Play::bugTest2(Board* parent){
    if(moveCounter==15)
        return;

    string s;
    cout << "Next Move: ";
    cin >> s;
    int** a;
    Board* b = new Board(parent,s[0]-'a'+1,s[1]-'0',player);
    b->printBoard();
    a=b->getBoard();
    for(int i=0;i<9;i++){
        for(int j=0;j<9;j++)
            cout << a[i][j]<< " ";
        cout<<endl;
    }
    nextMove();
    bugTest2(b);
}

void Play::bugTest1(){
}
#endif // __PLAY_H__
