#include "Player.h"

    Player::Player(char n, char c, ChessBoard *B)
{

    Name = n;
    Color = c;
    chessBoard = B;

}

int Player::PlayerMove(string start, string end)
{
    int sFirst = start[1]-49;
            int sSecond = start[0]-65;
            int fFirst = end[1]-49;
            int fSecond = end[0]-65;

return chessBoard.performMove(pair(sFirst, sSecond), pair(fFirst, fSecond), color);
}

int Player::GetCondition()
{

return chessBoard->getCondition();

}

void Player::PerformPromotion(char code)
{
    chessBoard->performPromotion(code);
}

