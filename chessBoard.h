#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <algorithm>
#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include <map>
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
            Pieces* additionalPiece;
            Move(Pieces* p, pair<int, int> dest, int name, Pieces* add);
            Move();
        };
        ChessBoard(string log = "", string playerWhite = "", string playerBlack = "");
        /*ritorna vettore con tutte le mosse possibili*/
        vector<Move> movesAvailable(char color);
        /*metodo per computer: mossa tratta da vector<Move> ritornato da movesAvailable
        ritorna true se è possibile promozione, false altrimenti*/
        bool performMove(Move move);
        /*metodo per giocatore: fornire posizioni
        ritorna true se è possibile promozione, false altrimenti*/
        bool performMove(pair<int, int>& start, pair<int, int>& destination, char color);
        void performPromotion(char newPiece);
        string printBoard();
        /*metodo usato da bot*/
        int getCondition();
        /*metodo usato da umano*/
        int getCondition(char color);
        pair<int, int> getPawnToPromote();
        /*TOGLIERLA ALLA FINE DI TUTTO
        importa board da file*/
        void justForDebug(string fileName);
        class InvalidInputException {};
        class InvalidMoveException {};
    private:
        /*ogni vettore rappresenta una riga*/
        vector<vector<Pieces*>> board;
        /*prima pezzi bianchi (pedoni per ultimi), poi pezzi neri (pedoni per ultimi)*/
        vector<Pieces*> piecesList;
        Move lastMove;
        string logFile;
        Pieces* pieceToPromote;
        /*0 se in scaccomatto, 1 se scacco, 2 se non più mosse regolari, 3 altrimenti*/
        int condition = -1;
        /*vettore contenente le mosse disponibili a un giocatore umano*/
        vector<Move> humanPlayerMoves;
        const int SIZE = 8;
        bool legitMoveInput(pair<int, int>& x);
        bool scanBoundaries(pair<int, int>& pos);
        bool scanBoundaries(int row, int column);
        /*se casella occupata, ritorna colore del pezzo presente
        altrimenti, ritorna 0*/
        char scanOccupied(pair<int, int>& pos);
        char scanOccupied(int row, int column);
        void initializeRow(int row);
        void insertPiece(Pieces* piece, pair<int, int>* pos);
        void scanAddSpecialMoves(vector<Move>& moves, char color);
        bool scanPromotion(Pieces* piece);
        /*row e column: eventuali coordinate modificate del re*/
        bool scanCheck(char color, int row = -1, int column = -1);
        //bool scanCheck(char color);
        bool scanCheck(Move& move, char color);
        //bool scanCheckMate(vector<Move>& moves, char color);
        bool scanCheckMate(bool initialCheck, vector<Move>& moves);
        /*p1 = pedone che cattura, p2 = pedone che viene catturato*/
        bool enPassantConditions(Pieces* p1, Pieces* p2);
        /*true se possibile arrocco, tipo di arrocco determinato da chiamante*/
        bool castlingConditions(Pieces* king, Pieces* tower);
        /*aggiorna log con mossa*/
        void updateLog(pair<int, int> start, pair<int, int> finish);
        /*aggiorna log con pezzo inserito con promozione*/
        void updateLog(char newPiece);
        /*mappa utilizzata in scanCheck*/
        map<pair<int, int>, string> directionsPieces {
            {pair(1,1), "PRAD"},
            {pair(1,0), "RDT"},
            {pair(1,-1), "PRAD"},
            {pair(0,-1), "RDT"},
            {pair(-1,-1), "PRAD"},
            {pair(-1,0), "RDT"},
            {pair(-1,1), "PRAD"},
            {pair(0,1), "RDT"}
        };
        /*vettore utilizzato in scanCheck*/
        vector<pair<int, int>> directionsHorse {
            pair(1,2), pair(2,1), pair(2,-1), pair(1,-2), pair(-1,-2), pair(-2,-1), pair(-2,1), pair(-1,2)
        };
};
/*operatore di confronto per Move
controlla se pezzo e posizione di arrivo sono uguali*/
bool operator==(const ChessBoard::Move& m1, const ChessBoard::Move& m2);

#endif