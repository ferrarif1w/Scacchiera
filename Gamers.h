#ifndef GAMERS_H
#define GAMERS_H

#include "chessBoard.h"

class Gamers
{

    protected:

        char Name;
        char Color;
        ChessBoard *chessBoard;
        char Type;

    public:

//costruttore
        Gamers(char Name, char Color, ChessBoard *chessBoard, char Type);

//player
        bool Move(string start, string end);
        int GetCondition();
        void PerformPromotion(char code);
        void PerformPromotion();

        //bot
        bool Move();
};

#endif