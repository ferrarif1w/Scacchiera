#ifndef C_H
#define C_H

#include <vector>
#include "Pieces.h"

class C : Pieces
{

    private:

        pair<int, int> position;
        char Color; //che valori può avere Color?
        bool Moved;

    public:

        C();
        C(pair<int, int> pos, char color);

        void SetMove(pair<int, int> NewPosition);
        pair<int, int> GetPosition();

        void SetColor(char col);
        char GetColor();

};
#endif