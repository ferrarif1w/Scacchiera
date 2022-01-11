#include "Gamers.h"

Gamers::Gamers(string n, char c, ChessBoard *B)
{
    Name = n;
    Color = c;
    chessBoard = B;
}

//player
bool Gamers::Move(string start, string end)
{
    int sFirst = start[1]-49;
    int sSecond = start[0]-65;
    int fFirst = end[1]-49;
    int fSecond = end[0]-65;

return chessBoard->performMove(pair(sFirst, sSecond), pair(fFirst, fSecond), Color);
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
bool Gamers::Move()
{

    vector<ChessBoard::Move> v1 = chessBoard->movesAvailable(Color);

    int m = rand() % v1.size();

    return chessBoard->performMove(v1[m]);
}

void Gamers::PerformPromotion()
{

    char P[4]{'A', 'T', 'C', 'R'};

    int r = rand() % 4;

    return chessBoard->performPromotion(P[r]);
}
