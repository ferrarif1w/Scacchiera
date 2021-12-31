#include <iostream>
#include <vector>
#include "Pieces.h"
#include "chessBoard.h"

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
    if(Color == 'N')
    return Name;
    else
    return (Name+32);
}


//Alfiere------------------------
std::vector<std::vector<std::pair<int, int> *>>& A::Pmove() //vector<vector<pair<int, int>>>
{
    std::vector<std::vector<std::pair<int, int> *>> Moves;
    int i=1;

    std::vector<std::pair<int, int> *> m1;
    while (position.first + i < 8 && position.second + i >= 0) //genera un vettore
        {
            m1.push_back(new std::pair(position.first + i, position.second + i));
            i++;
        }
    Moves.push_back(m1);
    i = 1;

    std::vector<std::pair<int, int> *> m2;
    while (position.first + i < 8 && position.second - i >= 0) //genera un vettore
    {
        m2.push_back(new std::pair(position.first + i, position.second - i));
        i++;
    }
    Moves.push_back(m2);
    i = 1;

    std::vector<std::pair<int, int> *> m3;
    while (position.first - i < 8 && position.second + i >= 0) //genera un vettore
    {
        m3.push_back(new std::pair(position.first - i, position.second + i));
        i++;
    }
    Moves.push_back(m3);
    i = 1;

    std::vector<std::pair<int, int> *> m4;
    while (position.first - i < 8 && position.second - i >= 0) //genera un vettore
    {
        m4.push_back(new std::pair(position.first - i, position.second - i));
        i++;
    }
    Moves.push_back(m4);
    i = 1;

    return Moves;
}

    A::A(std::pair<int, int> position, char color) : Pieces(position, color, 65)
    {}



//Cavallo------------------------
std::vector<std::vector<std::pair<int, int> *>>& C::Pmove()
{
    std::vector<std::vector<std::pair<int, int> *>> Moves;
    std::vector<std::pair<int, int> *> tmp;
    tmp.push_back(new std::pair(position.first + 2, position.second + 1));
    tmp.push_back(new std::pair(position.first + 2, position.second - 1));
    tmp.push_back(new std::pair(position.first - 2, position.second + 1));
    tmp.push_back(new std::pair(position.first - 2, position.second - 1));
    tmp.push_back(new std::pair(position.first + 1, position.second + 2));
    tmp.push_back(new std::pair(position.first - 1, position.second + 2));
    tmp.push_back(new std::pair(position.first + 1, position.second - 2));
    tmp.push_back(new std::pair(position.first - 1, position.second - 2));

    Moves.push_back(tmp);
    return Moves;
}

C::C(std::pair<int, int> position, char color) : Pieces(position, color, 67)
{}



//Donna------------------------
std::vector<std::vector<std::pair<int, int> *>>& D::Pmove()
{
    std::vector<std::vector<std::pair<int, int> *>> Moves;
    int i = 1;

    std::vector<std::pair<int, int> *> m1;
    while (position.first + i < 8 && position.second + i >= 0) //genera un vettore
    {
        m1.push_back(new std::pair(position.first + i, position.second + i));
        i++;
    }
    Moves.push_back(m1);
    i = 1;

    std::vector<std::pair<int, int> *> m2;
    while (position.first + i < 8 && position.second - i >= 0) //genera un vettore
    {
        m2.push_back(new std::pair(position.first + i, position.second - i));
        i++;
    }
    Moves.push_back(m2);
    i = 1;

    std::vector<std::pair<int, int> *> m3;
    while (position.first - i < 8 && position.second + i >= 0) //genera un vettore
    {
        m3.push_back(new std::pair(position.first - i, position.second + i));
        i++;
    }
    Moves.push_back(m3);
    i = 1;

    std::vector<std::pair<int, int> *> m4;
    while (position.first - i < 8 && position.second - i >= 0) //genera un vettore
    {
        m4.push_back(new std::pair(position.first - i, position.second - i));
        i++;
    }
    Moves.push_back(m4);
    i = 1;

        //--

    std::vector<std::pair<int, int> *> m5;
    while (position.first + i >= 0)
    {
        m5.push_back(new std::pair(position.first + i, position.second));
        i++;
    }
    Moves.push_back(m5);
    i = 1;

    std::vector<std::pair<int, int> *> m6;
    while (position.first + i >= 0)
    {
        m6.push_back(new std::pair(position.first - i, position.second));
        i++;
    }
    Moves.push_back(m6);
    i = 1;

    std::vector<std::pair<int, int> *> m7;
    while (position.first + i >= 0)
    {
        m7.push_back(new std::pair(position.first, position.second + i));
        i++;
    }
    Moves.push_back(m7);
    i = 1;

    std::vector<std::pair<int, int> *> m8;
    while (position.first + i >= 0)
    {
        m8.push_back(new std::pair(position.first, position.second - i));
        i++;
    }
    Moves.push_back(m8);
    i = 1;

    return Moves;
}


