#include "Pieces.h" //da estrarre dalla cartella
#include "R.h"

R::R(){}

R::R(pair<int, int> pos, char col)
{
    pair<int, int> position = pos;
    char Color = col;
}

void R::SetMove(pair<int, int> NewPosition)
{
    position = NewPosition;
}

pair<int, int> R::GetPosition()
{
    return position;
}

void R::SetColor(char Col)
{
    Color = Col;
}

char R::GetColor()
{
    return Color;
}

void R::SetStatus(bool Mov)
{
    Moved = Mov;
}

bool R::GetStatus()
{
    return Moved;
}
