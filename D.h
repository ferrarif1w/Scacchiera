#ifndef D_H
#define D_H

#include <vector>
#include "Pieces.h"

class D : Pieces
{

    private:

        pair<int, int> position;
        char Color;
        bool Moved;

    public:

        D();
        D(pair<int, int> pos, char color);

        void SetMove(pair<int, int> NewPosition);
        pair<int, int> GetPosition();

        char GetColor();

        void SetStatus(bool Mov);
        bool GetStatus();

};
#endif