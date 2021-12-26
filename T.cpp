#include "Pieces.h" //da estrarre dalla cartella
#include "T.h"

T::T(){}

T::T(pair<int, int> pos, char col)
{
    pair<int, int> position = pos;
    char Color = col;
}

void T::SetMove(pair<int, int> NewPosition)
{
    position = NewPosition;
}

pair<int, int> T::GetPosition()
{
    return position;
}

void T::SetColor(char Col)
{
    Color = Col;
}

char T::GetColor()
{
    return Color;
}

void T::SetStatus(bool Mov)
{
    Moved = Mov;
}

bool T::GetStatus()
{
    return Moved;
}
