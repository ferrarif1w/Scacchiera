#include "chessBoard.h"
#include "Gamers.h"
#include <iostream>
#include <chrono>
#include <thread>
using namespace std;

void printTextEffect(string s, int delayShort = 1, int delayLong = 250) {
    for (int i = 0; i < s.size(); i++) {
        this_thread::sleep_for(chrono::milliseconds(delayShort));
        cout << s[i];
    }
    this_thread::sleep_for(chrono::milliseconds(delayLong));
    cout << endl;
}

int main() {
    printTextEffect("Benvenuto nel gioco degli scacchi!");
    printTextEffect("Che partita vuoi fare? Inserire:");
    insertGame:
    printTextEffect("- pc: partita player vs. computer");
    printTextEffect("- cc: partita computer vs. computer");
    string game;
    cin >> game;
    vector<string> names(2);
    vector<char> types;
    vector<Gamers> players;
    vector<string> botNames{"Magnus", "Morphy", "Polgar", "Kasparov", "Gallo", "Shaldon", "Marius", "Bobbi", "Turing", "Pippo"};
    //se white == 0, primo giocatore inserito (giocatore oppure computer) ha il bianco
    //se white == 1, secondo giocatore inserito (computer) ha il bianco
    int whiteCode = rand() % 2;
    if (game == "pc" && whiteCode == 0) {
        printTextEffect("Inserisci il nome del giocatore umano: ");
        cin >> names[0];
        printTextEffect("Giocherai con le pedine bianche!");
        names[1] = botNames[rand() % 10];
        printTextEffect("Il bot si chiama " + names[1] + " e giocherà con le pedine nere.");
        types.push_back('U');
        types.push_back('B');
    }
    else if (game == "pc" && whiteCode == 1) {
        printTextEffect("Inserisci il nome del giocatore umano: ");
        cin >> names[1];
        printTextEffect("Giocherai con le pedine nere!");
        names[0] = botNames[rand() % 10];
        printTextEffect("Il bot si chiama " + names[0] + " e giocherà con le pedine bianche.");
        types.push_back('B');
        types.push_back('U');
    }
    else if (game == "cc") {
        names[0] = names[rand() % 10];
        names[1] = names[rand() % 10];
        printTextEffect("Il bot che giocherà con le pedine bianche si chiama " + names[0] + ".");
        printTextEffect("Il bot che giocherà con le pedine nere si chiama " + names[1] + ".");
        types.push_back('B');
        types.push_back('B');
    }
    else {
        printTextEffect("Input non valido, riprovare; si può inserire solo:");
        goto insertGame;
    }
    ChessBoard board = ChessBoard("log.txt", names[0], names[1]);
    players.push_back(Gamers('B', &board, names[0]));
    players.push_back(Gamers('N', &board, names[1]));
    int i = 0;
    int movesThreshold;
    if (game == "cc") movesThreshold = 50;
    else movesThreshold = -1;
    int index;
    while (i != movesThreshold) {
        int index = i%2;
        string message = "Turno di " + names[index] + " con le pedine ";
        if (index == 0) message += "bianche!";
        else message += "nere!";
        int cond = players[index].GetCondition();
        if (cond == 0) {
            message = names[index] + " è in scaccomatto, ";
            if (index = 0) message += names[1];
            else message += names[0];
            message += " vince!";
            printTextEffect(message);
            break;
        }
        else if (cond == 1) {
            message += "È sotto scacco!";
        }
        printTextEffect(message);
        Gamers p = players[index];
        if (types[index] == 'U') {
            printTextEffect("Se vuoi stampare la scacchiera, inserire 'y': ");
            char code;
            cin >> code;
            if (code == 'y') cout << board.printBoard();
            string start;
            string end;
            bool result;
            insertMove:
            printTextEffect("Inserisci le coordinate del pezzo che vuoi spostare e della casella nella quale vuoi spostare il pezzo: ");
            cin >> start >> end;
            try {result = p.Move(start, end);}
            catch (ChessBoard::InvalidMoveException e) {
                printTextEffect("La mossa inserita non è valida.");
                goto insertMove;
            }
            catch (ChessBoard::InvalidInputException e) {
                printTextEffect("L'input inserito non è valido");
                goto insertMove;
            }
            if (result) {
                message = "Inserisci il pezzo in cui vuoi promuovere il pedone in ";
                pair<int, int> pos = board.getPawnToPromote();
                message += pos.second + 65;
                message += pos.first + 49;
                promotion:
                message += ":\n- A: alfiere;\n- C: cavallo;\n- D: regina;\n- T: torre.";
                printTextEffect(message);
                char code;
                cin >> code;
                try {board.performPromotion(code);}
                catch (ChessBoard::InvalidInputException e) {
                    message = "L'input non è valido, inserisci una di queste lettere:";
                    goto promotion;
                }
            }
        }
        else {
            bool result = p.Move();
            printTextEffect("Mossa effettuata!");
            if (result) {
                pair<int, int> pos = board.getPawnToPromote();
                char newPiece = players[index].PerformPromotion();
                message = "Promozione effettuata: il pedone in ";
                message += pos.second + 65;
                message += pos.first + 49;
                message += " con ";
                switch (newPiece) {
                    case 'A':
                        message += " un alfiere!";
                        break;
                    case 'C':
                        message += " un cavallo!";
                        break;
                    case 'D':
                        message += " una regina!";
                        break;
                    case 'T':
                        message += " una torre!";
                        break;
                }
            }
        }
        i++;
    }

   
            
}