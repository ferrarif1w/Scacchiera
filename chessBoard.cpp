#include "chessBoard.h"
#include "Pieces.h"
#include <algorithm>
using namespace std;

bool ChessBoard::scanBoundaries(pair<int, int>* pos) {
    return (pos->first >= 0 && pos->first < SIZE && pos->second >= 0 && pos->second < SIZE);
}

bool ChessBoard::scanOccupied(pair<int, int>* pos) {
    return board[pos->first][pos->second] != nullptr;
}

void ChessBoard::scanAddSpecialMoves(vector<ChessBoard::Move*>& moves, char color) {
    //arrocco corto/lungo
    Pieces* firstTower = piecesList[0];
    Pieces* secondTower = piecesList[7];
    Pieces* king = piecesList[3];
    if (!(king && king->GetStatus() == 0)) return;
    if (firstTower && firstTower->GetStatus() == 0) {
        // arrocco lungo
        pair<int, int> destination(0, 2);
        int moveIndex = 4;
        moves.push_back(new Move(king, destination, moveIndex, firstTower));   
    }
    if (secondTower && secondTower->GetStatus() == 0) {
        // arrocco corto
        pair<int, int> destination(0, 6);
        int moveIndex = 3;
        moves.push_back(new Move(king, destination, moveIndex, secondTower));   
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

ChessBoard::ChessBoard() {
    for (int i = 0; i < 8; i++) board.push_back(vector<Pieces*>(8, nullptr));
    //inizializzare file
    initializeRow(0);
    initializeRow(1);
    initializeRow(6);
    initializeRow(7);
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
        vector<pair<int, int>*> pieceMoves = piece->Pmove();
        for (int j = 0; j < pieceMoves.size(); j++) {
            pair<int, int>* destination = pieceMoves[j];
            Pieces* additionalPiece = nullptr;
            int moveName = 0;
            if (!scanBoundaries(destination)) continue;
            if (scanOccupied(destination)) {
                additionalPiece = board[destination->first][destination->second];
                moveName++;
            }
            scanAddSpecialMoves(moves, color);
        }
    }
    return moves;
}

void ChessBoard::performMove(Move* move) {
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
}