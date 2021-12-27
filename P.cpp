#include "Pieces.h" //da estrarre dalla cartella
#include "P.h"

P::P(){}

P::P(pair<int, int> pos, char col)
{
    pair<int, int> position = pos;
    char Color = col;
}

void P::SetMove(pair<int, int> NewPosition)
{
    position = NewPosition;
}

pair<int, int> P::GetPosition()
{
    return position;
}

char P::GetColor()
{
    return Color;
}

void P::SetStatus(bool Mov)
{
    Moved = Mov;
}

bool P::GetStatus()
{
    return Moved;
}
