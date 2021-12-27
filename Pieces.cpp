#include <iostream>
#include <vector>
#include "Pieces.h"

//Alfiere
Pieces::A() {}

Pieces::A(pair<int, int> pos, char col)
{
    pair<int, int> position = pos;
    char Color = col;
}

void Pieces::SetMove(pair<int, int> NewPosition)
{
    position = NewPosition;
}

pair<int, int> Pieces::GetPosition()
{
    return position;
}

void Pieces::SetColor(char Col)
{
    Color = Col;
}

char Pieces::GetColor()
{
    return Color;
}

//Cavallo
Pieces::C() {}

Pieces::C(pair<int, int> pos, char col)
{
    pair<int, int> position = pos;
    char Color = col;
}

void Pieces::SetMove(pair<int, int> NewPosition)
{
    position = NewPosition;
}

pair<int, int> Pieces::GetPosition()
{
    return position;
}

void Pieces::SetColor(char Col)
{
    Color = Col;
}

char Pieces::GetColor()
{
    return Color;
}

//Donna
Pieces::D() {}

Pieces::D(pair<int, int> pos, char col)
{
    pair<int, int> position = pos;
    char Color = col;
}

void Pieces::SetMove(pair<int, int> NewPosition)
{
    position = NewPosition;
}

pair<int, int> Pieces::GetPosition()
{
    return position;
}

char Pieces::GetColor()
{
    return Color;
}

void Pieces::SetStatus(bool Mov)
{
    Moved = Mov;
}

bool Pieces::GetStatus()
{
    return Moved;
}

//Pedone
Pieces::P() {}

Pieces::P(pair<int, int> pos, char col)
{
    pair<int, int> position = pos;
    char Color = col;
}

void Pieces::SetMove(pair<int, int> NewPosition)
{
    position = NewPosition;
}

pair<int, int> Pieces::GetPosition()
{
    return position;
}

char Pieces::GetColor()
{
    return Color;
}

void Pieces::SetStatus(bool Mov)
{
    Moved = Mov;
}

bool Pieces::GetStatus()
{
    return Moved;
}

//Re
Pieces::R() {}

Pieces::R(pair<int, int> pos, char col)
{
    pair<int, int> position = pos;
    char Color = col;
}

void Pieces::SetMove(pair<int, int> NewPosition)
{
    position = NewPosition;
}

pair<int, int> Pieces::GetPosition()
{
    return position;
}

char Pieces::GetColor()
{
    return Color;
}

void Pieces::SetStatus(bool Mov)
{
    Moved = Mov;
}

bool Pieces::GetStatus()
{
    return Moved;
}

//Torre
Pieces::T() {}

Pieces::T(pair<int, int> pos, char col)
{
    pair<int, int> position = pos;
    char Color = col;
}

void Pieces::SetMove(pair<int, int> NewPosition)
{
    position = NewPosition;
}

pair<int, int> Pieces::GetPosition()
{
    return position;
}

char Pieces::GetColor()
{
    return Color;
}

void Pieces::SetStatus(bool Mov)
{
    Moved = Mov;
}

bool Pieces::GetStatus()
{
    return Moved;
}
