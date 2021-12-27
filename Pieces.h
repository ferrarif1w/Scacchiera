#ifndef PIECES_H
#define PIECES_H

#include <vector>

class Pieces
{

        protected:

        std::pair<int, int> position;
        char Color;
        bool Moved;


    public:

        Pieces();
        Pieces(std::pair<int, int> position, char color);

        void SetMove(std::pair<int, int> NewPosition);
        std::pair<int, int> GetPosition();

        char GetColor();

        void SetStatus(bool Mov);
        bool GetStatus();

        std::vector<std::pair<int, int>*> Pmove();
};
#endif