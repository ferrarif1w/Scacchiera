#include <iostream>
#include <algorithm>
#include <vector>
#include "chessBoard.h"
#include "Pieces.h"

class Bot
{

    protected:

    char Name;
    char Color;
    ChessBoard* chessBoard;

    public:

    Bot(char Name, char Color, ChessBoard* chessBoard);

    int BotMove();
};