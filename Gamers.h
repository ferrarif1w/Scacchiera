#ifndef GAMERS_H
#define GAMERS_H

#include "chessBoard.h"

class Gamers
{

    protected:

        string Name;
        char Color;
        ChessBoard *chessBoard;

    public:

//costruttore
        Gamers(char Color, ChessBoard *chessBoard);

//player
        bool Move(string start, string end);
        int GetCondition();
        void PerformPromotion(char code);
        void PerformPromotion();

        //bot
        bool Move();
};

#endif