#include "Gamers.h"

Gamers::Gamers(char n, char c, ChessBoard *B)
{

    char Name = n;
    char Color = c;
    ChessBoard *chessBoard = B;
}

//player
int Gamers::PlayerMove(string start, string end)
{
    int sFirst = start[1]-49;
            int sSecond = start[0]-65;
            int fFirst = end[1]-49;
            int fSecond = end[0]-65;

return chessBoard.performMove(pair(sFirst, sSecond), pair(fFirst, fSecond), color);
}

int Gamers::GetCondition()
{

return chessBoard->getCondition();

}

void Gamers::PerformPromotion(char code)
{
    chessBoard->performPromotion(code);
}

//Bot
string Gamers::BotMove()
{

    vector<ChessBoard::Move> v1 = chessBoard->movesAvailable(Color);

    int Cond = chessBoard->getCondition();

    if (Cond == 0 || Cond == 2)
    {
        return to_string("N" + Cond);
    }

    int m = rand() % v1.size();

    if (chessBoard->performMove(v1[m]))
    {
        m = rand() % 4;

        chessBoard->performPromotion(P[m]);

        return to_string(P[m] + Cond;)
    }

    return to_string("N" + Cond);
}
