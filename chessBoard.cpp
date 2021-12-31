#include "chessBoard.h"
#include "Pieces.h"
#include <bits/stdc++.h>
using namespace std;

ChessBoard::Move::Move(Pieces* p, pair<int, int>* dest, int name, Pieces* add = nullptr) : 
piece {p}, destination {dest}, moveName {name}, additionalPiece {add} {}

bool operator==(const ChessBoard::Move& m1, const ChessBoard::Move& m2) {
    return (m1.piece == m2.piece && m1.destination == m2.destination);
}

bool ChessBoard::scanBoundaries(pair<int, int>* pos) {
    return (pos->first >= 0 && pos->first < SIZE && pos->second >= 0 && pos->second < SIZE);
}

char ChessBoard::scanOccupied(pair<int, int>* pos) {
    Pieces* piece = board[pos->first][pos->second];
    if (!piece) return 0;
    else return piece->GetColor();
}

bool ChessBoard::scanPromotion(Pieces* piece) {
    return (piece->GetName() == 80 && piece->GetPosition().first == 0 ||
        piece->GetName() == 112 && piece->GetPosition().first == 7);
}

bool ChessBoard::enPassantConditions(Pieces* p1, Pieces* p2) {
    if (!p2) return false;  //controlla se esiste pezzo
    char n1 = p1->GetName();
    char n2 = p2->GetName();
    int row2 = p2->GetPosition().first;
    int row1 = p1->GetPosition().first;
    return (row1 == row2 && (n2 == 80 && row2 == 4 || n2 == 112 && row2 == 3) &&
        lastMove->piece == p2 && p2->GetStatus() == 1 && n1-n2 != 0);
}

int ChessBoard::castlingConditions(Pieces* king, Pieces* tower) {
    if (!(king && tower)) return 0;
    if (!(king->GetStatus() == 0 && tower->GetStatus() == 0)) return 0;
    int start = king->GetPosition().second;
    int finish = tower->GetPosition().second;
    int row = king->GetPosition().first;
    int factor;
    if (start < finish) factor = 1;
    else factor = -1;
    for (int i = 1; i < abs(start-finish); i++) {
        pair<int, int>* tmp = new pair(row, start + i*factor);
        char result = scanOccupied(tmp);
        delete tmp;
        if (result != 0) return 0;
    }
    if (abs(start-finish) == 4) return 4;
    else return 3;
}

void ChessBoard::scanAddSpecialMoves(vector<ChessBoard::Move*>& moves, char color) {
    int offset = 0;
    if (color == 'B') offset = SIZE*2;
    //arrocco
    Pieces* firstTower = piecesList[0+offset];
    Pieces* secondTower = piecesList[7+offset];
    Pieces* king = piecesList[3+offset];
    //arrocco lungo
    if (castlingConditions(king, firstTower))
        moves.push_back(new ChessBoard::Move(king, new pair(0,2), 4, firstTower));
    //arrocco corto
    if (castlingConditions(king, secondTower))
        moves.push_back(new ChessBoard::Move(king, new pair(0,6), 3, firstTower));

    //en passant
    //per essere valido, un pedone bianco dev'essere nella riga 5, un pedone nero nella riga 4
    int moveIndex = 2;
    int direction;
    if (color == 'B') direction = 1;
    else direction = -1;
    for (int i = 0; i < SIZE; i++) {
        Pieces* pawn = piecesList[i+offset];
        pair<int, int> pos = pawn->GetPosition();
        Pieces* toTheLeft = board[pos.first][pos.second-1];
        Pieces* toTheRight = board[pos.first][pos.second+1];
        if (enPassantConditions(pawn, toTheLeft)) {
            pair<int, int>* destination = new pair(pos.first - direction, pos.second + direction);
            moves.push_back(new ChessBoard::Move(pawn, destination, moveIndex, toTheLeft));
        }
        if (enPassantConditions(pawn, toTheRight)) {
            pair<int, int>* destination = new pair(pos.first - direction, pos.second + direction);
            moves.push_back(new ChessBoard::Move(pawn, destination, moveIndex, toTheLeft));
        }
    }
}

