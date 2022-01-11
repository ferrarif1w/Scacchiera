#include "Gamers.h"

Gamers::Gamers(char C, ChessBoard *B, string N)
{
    Name = N;
    Color = C;
    chessBoard = B;
}

//player
bool Gamers::Move(string start, string end)
{
    int sFirst = start[1]-49;
    int sSecond = start[0]-65;
    int fFirst = end[1]-49;
    int fSecond = end[0]-65;
    pair<int, int> s = pair(sFirst, sSecond);
    pair<int, int> f = pair(fFirst, fSecond);

return chessBoard->performMove(s, f, Color);
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

char Gamers::PerformPromotion()
{

    char P[4]{'A', 'T', 'C', 'R'};

    int r = rand() % 4;

    chessBoard->performPromotion(P[r]);

    return P[r];
}
