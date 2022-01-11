#include "chessBoard.h"

class replayBoard {
    public:
    //replay su file, video e entrambi
    void replayVideo ();
    void replayFile (string file);
    replayBoard (string log);

    private:
    //puntatore scacchiera, il nome del file di log
    ChessBoard* replay;
    string replayLog;
     
}