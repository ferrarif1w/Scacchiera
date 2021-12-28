#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <vector>
#include <string>
#include "Pieces.h"
using namespace std;

class ChessBoard {
    private:
        //ogni vettore rappresenta una riga
        vector<vector<Pieces*>> board;
        vector<Pieces*> piecesList;
        const int SIZE = 8;
        bool checkBoundaries(pair<int, int> pos);
        void initializeRow(int row);
    public:
        struct Move {
            Pieces* piece;
            pair<int, int> destination;
            string moveName = "";
            Pieces* eatenPiece = nullptr;
        };
        ChessBoard();
        vector<Move*> movesAvailable();
        void performMove(int moveIndex); //indice da vector<Move*> precedente
        string printBoard();
};

#endif