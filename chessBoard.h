#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <vector>
#include <string>
#include "Pieces.h"
using namespace std;

class ChessBoard {
    public:
        //pezzo, destinazione, codice della mossa, eventuale pezzo aggiuntivo
        struct Move {
            Pieces* piece;
            pair<int, int> destination;
            //0: mossa normale, 1: mossa normale con cattura,
            //2: en passant, 3: arrocco corto, 4: arrocco lungo
            int moveName;
            //pezzo cattuarto   se moveName = 1,2
            //torre mossa       se moveName = 3,4
            Pieces* additionalPiece = nullptr;
        };
        ChessBoard();
        vector<Move*> movesAvailable(char color);
        void performMove(Move* move); //indice da vector<Move*> precedente
        string printBoard();
    private:
        //ogni vettore rappresenta una riga
        vector<vector<Pieces*>> board;
        //prima pezzi bianchi (pedoni per ultimi), poi pezzi neri (pedoni per ultimi)
        vector<Pieces*> piecesList;
        const int SIZE = 8;
        bool scanBoundaries(pair<int, int>* pos);
        bool scanOccupied(pair<int, int>* pos);
        void initializeRow(int row);
        void insertPiece(Pieces* piece, pair<int, int> pos);
        void scanAddSpecialMoves(vector<Move*>& moves, char color);
        bool scanCheck(pair<int, int>* pos);
        bool scanCheck();
        bool scanCheckMate();
};

#endif