#include "chessBoard.h"
#include "Gamers.h"
#include <iostream>
#include <chrono>
#include <thread>
using namespace std;

//acronimo di printTextEffect
void PTE(string s, int delayShort = 1, int delayLong = 250) {
    for (int i = 0; i < s.size(); i++) {
        this_thread::sleep_for(chrono::milliseconds(delayShort));
        cout << s[i];
    }
    this_thread::sleep_for(chrono::milliseconds(delayLong));
    cout << endl;
}

int main() {
    const char B = 66;
    const char U = 85;
    srand(time(NULL));
    PTE("Benvenuto nel gioco degli scacchi!");
    PTE("Che partita vuoi fare? Inserire:");
    insertGame:
    PTE("- pc: partita player vs. computer");
    PTE("- cc: partita computer vs. computer");
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
        PTE("Inserisci il nome del giocatore umano: ");
        cin >> names[0];
        PTE("Giocherai con le pedine bianche!");
        names[1] = botNames[rand() % 10];
        PTE("Il bot si chiama " + names[1] + " e giocherà con le pedine nere.");
        types.push_back(U);
        types.push_back(B);
    }
    else if (game == "pc" && whiteCode == 1) {
        PTE("Inserisci il nome del giocatore umano: ");
        cin >> names[1];
        PTE("Giocherai con le pedine nere!");
        PTE("Se vuoi chiedere la patta, inserisci 'patta' quando ti chiede se vuoi stampare la scacchiera!");
        names[0] = botNames[rand() % 10];
        PTE("Il bot si chiama " + names[0] + " e giocherà con le pedine bianche.");
        types.push_back(B);
        types.push_back(U);
    }
    else if (game == "cc") {
        names[0] = botNames[rand() % 10];
        names[1] = botNames[rand() % 10];
        PTE("Il bot che giocherà con le pedine bianche si chiama " + names[0] + ".");
        PTE("Il bot che giocherà con le pedine nere si chiama " + names[1] + ".");
        types.push_back(B);
        types.push_back(B);
    }
    else {
        PTE("Input non valido, riprovare; si può inserire solo:");
        goto insertGame;
    }
    ChessBoard board = ChessBoard("log.txt", names[0], names[1]);
    players.push_back(Gamers('B', &board, names[0], types[0]));
    players.push_back(Gamers('N', &board, names[1], types[1]));
    PTE("Vuoi partire con una scacchiera personalizzata? ");
    char te;
    cin >> te;
    if (te == 'y') {
        board.justForDebug("board.txt");
        PTE("Ecco la nuova scacchiera!");
        cout << board.printBoard();
    }
    int i = 0;
    int movesThreshold;
    if (game == "cc") movesThreshold = 50;
    else movesThreshold = -1;
    int index;
    bool endgame = false;
    while (i != movesThreshold && !endgame) {
        int index = i%2;
        string message = "Turno di " + names[index] + " con le pedine ";
        if (index == 0) message += "bianche!";
        else message += "nere!";
        int cond = players[index].GetCondition();
        if (cond >= 9) {
            cond -= 10;
            if (cond != 0) {
                if (game == "pc") {
                    PTE("La configurazione attuale della scacchiera è comparsa per la terza volta! Vuoi dichiarare patta? ");
                    char draw;
                    cin >> draw;
                    if (draw == 'y') {
                        PTE("La partita termina in patta!");
                        endgame = true;
                        continue;
                    }
                    else {
                        PTE("Si continua a giocare!");
                        cond -= 10;
                    }
                }
                else {
                    PTE("La configurazione attuale della scacchiera è comparsa per la terza volta! I bot possono accordarsi per la patta?");
                    int decision = rand()%1000;
                    if (decision == 1) {
                        PTE("I bot si accordano per la patta! La partita termina!");
                        endgame = true;
                        continue;
                    }
                    else {
                        PTE("I bot decidono di continuare a giocare!");
                        cond -= 10;
                    }
                }
            }
        }
        switch (cond) {
            case 0:
                message = names[index] + " è in scaccomatto, ";
                if (index == 0) message += names[1];
                else message += names[0];
                message += " vince!";
                PTE(message);
                endgame = true;
                continue;
            case 1:
                message += " È sotto scacco!";
                PTE(message);
                break;
            case 2:
                PTE("È stato raggiunto uno stallo! Ecco la scacchiera finale:");
                cout << board.printBoard();
                endgame = true;
                continue;
            case 3:
                PTE("La partita termina in patta! Non ci sono abbastanza pezzi per eseguire uno scaccomatto! Ecco la scacchiera finale:");
                cout << board.printBoard();
                endgame = true;
                continue;
            case 4:
                PTE("La partita termina in patta! Sono state eseguite 50 mosse senza spostare pedoni o mangiare pezzi! Ecco la scacchiera finale:");
                cout << board.printBoard();
                endgame = true;
                continue;
        }
        Gamers p = players[index];
        if (types[index] == 'U') {
            PTE("Se vuoi stampare la scacchiera, inserire 'y': ");
            string code;
            cin >> code;
            if (code == "y") cout << board.printBoard();
            else if (code == "patta") {
                int decision = rand()%5;
                message = names[(i+1)%2];
                if (decision == 1) {
                    message += " accetta la patta!";
                    PTE(message);
                    endgame = true;
                    continue;
                }
                else {
                    message += " non accetta la patta! La partita continua!";
                    PTE(message);
                }
            }
            string start;
            string end;
            bool result;
            insertMove:
            PTE("Inserisci le coordinate del pezzo che vuoi spostare e della casella nella quale vuoi spostare il pezzo: ");
            cin >> start >> end;
            try {result = p.Move(start, end);}
            catch (ChessBoard::InvalidMoveException e) {
                PTE("La mossa inserita non è valida.");
                goto insertMove;
            }
            catch (ChessBoard::InvalidInputException e) {
                PTE("L'input inserito non è valido");
                goto insertMove;
            }
            if (result) {
                message = "Inserisci il pezzo in cui vuoi promuovere il pedone in ";
                pair<int, int> pos = board.getPawnToPromote();
                message += pos.second + 65;
                message += pos.first + 49;
                promotion:
                message += ":\n- A: alfiere;\n- C: cavallo;\n- D: regina;\n- T: torre.";
                PTE(message);
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
            int drawProposal = rand()%69;
            if (drawProposal == 1) {
                message = names[index] + " propone la patta! Vuoi accettare? ";
                char answer;
                cin >> answer;
                if (answer == 'y') {
                    PTE("Patta accettata!");
                    endgame = true;
                    continue;
                }
                else PTE("La partita continua!");
            }
            bool result = p.Move();
            PTE("Mossa effettuata!");
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
    if (game == "cc" && i == movesThreshold) 
        PTE("La partita termina in patta! È stata effettuata la 50esima mossa totale!");
    PTE("Grazie per aver giocato!"); 
}