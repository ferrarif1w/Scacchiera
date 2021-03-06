#include "chessBoard.h"
using namespace std;

//costruttore di Move
ChessBoard::Move::Move(Pieces* p, pair<int, int> dest, int name, Pieces* add = nullptr) : 
piece {p}, destination {dest}, moveName {name}, additionalPiece {add} {}

//costruttore di defualt di Move
ChessBoard::Move::Move() : piece {nullptr}, destination {pair<int, int>(-1, -1)}, moveName{-1}, 
additionalPiece {nullptr} {}

//overloading dell'operatore == per Move: confronta pezzo e destinazione
bool operator==(const ChessBoard::Move& m1, const ChessBoard::Move& m2) {
    return (m1.piece == m2.piece && m1.destination == m2.destination);
}

//controlla se input della mossa è valido
bool ChessBoard::legitMoveInput(pair<int, int>& x) {
    return (x.first >= 0 && x.first < 8 && x.second >= 0 && x.second < 8);
}

//controlla se posizione inserita è all'interno della scacchiera
bool ChessBoard::scanBoundaries(pair<int, int>& pos) {
    return (pos.first >= 0 && pos.first < SIZE && pos.second >= 0 && pos.second < SIZE);
}

bool ChessBoard::scanBoundaries(int row, int column) {
    pair<int, int> tmp = pair<int, int>(row, column);
    bool result = scanBoundaries(tmp);
    return result;
}

char ChessBoard::scanOccupied(pair<int, int>& pos) {
    Pieces* piece = board[pos.first][pos.second];
    if (!piece) return 0;
    else return piece->GetColor();
}

char ChessBoard::scanOccupied(int row, int column) {
    pair<int, int> tmp = pair<int, int>(row, column);
    char result = scanOccupied(tmp);
    return result;
}

bool ChessBoard::scanPromotion(Pieces* piece) {
    return (piece->GetName() == 'P' && piece->GetPosition().first == 0 ||
        piece->GetName() == 'p' && piece->GetPosition().first == 7);
}

bool ChessBoard::scanCheck(char color, int row, int column) {
    int offset = 0;
    if (color == 'N') offset = SIZE*2;
    
    pair<int, int> pos;
    vector<vector<Pieces*>>* tmpBoard;
    if (row == -1 && column == -1) {
        Pieces* king = piecesList[4+offset];
        pos = king->GetPosition();
    }
    else pos = pair<int, int>(row, column);
    for (auto it = directionsPieces.begin(); it != directionsPieces.end(); ++it) {
        pair<int, int> direction = it->first;
        string pieces = it->second;
        pair<int, int> tmp = pair<int, int>(pos.first+direction.first, pos.second+direction.second);
        int i = 1;
        while (scanBoundaries(tmp)) {
            char pieceColor = scanOccupied(tmp);
            char pieceName;
            if (pieceColor != 0) {
                if (pieceColor == color) break;
                char pieceName = board[tmp.first][tmp.second]->GetName();
                if (pieceName > 90) pieceName -= 32;
                auto searchResult = find(pieces.begin(), pieces.end(), pieceName);
                if (searchResult != pieces.end() && ((pieceName != 'P' && pieceName != 'R') || 
                    i == 1)) return true;
                
                else break;
            }
            tmp.first += direction.first;
            tmp.second += direction.second;
            i++;
        }
    }
    for (int i = 0; i < directionsHorse.size(); i++) {
        pair<int, int> direction = directionsHorse[i];
        pair<int, int> tmp = pair<int, int>(pos.first+direction.first, pos.second+direction.second);
        if (scanBoundaries(tmp)) {
            char pieceColor = scanOccupied(tmp);
            if (pieceColor != 0 && pieceColor != color) {
                char pieceName = board[tmp.first][tmp.second]->GetName();
                if (pieceName > 90) pieceName -= 32;
                if (pieceName == 'C') return true;
            }
        }
    }
    return false;
}

