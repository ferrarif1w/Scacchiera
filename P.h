#ifndef P_H
#define P_H

#include <vector>
#include "Pieces.h"

class P : Pieces
{

    private:

        pair<int, int> position;
        char Color;
        bool Moved;

    public:

        P();
        P(pair<int, int> pos, char color);

        void SetMove(pair<int, int> NewPosition);
        pair<int, int> GetPosition();

        char GetColor();

        void SetStatus(bool Mov);
        bool GetStatus();

};
#endif