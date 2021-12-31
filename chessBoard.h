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
            pair<int, int>* destination;
            //0: mossa normale, 1: mossa normale con cattura,
            //2: en passant, 3: arrocco corto, 4: arrocco lungo
            int moveName;
            //pezzo cattuarto   se moveName = 1,2
            //torre mossa       se moveName = 3,4
            Pieces* additionalPiece;
            Move(Pieces* p, pair<int, int>* dest, int name, Pieces* add);
            Move();
        };
        ChessBoard(string log);
        vector<Move*> movesAvailable(char color);
        //metodo per computer: mossa tratta da vector<Move*> ritornato da movesAvailable
        //pezzo da promuovere se promozione possibile
        Pieces* performMove(Move* move);
        //metodo per giocatore: fornire posizioni
        //pezzo da promuovere se promozione possibile
        Pieces* performMove(pair<int, int> start, pair<int, int> destination, char color);
        void performPromotion(Pieces* piece, char newPiece);
        string printBoard();
        class InvalidMoveException {};
        class InvalidPieceException {};
    private:
        //ogni vettore rappresenta una riga
        vector<vector<Pieces*>> board;
        //prima pezzi bianchi (pedoni per ultimi), poi pezzi neri (pedoni per ultimi)
        vector<Pieces*> piecesList;
        Move* lastMove;
        string logFile;
        Pieces* pieceToPromote;
        const int SIZE = 8;
        bool scanBoundaries(pair<int, int>* pos);
        //se casella occupata, ritorna colore del pezzo presente
        //altrimenti, ritorna 0
        char scanOccupied(pair<int, int>* pos);
        void initializeRow(int row);
        void insertPiece(Pieces* piece, pair<int, int>* pos);
        void scanAddSpecialMoves(vector<Move*>& moves, char color);
        bool scanPromotion(Pieces* piece);
        bool scanCheck(pair<int, int>* pos);
        bool scanCheck();
        bool scanCheckMate();
        //p1 = pedone che cattura, p2 = pedone che viene catturato
        bool enPassantConditions(Pieces* p1, Pieces* p2);
        //ritorna moveName adatto (3 se corto, 4 se lungo, 0 se non si può fare)
        int castlingConditions(Pieces* king, Pieces* tower);
};
//operatore di confronto per Move
//controlla se pezzo e posizione di arrivo sono uguali
bool operator==(const ChessBoard::Move& m1, const ChessBoard::Move& m2);

#endif