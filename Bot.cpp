#include "Bot.h"

    Bot::Bot(char n, char c, ChessBoard *B)
{

    Name = n;
    Color = c;
    chessBoard = B;

}

string Bot::BotMove()
{

    vector<ChessBoard::Move> v1 = chessBoard->movesAvailable(Color);

    int Cond = chessBoard->getCondition();

    if(Cond == 0 || Cond == 2)
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
