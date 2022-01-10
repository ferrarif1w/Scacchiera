#include "Bot.h"
#include <cstdlib>

    Bot::Bot(char n, char c, ChessBoard *B)
{

    Name = n;
    Color = c;
    chessBoard = B;

}

int Bot::BotMove()
{

    vector<ChessBoard::Move> v1 = chessBoard->movesAvailable(Color);
    switch (chessBoard->getCondition())
    {
        case 0:
        
            return 0;
        
        break;
    
        case 1:

            return 1;

        break;

        case 2:

            return 2;

        break;
    }

    int m = rand() % v1.size();

    if (chessBoard->performMove(v1[m]))
    {
        m = rand() % 4;

        chessBoard->performPromotion(P[m]);
    }
}
