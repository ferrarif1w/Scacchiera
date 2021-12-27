#include "Pieces.h" //da estrarre dalla cartella
#include "A.h"

A::A(){}

A::A(pair<int, int> pos, char col)
{
    pair<int, int> position = pos;
    char Color = col;
}

void A::SetMove(pair<int, int> NewPosition)
{
    position = NewPosition;
}

pair<int, int> A::GetPosition()
{
    return position;
}

void A::SetColor(char Col)
{
    Color = Col;
}

char A::GetColor()
{
    return Color;
}
