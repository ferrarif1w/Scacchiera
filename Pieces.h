#ifndef PIECES_H
#define PIECES_H

#include <vector>
using namespace std;

class Pieces
{

    private:
        int Pos(pair<int, int> pos);
        bool PrimaMossa = false;

    public:
        Pieces();
        Pieces(pair<int, int> position);

};
#endif