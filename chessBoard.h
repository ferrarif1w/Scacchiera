#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <vector>
#include <string>
#include "Pieces.h"
using namespace std;

class ChessBoard {
    public:
        struct Move {
            Pieces* piece;
            pair<int, int> destination;
            int moveName;
            //0: mossa normale, 1: mossa normale con cattura,
            //2: en passant, 3: arrocco, 4: arrocco lungo
            Pieces* additionalPiece = nullptr;
            //pezzo cattuarto   se moveName = 1,2
            //torre mossa       se moveName = 3,4
        };
        ChessBoard();
        vector<Move*> movesAvailable();
        void performMove(Move* move); //indice da vector<Move*> precedente
        string printBoard();
        vector<vector<Pieces*>> board;
    private:
        //ogni vettore rappresenta una riga
        vector<Pieces*> piecesList;
        const int SIZE = 8;
        bool scanBoundaries(pair<int, int>* pos);
        bool scanOccupied(pair<int, int>* pos);
        void initializeRow(int row);
        void insertPiece(Pieces* piece, pair<int, int> pos);
        bool scanExecutePromotion();
        bool scanExecuteEnPassant(vector<Move*>& moves);
        bool scanExecuteCastling(vector<Move*>& moves);
        bool scanCheck();
        bool scanCheckMate();
};

#endif