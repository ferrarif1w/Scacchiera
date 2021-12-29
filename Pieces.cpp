#include <iostream>
#include <vector>
#include "Pieces.h"

Pieces::Pieces(std::pair<int, int> pos, char col, char n)
{
    position = pos;
    Color = col;
    Name = n;
    Moved = 0;
}

void Pieces::SetMove(std::pair<int, int> NewPosition)
{
    position = NewPosition;
    Moved++;
}

std::pair<int, int> Pieces::GetPosition()
{
    return position;
}

char Pieces::GetColor()
{
    return Color;
}

int Pieces::GetStatus()
{
    return Moved;
}

char Pieces::GetName()

{
    if(Color == 'B')
    return Name;
    else
    return (Name+32);
}


//Alfiere------------------------
std::vector<std::pair<int, int> *>& A::Pmove()
{
    std::vector<std::pair<int, int> *> Moves;
    int i=1;

    while (position.first + i < 8 && position.second + i < 8)
        {
            Moves.push_back(new std::pair(position.first + i, position.second + i));
            i++;
        }

    while (position.first + i < 8 && position.second - i >= 0)
        {
            Moves.push_back(new std::pair(position.first + i, position.second - i));
            i++;
        }

    while (position.first - i >= 8 && position.second + i < 8)
        {
            Moves.push_back(new std::pair(position.first - i, position.second + i));
            i++;
        }


    while (position.first - i >= 8 && position.second - i >= 8)
        {
            Moves.push_back(new std::pair(position.first - i, position.second - i));
            i++;
        }

    return Moves;
}

A::A(std::pair<int, int> position, char color) : Pieces(position, color, 65)
{}



//Cavallo------------------------
std::vector<std::pair<int, int> *>& C::Pmove()
{
    std::vector<std::pair<int, int> *> Moves;
    Moves.push_back(new std::pair(position.first + 2, position.second+1));
    Moves.push_back(new std::pair(position.first + 2, position.second-1));
    Moves.push_back(new std::pair(position.first - 2, position.second+1));
    Moves.push_back(new std::pair(position.first - 2, position.second-1));
    Moves.push_back(new std::pair(position.first + 1, position.second+2));
    Moves.push_back(new std::pair(position.first - 1, position.second+2));
    Moves.push_back(new std::pair(position.first + 1, position.second-2));
    Moves.push_back(new std::pair(position.first - 1, position.second-2));

    return Moves;
}

C::C(std::pair<int, int> position, char color) : Pieces(position, color, 67)
{}



//Donna------------------------
std::vector<std::pair<int, int> *>& D::Pmove()
{
    std::vector<std::pair<int, int> *> Moves;
    int i = 1;

    while (position.first + i < 8 && position.second + i < 8)
        {
            Moves.push_back(new std::pair(position.first + i, position.second + i));
            i++;
        }

    while (position.first + i < 8 && position.second - i >= 0)
        {
            Moves.push_back(new std::pair(position.first + i, position.second - i));
            i++;
        }

    while (position.first - i >= 8 && position.second + i < 8)
        {
            Moves.push_back(new std::pair(position.first - i, position.second + i));
            i++;
        }

    while (position.first - i >= 8 && position.second - i >= 8)
        {
            Moves.push_back(new std::pair(position.first - i, position.second - i));
            i++;
        }

//--

    while (position.first + i < 8)
        {
            Moves.push_back(new std::pair(position.first + i, position.second));
            i++;
        }

    while (position.first + i >= 0)
        {
            Moves.push_back(new std::pair(position.first - i, position.second));
            i++;
        }

    while (position.first + i < 8)
        {
            Moves.push_back(new std::pair(position.first, position.second + i));
            i++;
        }

    while (position.first + i >= 0)
        {
            Moves.push_back(new std::pair(position.first, position.second - i));
            i++;
        }


    return Moves;
}

D::D(std::pair<int, int> position, char color) : Pieces(position, color, 68)
{}



//Pedone------------------------
std::vector<std::pair<int, int> *>& P::Pmove()
{
    std::vector<std::pair<int, int> *> Moves;

    Moves.push_back(new std::pair(position.first + 1, position.second));

    if(Moved == 0)
    Moves.push_back(new std::pair(position.first + 2, position.second));

    return Moves;
}

P::P(std::pair<int, int> position, char color) : Pieces(position, color, 80)
{}



//Re------------------------
std::vector<std::pair<int, int> *>& R::Pmove()
{
    std::vector<std::pair<int, int> *> Moves;

    Moves.push_back(new std::pair(position.first + 1, position.second));
    Moves.push_back(new std::pair(position.first - 1, position.second));
    Moves.push_back(new std::pair(position.first, position.second + 1));
    Moves.push_back(new std::pair(position.first, position.second - 1));

//---

    Moves.push_back(new std::pair(position.first + 1, position.second+1));
    Moves.push_back(new std::pair(position.first - 1, position.second-1));
    Moves.push_back(new std::pair(position.first + 1, position.second -1));
    Moves.push_back(new std::pair(position.first -1, position.second + 1));

    return Moves;
}

R::R(std::pair<int, int> position, char color) : Pieces(position, color, 82)
{}



//Torre------------------------
std::vector<std::pair<int, int> *>& T::Pmove()
{
    std::vector<std::pair<int, int> *> Moves;
    int i = 0;

    while (position.first + i < 8)
        {
            Moves.push_back(new std::pair(position.first + i, position.second));
            i++;
        }

    while (position.first + i >= 0)
        {
            Moves.push_back(new std::pair(position.first - i, position.second));
            i++;
        }

    while (position.first + i < 8)
        {
            Moves.push_back(new std::pair(position.first, position.second + i));
            i++;
        }
    
    while (position.first + i >= 0)
        {
            Moves.push_back(new std::pair(position.first, position.second - i));
            i++;
        }

    return Moves;
}

T::T(std::pair<int, int> position, char color) : Pieces(position, color, 84)
{}