bool ChessBoard::scanCheck(Move& move, char color) {
    vector<vector<Pieces*>> oldBoard = board;
    Pieces* piece = move.piece;
    pair<int, int> start = move.piece->GetPosition();
    pair<int, int> end = move.destination;
    board[end.first][end.second] = piece;
    board[start.first][start.second] = nullptr;
    switch (move.moveName) {
        case 0:
            break;
        case 3: {   //arrocco corto
                Pieces* tower = move.additionalPiece; //colonna attuale: 7, col. destinazione: 5
                pair<int, int> pos = tower->GetPosition();
                board[pos.first][pos.second] = nullptr;
                board[pos.first][pos.second-2] = tower;
                break;
            }
        case 4: {   //arrocco lungo
                Pieces* tower = move.additionalPiece; //colonna attuale: 0, col. destinazione: 4
                pair<int, int> pos = tower->GetPosition();
                board[pos.first][pos.second] = nullptr;
                board[pos.first][pos.second+3] = tower;
                break;
            }
    }
    bool result;
    if (piece->GetName() == 'R' || piece->GetName() == 'r') 
        result = scanCheck(color, end.first, end.second);
    else result = scanCheck(color);
    board = oldBoard;
    return result;
}

bool ChessBoard::scanCheckmate(bool initialCheck, vector<Move>& moves) {
    return initialCheck && moves.size() == 0;
}

bool ChessBoard::scanCheckmateImpossibility() {
    if (PLWK > 2) return false;
    if (PLWK == 0) return true;
    int horsesNumber = 0;
    vector<int> horsesIndexes{1, 6, 17, 22};
    for (int i : horsesIndexes) {
        if (piecesList[i]) horsesNumber++;
    }
    for (int i = 0; i < SIZE; i++) {
        Pieces* tmpB = piecesList[8+i];
        Pieces* tmpN = piecesList[24+i];
        if (tmpB && tmpB->GetName() == 'c') horsesNumber++;
        if (tmpN && tmpN->GetName() == 'C') horsesNumber++;
    }
    if (horsesNumber == 1 && PLWK == 1) return true;
    int WLSBN = 0; //alfieri bianchi campochiaro
    int BLSBN = 0; //alfieri neri campochiaro
    int WDSBN = 0; //alfieri bianchi camposcuro
    int BDSBN = 0; //alfieri neri camposcuro
    if (piecesList[2]) WDSBN++;
    if (piecesList[5]) WLSBN++;
    if (piecesList[18]) BLSBN++;
    if (piecesList[21]) BDSBN++;
    for (int i = 0; i < SIZE; i++) {
        Pieces* tmpB = piecesList[8+i];
        Pieces* tmpN = piecesList[24+i];
        if (tmpB && tmpB->GetName() == 'a') {
            if (i%2 == 0) WLSBN++;
            else WDSBN++;
        }
        if (tmpN && tmpN->GetName() == 'A') {
            if (i%2 == 0) BDSBN++;
            else BLSBN++;
        }
    }
    if (BDSBN + BLSBN + WDSBN + WLSBN == 1 && PLWK == 1) return true;
    if ((WLSBN == 1 && BLSBN == 1 || WDSBN == 1 && BDSBN == 1) && PLWK == 2) return true;
    return false;
}

bool ChessBoard::enPassantConditions(Pieces* p1, Pieces* p2) {
    if (!p2) return false;  //controlla se esiste pezzo
    char n1 = p1->GetName();
    char n2 = p2->GetName();
    int row2 = p2->GetPosition().first;
    int row1 = p1->GetPosition().first;
    return (row1 == row2 && (n2 == 'P' && row2 == 4 || n2 == 'p' && row2 == 3) &&
        lastMove.piece == p2 && p2->GetStatus() == 1 && n1-n2 != 0);
}

