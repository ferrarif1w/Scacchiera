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

    int m = rand() % v1.size();

    //ritorna 1 se è possibile promozione, 0 se è scaccomatto, -1 altrimenti
    int m1 = chessBoard->performMove(v1[m]);

    if (m1 = 1)
        chessBoard->performPromotion(piece, newPiece);
}
