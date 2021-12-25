#include "Pieces.cpp" //da estrarre dalla cartella

Pieces::Pieces::P()
{}


Pieces::Pieces::P(pair<int, int> position, char color)
{
    pair<int, int> pos = position;
    char nC = color;
}

Pieces::SetPosition(pair<int, int> newPosition)
{
    pair<int, int> position = newposition;
}

Pieces::Getposition()
{
    return position;
}

Pieces::SetColor(char color)
{
    char nC = color;
}

Pieces::GetColor()
{
    return nC;
}

Pieces::SetStatus(bool primaMossa)
{
    bool nS = primaMossa;
}

Pieces::SetStatus()
{
    return nS;
}