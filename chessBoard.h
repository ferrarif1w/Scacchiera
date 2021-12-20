#include <vector>
#include <string>
#include "Pieces.h"
using namespace std;

class ChessBoard {
    private:
        vector<vector<Pieces*>> board;
        const int SIZE = 8;
        bool checkBoundaries(pair<int, int> pos);
    public:
        struct Move {
            Pieces* piece;
            pair<int, int> destination;
            string moveName = 0;
        };
        ChessBoard();
        vector<Move*> movesAvailable();
        void performMove(int moveIndex); //indice da vector<Move*> precedente
        string printBoard();
};