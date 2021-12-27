#include "Pieces.h" //da estrarre dalla cartella
#include "C.h"

C::C(){}

C::C(pair<int, int> pos, char col)
{
    pair<int, int> position = pos;
    char Color = col;
}

void C::SetMove(pair<int, int> NewPosition)
{
    position = NewPosition;
}

pair<int, int> C::GetPosition()
{
    return position;
}

void C::SetColor(char Col)
{
    Color = Col;
}

char C::GetColor()
{
    return Color;
}

