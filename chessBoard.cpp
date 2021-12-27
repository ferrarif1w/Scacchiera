#include "chessBoard.h"
using namespace std;

bool ChessBoard::checkBoundaries(pair<int, int> pos) {
    return (pos.first >= 0 && pos.first < SIZE && pos.second >= 0 && pos.second < SIZE);
}

void ChessBoard::initializeRow(int row, char color) {
    if (row == 1 || row == 6) {   
        for (int i = 0; i < 8; i++) {
            board[1][i] = new P(Pair(row, i), color); 
            board[6][i] = new P(Pair(row, i), color);
        }
    }
    else if (row == 0 || row == 7) {
        board[row][0] = new T(Pair(row, i), color);
        board[row][1] = new C(Pair(row, i), color);
        board[row][2] = new A(Pair(row, i), color);
        board[row][3] = new D(Pair(row, i), color);
        board[row][4] = new R(Pair(row, i), color);
        board[row][5] = new A(Pair(row, i), color);
        board[row][6] = new C(Pair(row, i), color);
        board[row][7] = new T(Pair(row, i), color);
    }
}

ChessBoard::ChessBoard() {
    for (int i = 0; i < 8; i++) board.push_back(vector<Pieces*>(8, nullptr));
    //inizializzare file
}

string ChessBoard::printBoard() {
    string out = "";
    for (int i = 7; i >= 0; i--) {
        out += i+1;
        out += " ";
        for (int j = 0; j < 8; j++) {
            if (board[i][j] != nullptr) {
                //ritornare lettera con metodo di Pieces
            }
        }
        out += "\n";
    }
    out += "\n";
    out += "  ABCDEFGH";
    return out;
}