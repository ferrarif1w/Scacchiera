#include "Pieces.h" //da estrarre dalla cartella
#include "D.h"

D::D(){}

D::D(pair<int, int> pos, char col)
{
    pair<int, int> position = pos;
    char Color = col;
}

void D::SetMove(pair<int, int> NewPosition)
{
    position = NewPosition;
}

pair<int, int> D::GetPosition()
{
    return position;
}

void D::SetColor(char Col)
{
    Color = Col;
}

char D::GetColor()
{
    return Color;
}

void D::SetStatus(bool Mov)
{
    Moved = Mov;
}

bool D::GetStatus()
{
    return Moved;
}
