#include "chessBoard.h"

class Bot
{

    protected:

    char Name;
    char Color;
    ChessBoard* chessBoard;
    char P[4] {A, T, C, R};

    public:

    Bot(char Name, char Color, ChessBoard* chessBoard);

    int BotMove();
};