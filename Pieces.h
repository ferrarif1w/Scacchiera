#ifndef PIECES_H
#define PIECES_H

#include <vector>

class Pieces
{

        protected:

        std::pair<int, int> position;
        char Color;
        int Moved;
        char Name;

    public:
        Pieces(std::pair<int, int> position, char color, char n);

        void SetMove(std::pair<int, int> NewPosition);
        std::pair<int, int> GetPosition();

        char GetColor();
        char GetName();

        int GetStatus();


        virtual std::vector<std::pair<int, int>*>& Pmove() = 0;
};

class A : Pieces
{
    public:
        A(std::pair<int, int> position, char color);
        std::vector<std::pair<int, int> *>& Pmove() override;
};

class C : Pieces
{
public:
    C(std::pair<int, int> position, char color);
    std::vector<std::pair<int, int> *>& Pmove() override;
};

class D : Pieces
{
public:
    D(std::pair<int, int> position, char color);
    std::vector<std::pair<int, int> *>& Pmove() override;
};

class P : Pieces
{
public:
    P(std::pair<int, int> position, char color);
    std::vector<std::pair<int, int> *>& Pmove() override;
};

class R : Pieces
{
public:
    R(std::pair<int, int> position, char color);
    std::vector<std::pair<int, int> *>& Pmove() override;
};

class T : Pieces
{
public:
    T(std::pair<int, int> position, char color);
    std::vector<std::pair<int, int> *>& Pmove() override;
};

#endif