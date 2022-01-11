#include "chessBoard.h"
#include "Gamers.h"
#include <iostream>
#include <chrono>
#include <thread>
using namespace std;

void printTextEffect(string s) {
    for (int i = 0; i < s.size(); i++) {
        this_thread::sleep_for(chrono::milliseconds(1));
        cout << s[i];
    }
    this_thread::sleep_for(chrono::milliseconds(250));
    cout << endl;
}

int main() {
    printTextEffect("Benvenuto nel gioco degli scacchi!");
    printTextEffect("Che partita vuoi fare? Inserire:");
    insertGame:
    printTextEffect("- pc: partita player vs. computer");
    printTextEffect("- cc: partita computer vs. computer");
    cout << endl;
    string game;
    cin >> game;
    string messagePlayer1;
    string messagePlayer2;
    if (game == "pc") {
        messagePlayer1 = "Inserire il nome del giocatore umano: ";
        messagePlayer2 = "Inserire il nome del giocatore computer: ";
    }
    else if (game == "cc") {
        messagePlayer1 = "Inserire il nome del primo giocatore computer: ";
        messagePlayer2 = "Inserire il nome del secondo giocatore computer: ";
    }
    else {
        printTextEffect("Input non valido, riprovare; si può inserire solo:");
        goto insertGame;
    }
    string nameWhite;
    string nameBlack;
    //se white == 0, primo giocatore inserito (giocatore oppure computer) ha il bianco
    //se white == 1, secondo giocatore inserito (computer) ha il bianco
    int whiteCode = rand() % 2;
    if (whiteCode == 0) {
        printTextEffect(messagePlayer1);
        cin >> nameWhite;
        printTextEffect(messagePlayer2);
        cin >> nameBlack;
    }
    else {
        printTextEffect(messagePlayer1);
        cin >> nameBlack;
        printTextEffect(messagePlayer2);
        cin >> nameWhite;
    }
    ChessBoard board = ChessBoard("log.txt", nameBlack, nameWhite);
    char typeWhite;
    char typeBlack;
    if (game == "cc") {
        typeWhite = 'B';
        typeBlack = 'B';
    }
    else if (game == "pc" && whiteCode == 0) {
        typeWhite = 'U';
        typeBlack = 'B';
    }
    else {
        typeWhite = 'B';
        typeBlack = 'U';
    }
    Gamers white = Gamers()
    int i = 0;
    while (true) {
        if (i%2 == 0) color = 'B';
        else color = 'N';
    }


    
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