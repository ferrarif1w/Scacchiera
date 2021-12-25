#include "chessBoard.h"
using namespace std;

bool ChessBoard::checkBoundaries(pair<int, int> pos) {
    return (pos.first >= 0 && pos.first < SIZE && pos.second >= 0 && pos.second < SIZE);
}

void ChessBoard::initializeRow(int row) {
    /*if (row == 1 || row == 6) {   
        for (int i = 0; i < 8; i++) {
            board[1][i] = new P();
            board[6][i] = new P();
        }
    }
    else if (row == 0 || row == 7) {
        board[0][0] = new T();
        board[0][1] = new C();
        board[0][2] = new A();
        board[0][3] = new D();
        board[0][4] = new R();
        board[0][5] = new A();
        board[0][6] = new C();
        board[0][7] = new T();
    }*/
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