void ChessBoard::insertPiece(Pieces* piece, pair<int, int>* pos) {
    board[pos->first][pos->second] = piece;
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
            insertPiece(piece, new pair(row, i));
        }
    }
    else if (row == 0 || row == 7) {
        piece = new T(pair(row, 0), color);
        insertPiece(piece, new pair(row, 0));
        piece = new C(pair(row, 1), color);
        insertPiece(piece, new pair(row, 1));
        piece = new A(pair(row, 2), color);
        insertPiece(piece, new pair(row, 2));
        piece = new D(pair(row, 3), color);
        insertPiece(piece, new pair(row, 3));
        piece = new R(pair(row, 4), color);
        insertPiece(piece, new pair(row, 4));
        piece = new A(pair(row, 5), color);
        insertPiece(piece, new pair(row, 5));
        piece = new C(pair(row, 6), color);
        insertPiece(piece, new pair(row, 6));
        piece = new T(pair(row, 7), color);
        insertPiece(piece, new pair(row, 7));
    }
}

ChessBoard::ChessBoard(string log) {
    for (int i = 0; i < 8; i++) board.push_back(vector<Pieces*>(8, nullptr));
    //inizializzare file
    initializeRow(0);
    initializeRow(1);
    initializeRow(6);
    initializeRow(7);
    lastMove = new ChessBoard::Move(nullptr, nullptr, -1, nullptr);
    pieceToPromote = nullptr;
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
    if (color == 'N') start = SIZE*2;
    for (int i = 0; i < SIZE*2; i++) {
        Pieces* piece = piecesList[start+i];
        vector<vector<pair<int, int>*>> pieceMoves = piece->Pmove();
        for (int j = 0; j < pieceMoves.size(); j++) {
            vector<pair<int, int>*> tmp = pieceMoves[j];
            for (int k = 0; k < tmp.size(); k++) {
                pair<int, int>* destination = tmp[k];
                if (!scanBoundaries(destination)) continue;
                Pieces* additionalPiece = nullptr;
                int moveName = 0;
                char occ = scanOccupied(destination);
                if (occ == color) break;
                else if (occ != color && occ != 0) { //ovvero occ = colore avversario
                    moveName++;
                    additionalPiece = board[destination->first][destination->second];
                }
                moves.push_back(new Move(piece, destination, moveName, additionalPiece));
                if (occ != 0 && pieceMoves.size() > 1) break;
            }
        }
    }
    scanAddSpecialMoves(moves, color);
    return moves;
}

Pieces* ChessBoard::performMove(ChessBoard::Move* move) {
    Pieces* piece = move->piece;
    pair<int, int> start = piece->GetPosition();
    pair<int, int> destination = *move->destination;
    piece->SetMove(destination);
    board[destination.first][destination.second] = piece;
    board[start.first][start.second] = nullptr;
    if (move->moveName == 1) {
        Pieces* additionalPiece = move->additionalPiece;
        *(find(piecesList.begin(), piecesList.end(), additionalPiece)) = nullptr;
        delete additionalPiece;
    }
    lastMove = move;
    if (scanPromotion(piece)) return piece;
    else return nullptr;
}

Pieces* ChessBoard::performMove(pair<int, int> start, pair<int, int> destination, char color) {
    vector<ChessBoard::Move*> moves = movesAvailable(color);
    Pieces* piece = board[start.first][start.second];
    ChessBoard::Move* tmpMove = new ChessBoard::Move(piece, &destination, 0, nullptr);
    auto result = find(moves.begin(), moves.end(), tmpMove);
    if (result == moves.end()) throw InvalidMoveException();
    return performMove(*result);
}

void ChessBoard::performPromotion(Pieces* piece, char newPiece) {
    
}