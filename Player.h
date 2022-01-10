#ifndef PLAYER_H
#define PLAYER_H
#include "chessBoard.h"



class Player
{

    protected:

    char Name;
    char Color;
    ChessBoard* chessBoard;
    char P[4] {A, T, C, R};

    public:

    Player(char Name, char Color, ChessBoard* chessBoard);

    int PlayerMove(string start, string end);
    int GetCondition();
    void PerformPromotion(char code);


    
    
};


#endif