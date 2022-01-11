#ifndef GAMERS_H
#define GAMERS_H

#include "chessBoard.h"

class Gamers
{

    protected:

        char Name;
        char Color;
        ChessBoard *chessBoard;
        char P[4]{'A', 'T', 'C', 'R'};

    public:

//costruttore
        Gamers(char Name, char Color, ChessBoard *chessBoard);

//player
        int PlayerMove(string start, string end);
        int GetCondition();
        void PerformPromotion(char code);

//bot
        string BotMove();
};

#endif