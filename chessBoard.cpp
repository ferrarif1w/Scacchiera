#include "chessBoard.h"
#include "Pieces.h"
using namespace std;

bool ChessBoard::checkBoundaries(pair<int, int> pos) {
    return (pos.first >= 0 && pos.first < SIZE && pos.second >= 0 && pos.second < SIZE);
}

void ChessBoard::initializeRow(int row) {
    char color;
    if (row == 0 || row == 1) color = 'N';
    else color = 'B';
    if (row == 1 || row == 6) {   
        for (int i = 0; i < 8; i++) {
            board[1][i] = new P(pair(row, i), color); 
            board[6][i] = new P(pair(row, i), color);
        }
    }
    else if (row == 0 || row == 7) {
        board[row][0] = new T(pair(row, 0), color);
        board[row][1] = new C(pair(row, 1), color);
        board[row][2] = new A(pair(row, 2), color);
        board[row][3] = new D(pair(row, 3), color);
        board[row][4] = new R(pair(row, 4), color);
        board[row][5] = new A(pair(row, 5), color);
        board[row][6] = new C(pair(row, 6), color);
        board[row][7] = new T(pair(row, 7), color);
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