D::D(std::pair<int, int> position, char color) : Pieces(position, color, 68)
{}



//Pedone------------------------
std::vector<std::vector<std::pair<int, int> *>>& P::Pmove()
{
    std::vector<std::vector<std::pair<int, int> *>> Moves;
    std::vector<std::pair<int, int> *> tmp;

    tmp.push_back(new std::pair(position.first + 1, position.second));

    if(Moved == 0)
        tmp.push_back(new std::pair(position.first + 2, position.second));

    Moves.push_back(tmp);

    return Moves;
}

P::P(std::pair<int, int> position, char color) : Pieces(position, color, 80)
{}



//Re------------------------
std::vector<std::vector<std::pair<int, int> *>> & R::Pmove()
{
    std::vector<std::vector<std::pair<int, int> *>> Moves;
    std::vector<std::pair<int, int> *> tmp;

    tmp.push_back(new std::pair(position.first + 1, position.second));
    tmp.push_back(new std::pair(position.first - 1, position.second));
    tmp.push_back(new std::pair(position.first, position.second + 1));
    tmp.push_back(new std::pair(position.first, position.second - 1));

    //---

    tmp.push_back(new std::pair(position.first + 1, position.second + 1));
    tmp.push_back(new std::pair(position.first - 1, position.second - 1));
    tmp.push_back(new std::pair(position.first + 1, position.second - 1));
    tmp.push_back(new std::pair(position.first - 1, position.second + 1));

    Moves.push_back(tmp);

    return Moves;
}

R::R(std::pair<int, int> position, char color) : Pieces(position, color, 82)
{}



//Torre------------------------
std::vector<std::vector<std::pair<int, int> *>>& T::Pmove()
{
    std::vector<std::vector<std::pair<int, int> *>> Moves;
    int i = 0;

    std::vector<std::pair<int, int> *> m1;
    while (position.first + i >= 0)
    {
        m1.push_back(new std::pair(position.first + i, position.second));
        i++;
    }
    Moves.push_back(m1);
    i = 1;

    std::vector<std::pair<int, int> *> m2;
    while (position.first + i >= 0)
    {
        m2.push_back(new std::pair(position.first - i, position.second));
        i++;
    }
    Moves.push_back(m2);
    i = 1;

    std::vector<std::pair<int, int> *> m3;
    while (position.first + i >= 0)
    {
        m3.push_back(new std::pair(position.first, position.second + i));
        i++;
    }
    Moves.push_back(m3);
    i = 1;

    std::vector<std::pair<int, int> *> m4;
    while (position.first + i >= 0)
    {
        m4.push_back(new std::pair(position.first, position.second - i));
        i++;
    }
    Moves.push_back(m4);
    i = 1;

    return Moves;
}

T::T(std::pair<int, int> position, char color) : Pieces(position, color, 84)
{}