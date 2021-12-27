#ifndef A_H
#define A_H

#include <vector>
#include "Pieces.h"

class A : Pieces
{

    private:

        pair<int, int> position;
        char Color;
        bool Moved;

    public:

        A();
        A(pair<int, int> pos, char color);

        void SetMove(pair<int, int> NewPosition);
        pair<int, int> GetPosition();

        void SetColor(char col);
        char GetColor();


};
#endif