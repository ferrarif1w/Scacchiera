#include "chessBoard.h"
using namespace std;

bool ChessBoard::CheckBoundaries(pair<int, int> pos) {
    return (pos.first >= 0 && pos.first < SIZE && pos.second >= 0 && pos.second < SIZE);
}