bool ChessBoard::castlingConditions(Pieces* king, Pieces* tower) {
    if (!(king && tower)) return 0;
    if (!(king->GetStatus() == 0 && tower->GetStatus() == 0)) return 0;
    int start = king->GetPosition().second;
    int finish = tower->GetPosition().second;
    int row = king->GetPosition().first;
    int tmp = tower->GetPosition().first;
    char color = king->GetColor();
    if (row != tmp) return 0; //DA TOGLIERE INSIEME A JUSTFORDEBUG
    int factor;
    if (start < finish) factor = 1;
    else factor = -1;
    if (scanCheck(color)) return false;
    for (int i = 1; i < abs(start-finish); i++) {
        Move tmp = Move(king, pair<int, int>(row, start + i*factor), 0);
        if (scanOccupied(row, start + i*factor) != 0 || (i <= 2 && scanCheck(tmp, color)))
            return false;
    }
    return true;
}

void ChessBoard::scanAddSpecialMoves(vector<Move>& moves, char color) {
    int offset = 0;
    if (color == 'N') offset = SIZE*2;

    //arrocco
    Pieces* firstTower = piecesList[0+offset];
    Pieces* secondTower = piecesList[7+offset];
    Pieces* king = piecesList[4+offset];
    int row = (color == 'B') ? 0 : 7;
    //arrocco lungo
    if (castlingConditions(king, firstTower))
        moves.push_back(Move(king, pair<int, int>(row,2), 4, firstTower));
    //arrocco corto
    if (castlingConditions(king, secondTower))
        moves.push_back(Move(king, pair<int, int>(row,6), 3, secondTower));

    //en passant + controllare se pedoni hanno pedine da mangiare in diagonale
    //per essere valido, un pedone bianco dev'essere nella riga 5, un pedone nero nella riga 4
    int direction;
    if (color == 'B') direction = 1;
    else direction = -1;
    Move tmp;
    for (int i = 0; i < SIZE; i++) {
        Pieces* pawn = piecesList[8+i+offset];
        if (!pawn) continue;
        if (pawn->GetName() != 80 && pawn->GetName() != 112) continue;
        pair<int, int> pos = pawn->GetPosition();
        if (scanBoundaries(pos.first, pos.second-direction)) {
            Pieces* toTheLeft = board[pos.first][pos.second-direction];
            pair<int, int> destination = pair<int, int>(pos.first + direction, pos.second - direction);
            tmp = Move(pawn, destination, 2, toTheLeft);
            if (enPassantConditions(pawn, toTheLeft) && !scanCheck(tmp, color))
                moves.push_back(tmp);
        }
        if (scanBoundaries(pos.first, pos.second+direction)) {
            Pieces* toTheRight = board[pos.first][pos.second+direction];
            pair<int, int> destination = pair<int, int>(pos.first + direction, pos.second + direction);
            tmp = Move(pawn, destination, 2, toTheRight);
            if (enPassantConditions(pawn, toTheRight) && !scanCheck(tmp, color))
                moves.push_back(tmp);
        }
        if (scanBoundaries(pos.first+direction, pos.second-direction)) {
            Pieces* forwardLeft = board[pos.first+direction][pos.second-direction];
            pair<int, int> destination = pair<int, int>(pos.first + direction, pos.second - direction);
            tmp = Move(pawn, destination, 1, forwardLeft);
            if (forwardLeft && forwardLeft->GetColor() != color && !scanCheck(tmp, color))
                moves.push_back(tmp);
        }
        if (scanBoundaries(pos.first+direction, pos.second+direction)) {
            Pieces* forwardRight = board[pos.first+direction][pos.second+direction];
            pair<int, int> destination = pair<int, int>(pos.first + direction, pos.second + direction);
            tmp = Move(pawn, destination, 1, forwardRight);
            if (forwardRight && forwardRight->GetColor() != color && !scanCheck(tmp, color))
                moves.push_back(tmp);
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
            piece = new P(pair<int, int>(row, i), color);
            insertPiece(piece, new pair<int, int>(row, i));
        }
    }
    else if (row == 0 || row == 7) {
        piece = new T(pair<int, int>(row, 0), color);
        insertPiece(piece, new pair<int, int>(row, 0));
        piece = new C(pair<int, int>(row, 1), color);
        insertPiece(piece, new pair<int, int>(row, 1));
        piece = new A(pair<int, int>(row, 2), color);
        insertPiece(piece, new pair<int, int>(row, 2));
        piece = new D(pair<int, int>(row, 3), color);
        insertPiece(piece, new pair<int, int>(row, 3));
        piece = new R(pair<int, int>(row, 4), color);
        insertPiece(piece, new pair<int, int>(row, 4));
        piece = new A(pair<int, int>(row, 5), color);
        insertPiece(piece, new pair<int, int>(row, 5));
        piece = new C(pair<int, int>(row, 6), color);
        insertPiece(piece, new pair<int, int>(row, 6));
        piece = new T(pair<int, int>(row, 7), color);
        insertPiece(piece, new pair<int, int>(row, 7));
    }
}

