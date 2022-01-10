#include "chessBoard.h"
using namespace std;

int main() {
    string playerWhite;
    string playerBlack;
    cout << "Inserire nome giocatore umano: ";
    cin >> playerWhite;
    cout << "Inserire nome giocatore robot: ";
    cin >> playerBlack;
    char P[4] {'A', 'T', 'C', 'R'};
    ChessBoard test("tests", playerBlack, playerWhite);
    int i = 0;
    int code = 0;
    char color;
    string t = "board.txt";
    cout << "Scacchiera creata: " << endl;
    cout << test.printBoard() << endl << endl;
    char te;
    cout << "Modificare scacchiera? ";
    cin >> te;
    if (te == 'y') {
        test.justForDebug(t);
        cout << "Scacchiera modificata" << endl;
        cout << "Scacchiera nuova: " << endl;
        cout << test.printBoard() << endl << endl;
    }
    while (i < 209) {
        if (i%2 == 0) color = 'B';
        else color = 'N';
        cout << "Turno di " << color << endl;
        /*cout << "Scegliere manualmente la mossa? ";
        cin >> te;*/
        if (color == 'B') {
            int cond = test.getCondition(color);
            switch (cond) {
                case 0:
                    cout << "scaccomatto" << endl;
                    cout << "partita finita" << endl;
                    return 0;
                case 1:
                    cout << "scacco" << endl;
                    break;
                case 2:
                    cout << "stallo" << endl;
                    cout << "partita finita" << endl;
                    return 0;
            }
            start:
            cout << "Inserire partenza e destinazione: " << endl;
            string start;
            string finish;
            cin >> start >> finish;
            int sFirst = start[1]-49;
            int sSecond = start[0]-65;
            int fFirst = finish[1]-49;
            int fSecond = finish[0]-65;
            bool result;
            try {result = test.performMove(pair(sFirst, sSecond), pair(fFirst, fSecond), color);}
            catch (ChessBoard::InvalidMoveException e) {
                cout << "La mossa inserita non è valida" << endl;
                goto start;
            }
            catch (ChessBoard::InvalidInputException e) {
                cout << "L'input inserito non è valido" << endl;
                goto start;
            }
            if (result) {
                cout << "Vuoi promuovere il pedone in " << finish << "? ";
                char answer;
                cin >> answer;
                if (answer == 'y') {
                    start2:
                    try {
                        cout << "Inserire il codice del pezzo a cui promuovere il pedone: ";
                        char code;
                        cin >> code;
                        test.performPromotion(code);
                    }
                    catch (ChessBoard::InvalidInputException e) {
                        cout << "L'input inserito non è valido" << endl;
                        goto start;
                    }
                }
            }
        }
        else {
            auto moves = test.movesAvailable(color);
            int cond = test.getCondition();
            cout << "Mosse create" << endl;
            switch (cond) {
                case 0:
                    cout << "scaccomatto" << endl;
                    cout << "partita finita" << endl;
                    return 0;
                case 1:
                    cout << "scacco" << endl;
                    break;
                case 2:
                    cout << "stallo" << endl;
                    cout << "partita finita" << endl;
                    return 0;
            }
            code = rand() % moves.size();
            cout << "Mossa effettuata" << endl;
            if (test.performMove(moves[code])) {
                int piece = rand() % 4;
                test.performPromotion(P[piece]);
                cout << "Promozione effettuata" << endl;
            }
        }
        cout << endl << "Scacchiera attuale: " << endl;
        cout << test.printBoard() << endl << endl;
        i++;
    }
}