#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <algorithm>
#include <fstream>
#include <string>
#include <utility>
#include <vector>
#include <map>
#include <random>
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
        //ritorna vettore con tutte le mosse possibili
        vector<Move> movesAvailable(char color);
        //metodo generale
        //ritorna true se è possibile promozione, false altrimenti
        bool performMove(Move move);
        //metodo per computer: mossa presa automaticamente da nextPlayerMoves
        //ritorna true se è possibile promozione, false altrimenti
        bool performMove();
        //metodo per giocatore: fornire posizioni
        //ritorna true se è possibile promozione, false altrimenti
        bool performMove(pair<int, int>& start, pair<int, int>& destination, char color = 0);
        void performPromotion(char newPiece);
        string printBoard();
        int getCondition(char color);
        pair<int, int> getPawnToPromote();
        //aggiorna log con informazioni su vittoria
        //se ending=0, stampato in file condition: 0 se in scaccomatto, 2 se stallo,
        //3 se patta per mancanza di pezzi, 4 se patta per numero di mosse,
        //5 se patta per ripetizione di posizione,
        //6 se patta per raggiungimento limite mosse in partita tra bot,
        //7 se patta per accordo
        void updateLogVictory(int ending);
        //aggiorna log con tipo di partita
        void updateLogGameType(string type);
        //TOGLIERLA ALLA FINE DI TUTTO
        //importa board da file
        void justForDebug(string fileName);
        class InvalidInputException {};
        class InvalidMoveException {};
    private:
        //ogni vettore rappresenta una riga
        vector<vector<Pieces*>> board;
        //prima pezzi bianchi (pedoni per ultimi), poi pezzi neri (pedoni per ultimi)
        vector<Pieces*> piecesList;
        //acronimo di piecesLeftWithoutKings
        int PLWK;
        Move lastMove;
        string logFile;
        Pieces* pieceToPromote;
        //0 se in scaccomatto, 1 se scacco, 2 se stallo, 3 se patta per mancanza di pezzi,
        //4 se patta per numero di mosse, -1 altrimenti; incrementata di 10 se possibile patta
        //per ripetizioni di posizione
        int condition = -1;
        //vettore contenente le mosse disponibili a un giocatore umano
        vector<Move> nextPlayerMoves;
        //mappa che salva le configurazioni apparse e il numero di apparizioni
        map<string, int> positions;
        //numero di mosse effettuate senza muovere pedoni e catturare pezzi (per patta per numero di mosse)
        int drawMoves;
        const int SIZE = 8;
        bool legitMoveInput(pair<int, int>& x);
        bool scanBoundaries(pair<int, int>& pos);
        bool scanBoundaries(int row, int column);
        ///se casella occupata, ritorna colore del pezzo presente
        //altrimenti, ritorna 0
        char scanOccupied(pair<int, int>& pos);
        char scanOccupied(int row, int column);
        void initializeRow(int row);
        void insertPiece(Pieces* piece, pair<int, int>* pos);
        void scanAddSpecialMoves(vector<Move>& moves, char color);
        bool scanPromotion(Pieces* piece);
        //row e column: eventuali coordinate modificate del re
        bool scanCheck(char color, int row = -1, int column = -1);
        bool scanCheck(Move& move, char color);
        bool scanCheckmate(bool initialCheck, vector<Move>& moves);
        bool scanCheckmateImpossibility();
        //p1 = pedone che cattura, p2 = pedone che viene catturato
        bool enPassantConditions(Pieces* p1, Pieces* p2);
        //true se possibile arrocco, tipo di arrocco determinato da chiamante
        bool castlingConditions(Pieces* king, Pieces* tower);
        //aggiorna log con mossa
        void updateLogMove(pair<int, int> start, pair<int, int> finish);
        //aggiorna log con pezzo inserito con promozione
        void updateLogPromotion(char newPiece);
        //aggiorna log con scacco
        void updateLogCheck();
        //mappa utilizzata in scanCheck
        map<pair<int, int>, string> directionsPieces{
            {pair<int, int>(1, 1), "PRAD"},
            {pair<int, int>(1, 0), "RDT"},
            {pair<int, int>(1, -1), "PRAD"},
            {pair<int, int>(0, -1), "RDT"},
            {pair<int, int>(-1, -1), "PRAD"},
            {pair<int, int>(-1, 0), "RDT"},
            {pair<int, int>(-1, 1), "PRAD"},
            {pair<int, int>(0, 1), "RDT"}};
        //vettore utilizzato in scanCheck
        vector<pair<int, int>> directionsHorse{
            pair<int, int>(1, 2), pair<int, int>(2, 1), pair<int, int>(2, -1), pair<int, int>(1, -2), pair<int, int>(-1, -2), pair<int, int>(-2, -1), pair<int, int>(-2, 1), pair<int, int>(-1, 2)};
};
//operatore di confronto per Move
//controlla se pezzo e posizione di arrivo sono uguali
bool operator==(const ChessBoard::Move& m1, const ChessBoard::Move& m2);

#endif