void ChessBoard::updateLogMove(pair<int, int> start, pair<int, int> end) {
    ofstream write;
    write.open(logFile, ofstream::app);
    string out;
    out += to_string(start.first) + to_string(start.second) + " ";
    out += to_string(end.first) + to_string(end.second) + "\n";
    write << out;
    write.close();
}

void ChessBoard::updateLogPromotion(char newPiece) {
    ofstream write;
    write.open(logFile, ofstream::app);
    write << "p " << newPiece << "\n";
    write.close();
}

void ChessBoard::updateLogCheck() {
    ofstream write;
    write.open(logFile, ofstream::app);
    write << "c";
    write.close();
}

void ChessBoard::updateLogVictory(int ending) {
    ofstream write;
    write.open(logFile, ofstream::app);
    write << "END:" << ending;
    write.close();
}

void ChessBoard::updateLogGameType(string type) {
    ofstream write;
    write.open(logFile, ofstream::app);
    write << type << "\n";
    write.close();
}

ChessBoard::ChessBoard(string log, string playerWhite, string playerBlack) {
    for (int i = 0; i < 8; i++) board.push_back(vector<Pieces*>(8, nullptr));
    //inizializzare file
    initializeRow(0);
    initializeRow(1);
    initializeRow(7);
    initializeRow(6);
    lastMove = Move();
    nextPlayerMoves.push_back(Move());
    pieceToPromote = nullptr;
    logFile = log;
    drawMoves = 0;
    PLWK = 30;
    if (log != "" && playerWhite != "" && playerBlack != "") {
        ofstream write(logFile);
        string playerRow = "B: " + playerWhite + "\nN: " + playerBlack + "\n\n";
        write << playerRow;
        write.close();
    }
}

string ChessBoard::printBoard() {
    string out = "";
    out += "   ┌───┬───┬───┬───┬───┬───┬───┬───┐\n";
    for (int i = 7; i >= 0; i--) {
        out += to_string(i+1);
        out += "  │ ";
        for (int j = 0; j < 8; j++) {
            if (board[i][j] != nullptr) out += board[i][j]->GetName();
            else out += " ";
            out += " │ ";
        }
        out += "\n";
        if (i >= 1) out += "   ├───┼───┼───┼───┼───┼───┼───┼───┤\n";
    }
    out += "   └───┴───┴───┴───┴───┴───┴───┴───┘\n";
    out += "     A   B   C   D   E   F   G   H\n\n";
    return out;
}

int ChessBoard::getCondition(char color) {
    Pieces* tmp = nextPlayerMoves[0].piece;
    if (condition == -1 || condition == 1) nextPlayerMoves = movesAvailable(color);
    if (condition != 0 && condition != 2) {
        try {
            if (scanCheckmateImpossibility()) condition = 3;
            else if (drawMoves >= 50) condition = 4;
            else if (positions.at(printBoard()) == 3) {
                condition = 5;
                positions.erase(printBoard());
            }
        }
        catch (out_of_range& e) {}
    }
    return condition;
}

