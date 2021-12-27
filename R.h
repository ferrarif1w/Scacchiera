#ifndef R_H
#define R_H

#include <vector>
#include "Pieces.h"

class R : Pieces
{

    private:

        pair<int, int> position;
        char Color;
        bool Moved;

    public:

        R();
        R(pair<int, int> pos, char color);

        void SetMove(pair<int, int> NewPosition);
        pair<int, int> GetPosition();

        char GetColor();

        void SetStatus(bool Mov);
        bool GetStatus();

};
#endif