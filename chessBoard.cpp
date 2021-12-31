#include "chessBoard.h"
#include "Pieces.h"
#include <algorithm>
using namespace std;

ChessBoard::Move::Move(Pieces* p, pair<int, int> dest, int name, Pieces* add = nullptr) : 
piece {p}, destination {dest}, moveName {name}, additionalPiece {add} {}

bool ChessBoard::scanBoundaries(pair<int, int>* pos) {
    return (pos->first >= 0 && pos->first < SIZE && pos->second >= 0 && pos->second < SIZE);
}

bool ChessBoard::scanOccupied(pair<int, int>* pos) {
    return board[pos->first][pos->second] != nullptr;
}

bool ChessBoard::enPassantConditions(Pieces* p1, Pieces* p2) {
    if (!p2) return false;  //controlla se esiste pezzo
    char n1 = p1->GetName();
    char n2 = p2->GetName();
    int row2 = p2->GetPosition().first;
    return (lastMove.piece == p2 && p2->GetStatus() == 1 && (n2 == 80 || n2 == 112) && n1-n2 != 0);
}

/*bool ChessBoard::scanPromptPromotion(Pieces* piece) {
    if ()
}*/

void ChessBoard::scanAddSpecialMoves(vector<ChessBoard::Move*>& moves, char color) {
    int offset = 0;
    if (color == 'B') offset = SIZE*2;
    //arrocco corto/lungo
    Pieces* firstTower = piecesList[0+offset];
    Pieces* secondTower = piecesList[7+offset];
    Pieces* king = piecesList[3+offset];
    if (!(king && king->GetStatus() == 0)) return;
    if (firstTower && firstTower->GetStatus() == 0) {
        // arrocco lungo
        pair<int, int> destination(0, 2);
        int moveIndex = 4;
        moves.push_back(new ChessBoard::Move(king, destination, moveIndex, firstTower));   
    }
    if (secondTower && secondTower->GetStatus() == 0) {
        // arrocco corto
        pair<int, int> destination(0, 6);
        int moveIndex = 3;
        moves.push_back(new ChessBoard::Move(king, destination, moveIndex, secondTower));   
    }

    //en passant
    //per essere valido, un pedone bianco dev'essere nella riga 5, un pedone nero nella riga 4
    int moveIndex = 2;
    for (int i = 0; i < SIZE; i++) {
        Pieces* pawn = piecesList[i+offset];
        pair<int, int> pos = pawn->GetPosition();
        if (!(color == 'N' && pos.first == 3 || color == 'B' && pos.first == 4)) continue;
        Pieces* toTheLeft = board[pos.first][pos.second-1];
        Pieces* toTheRight = board[pos.first][pos.second+1];
        if (enPassantConditions(pawn, toTheLeft)) {
            pair<int, int> destination(pos.first - 1, pos.second + 1);
            moves.push_back(new ChessBoard::Move(pawn, destination, moveIndex, toTheLeft));
        }
        if (enPassantConditions(pawn, toTheLeft)) {
            pair<int, int> destination(pos.first - 1, pos.second + 1);
            moves.push_back(new ChessBoard::Move(pawn, destination, moveIndex, toTheLeft));
        }
    }
}

void ChessBoard::insertPiece(Pieces* piece, pair<int, int> pos) {
    board[pos.first][pos.second] = piece;
    piecesList.push_back(piece);
}

void ChessBoard::initializeRow(int row) {
    char color;
    if (row == 0 || row == 1) color = 'B';
    else color = 'N';
    Pieces* piece;
    if (row == 1 || row == 6) {   
        for (int i = 0; i < SIZE; i++) {
            piece = new P(pair(row, i), color);
            insertPiece(piece, pair(row, i));
        }
    }
    else if (row == 0 || row == 7) {
        piece = new T(pair(row, 0), color);
        insertPiece(piece, pair(row, 0));
        piece = new C(pair(row, 1), color);
        insertPiece(piece, pair(row, 1));
        piece = new A(pair(row, 2), color);
        insertPiece(piece, pair(row, 2));
        piece = new D(pair(row, 3), color);
        insertPiece(piece, pair(row, 3));
        piece = new R(pair(row, 4), color);
        insertPiece(piece, pair(row, 4));
        piece = new A(pair(row, 5), color);
        insertPiece(piece, pair(row, 5));
        piece = new C(pair(row, 6), color);
        insertPiece(piece, pair(row, 6));
        piece = new T(pair(row, 7), color);
        insertPiece(piece, pair(row, 7));
    }
}

ChessBoard::ChessBoard(string log) {
    for (int i = 0; i < 8; i++) board.push_back(vector<Pieces*>(8, nullptr));
    //inizializzare file
    initializeRow(0);
    initializeRow(1);
    initializeRow(6);
    initializeRow(7);
    lastMove.moveName = -1;
    logFile = log;
}

string ChessBoard::printBoard() {
    string out = "";
    for (int i = 7; i >= 0; i--) {
        out += to_string(i+1);
        out += " ";
        for (int j = 0; j < 8; j++) {
            if (board[i][j] != nullptr) out += board[i][j]->GetName();
            else out += " ";
        }
        out += "\n";
    }
    out += "\n";
    out += "  ABCDEFGH";
    return out;
}

vector<ChessBoard::Move*> ChessBoard::movesAvailable(char color) {
    vector<ChessBoard::Move*> moves;
    int start = 0;
    if (color = 'B') start = SIZE*2;
    for (int i = 0; i < SIZE*2; i++) {
        Pieces* piece = piecesList[start+i];
        vector<vector<pair<int, int>*>> pieceMoves = piece->Pmove();
        /*for (int j = 0; j < pieceMoves.size(); j++) {
            pair<int, int>* destination = pieceMoves[j];
            Pieces* additionalPiece = nullptr;
            int moveName = 0;
            if (scanOccupied(destination)) {
                additionalPiece = board[destination->first][destination->second];
                moveName++;
            }
            moves.push_back(new ChessBoard::Move(piece, *destination, moveName, additionalPiece));
        }*/
    }
    scanAddSpecialMoves(moves, color);
    return moves;
}

bool ChessBoard::performMove(ChessBoard::Move* move) {
    Pieces* piece = move->piece;
    pair<int, int> start = piece->GetPosition();
    pair<int, int> destination = (*move).destination;
    piece->SetMove(destination);
    board[destination.first][destination.second] = piece;
    board[start.first][start.second] = nullptr;
    if (move->moveName == 1) {
        Pieces* additionalPiece = move->additionalPiece;
        *(find(piecesList.begin(), piecesList.end(), additionalPiece)) = nullptr;
        delete additionalPiece;
    }
    lastMove = *move;
    scanPromptPromotion(piece);
}

void ChessBoard::performMove(pair<int, int> start, pair<int, int> destination, char color) {
    vector<ChessBoard::Move*> moves = movesAvailable(color);
    //if ()
}

bool operator==(const ChessBoard::Move& m1, const ChessBoard::Move& m2) {
    return (m1.piece == m2.piece && m1.destination == m2.destination);
}