vector<ChessBoard::Move> ChessBoard::movesAvailable(char color) {
    vector<Move> moves;
    int start = 0;
    if (color == 'N') start = SIZE*2;
    bool initialCheck = scanCheck(color);
    for (int i = 0; i < SIZE*2; i++) {
        Pieces* piece = piecesList[start+i];
        if (!piece) continue;
        vector<vector<pair<int, int>>> pieceMoves = piece->Pmove();
        for (int j = 0; j < pieceMoves.size(); j++) {
            vector<pair<int, int>> tmp = pieceMoves[j];
            for (int k = 0; k < tmp.size(); k++) {
                pair<int, int> destination = tmp[k];
                if (!scanBoundaries(destination)) continue;
                Pieces* additionalPiece = nullptr;
                int moveName = 0;
                char occ = scanOccupied(destination);
                if (occ != 0 && (piece->GetName() == 80 || piece->GetName() == 112)) break;
                else if (occ == color && pieceMoves.size() > 1) break;
                else if (occ == color && pieceMoves.size() == 1) continue;
                else if (occ != color && occ != 0) { //ovvero occ = colore avversario
                    moveName++;
                    additionalPiece = board[destination.first][destination.second];
                }
                Move move = Move(piece, destination, moveName, additionalPiece);
                if (!scanCheck(move, color))
                    moves.push_back(Move(piece, destination, moveName, additionalPiece));
                if (occ != 0 && pieceMoves.size() > 1) break;
            }
        }
    }
    scanAddSpecialMoves(moves, color);
    if (scanCheckmate(initialCheck, moves)) condition = 0;
    else if (initialCheck) {
        if (logFile != "") updateLogCheck();
        condition = 1;
    }
    else if (moves.size() == 0) condition = 2;
    else condition = -1;
    return moves;
}

bool ChessBoard::performMove(Move move) {
    pieceToPromote = nullptr;
    Pieces* piece = move.piece;
    pair<int, int> start = piece->GetPosition();
    pair<int, int> destination = move.destination;
    int name = move.moveName;
    piece->SetMove(destination);
    board[destination.first][destination.second] = piece;
    board[start.first][start.second] = nullptr;
    switch (name) {
        case 0:
            break;
        case 3: {   //arrocco corto
                Pieces* tower = move.additionalPiece; //colonna attuale: 7, col. destinazione: 5
                pair<int, int> pos = tower->GetPosition();
                tower->SetMove(pair<int, int>(pos.first, pos.second-2));
                board[pos.first][pos.second] = nullptr;
                board[pos.first][pos.second-2] = tower;
                break;
            }
        case 4: {   //arrocco lungo
                Pieces* tower = move.additionalPiece; //colonna attuale: 0, col. destinazione: 4
                pair<int, int> pos = tower->GetPosition();
                tower->SetMove(pair<int, int>(pos.first, pos.second+3));
                board[pos.first][pos.second] = nullptr;
                board[pos.first][pos.second+3] = tower;
                break;
            }
        default:    //mossa normale con cattura, en passant
            Pieces* additionalPiece = move.additionalPiece;
            *(find(piecesList.begin(), piecesList.end(), additionalPiece)) = nullptr;
            if (name == 2) {
                pair<int, int> pawnPos = additionalPiece->GetPosition();
                board[pawnPos.first][pawnPos.second] = nullptr;
            }
            delete additionalPiece;
            PLWK--;
            break;
    }
    if (piece->GetName() != 'P' && piece->GetName() != 'p' && name != 1 && name != 2) drawMoves++;
    else drawMoves = 0;
    condition = -1;
    lastMove = move;
    positions[printBoard()]++;
    if (logFile != "") updateLogMove(start, destination);
    if (scanPromotion(piece)) {
        pieceToPromote = piece;
        return true;
    }
    return false;
}

bool ChessBoard::performMove(pair<int, int>& start, pair<int, int>& destination, char color) {
    if (!(legitMoveInput(start) && legitMoveInput(destination))) throw InvalidInputException();
    if (color != 0) nextPlayerMoves = movesAvailable(color);
    Pieces* piece = board[start.first][start.second];
    Move tmpMove = Move(piece, destination, 0, nullptr);
    auto result = find(nextPlayerMoves.begin(), nextPlayerMoves.end(), tmpMove);
    if (result == nextPlayerMoves.end()) throw InvalidMoveException();
    return performMove(*result);
}

bool ChessBoard::performMove() {
    int i = rand() % nextPlayerMoves.size();
    Move m = nextPlayerMoves[i];
    return performMove(m);
}

void ChessBoard::performPromotion(char code) {
    pair<int, int> pos = pieceToPromote->GetPosition();
    char color = pieceToPromote->GetColor();
    int moves = pieceToPromote->GetStatus();
    Pieces* newPiece;
    switch (code) {
        case 'A':    //alfiere
            newPiece = new A(pos, color, moves);
            break;
        case 'C':    //cavallo
            newPiece = new C(pos, color, moves);
            break;
        case 'D':    //regina
            newPiece = new D(pos, color, moves);
            break;
        case 'T':    //torre
            newPiece = new T(pos, color, moves);
            break;
        default:
            throw InvalidInputException();
    }
    board[pos.first][pos.second] = newPiece;
    *(find(piecesList.begin(), piecesList.end(), pieceToPromote)) = newPiece;
    delete pieceToPromote;
    if (logFile != "") updateLogPromotion(code);
}

pair<int, int> ChessBoard::getPawnToPromote() {
    return pieceToPromote->GetPosition();
}

void ChessBoard::justForDebug(string fileName) {
    PLWK = 0;
    for (int i = 0; i < 32; i++) delete piecesList[i];
    piecesList = vector<Pieces*>(32, nullptr);
    board = vector<vector<Pieces*>>(8, vector<Pieces*>(8, nullptr));
    vector<Pieces*> blackPawns;
    vector<Pieces*> whitePawns;
    string line;
    ifstream reader(fileName);
    Pieces* piece;
    for (int i = 7; i >= 0; i--) {
        getline(reader, line);
        for (int j = 0; j < 8; j++) {
            char character = line[j];
            if (character != '-') {
                char color = 'N';
                int index = 0;
                if (character > 90) {
                    character -= 32;
                    color = 'B';
                }
                if (color == 'N') index += 16;
                PLWK++;
                switch (character) {
                    case 'A':
                        piece = new A(pair<int, int>(i, j), color);
                        //alfiere campochiaro
                        if (abs(i-j)%2 == 1) index += (color == 'N') ? 2 : 5;
                        // alfiere camposcuro
                        else if (abs(i-j)%2 == 0) index += (color == 'N') ? 5 : 2;
                        else index = -1;
                        break;
                    case 'C':
                        piece = new C(pair<int, int>(i, j), color);
                        if (!piecesList[index+1]) index += 1;
                        else if (!piecesList[index+6]) index += 6;
                        else index = -1;
                        break;
                    case 'D':
                        piece = new D(pair<int, int>(i, j), color);
                        if (!piecesList[index+3]) index += 3;
                        else index = -1;
                        break;
                    case 'P':
                        piece = new P(pair<int, int>(i, j), color);
                        index = -1;
                        break;
                    case 'R':
                        piece = new R(pair<int, int>(i, j), color);
                        index += 4;
                        PLWK--;
                        break;
                    case 'T':
                        piece = new T(pair<int, int>(i, j), color);
                        if ((color == 'N' && i == 7 || color == 'B' && i == 0) && j == 0) index += 0;
                        else if ((color == 'N' && i == 7 || color == 'B' && i == 0) && j == 7) index += 7;
                        else if (!piecesList[index]) index += 0;
                        else if (!piecesList[index+7]) index += 7;
                        else index = -1;
                        break;
                }
                board[i][j] = piece;
                if (index == -1) {
                    if (color == 'N') blackPawns.push_back(piece);
                    else whitePawns.push_back(piece);
                }
                else piecesList[index] = piece;
            }
        }
    }
    int startIndex = 8;
    for (int i = 0; i < whitePawns.size(); i++) {
        piecesList[startIndex+i] = whitePawns[i];
    }
    startIndex = 24;
    for (int i = 0; i < blackPawns.size(); i++) {
        piecesList[startIndex+i] = blackPawns[i];
    }
}