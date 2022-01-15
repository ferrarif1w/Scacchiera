#include "chessBoard.h"
#include "Gamers.h"
#include "PTE.cpp"
#include <iostream>
using namespace std;

string CLN() {
    int i = -1;
    ifstream scanner;
    scanner.open("blank.txt");
    string name;
    while (true) {
        name = "logs/log" + to_string(++i) + ".txt";
        scanner.close();
        scanner.open(name);
        if (!scanner.good()) break;
    }
    return name;
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
        auto tmp = find(botNames.begin(), botNames.end(), names[0]);
        if (tmp != botNames.end()) botNames.erase(tmp);
        PTE("Giocherai con le pedine bianche!");
        PTE("Se vuoi chiedere la patta, inserisci 'patta' quando ti viene chiesto se vuoi stampare la scacchiera!");
        names[1] = botNames[rand() % botNames.size()];
        PTE("Il bot si chiama " + names[1] + " e giocherà con le pedine nere.");
        types.push_back(U);
        types.push_back(B);
    }
    else if (game == "pc" && whiteCode == 1) {
        PTE("Inserisci il nome del giocatore umano: ");
        cin >> names[1];
        auto tmp = find(botNames.begin(), botNames.end(), names[0]);
        if (tmp != botNames.end()) botNames.erase(tmp);
        PTE("Giocherai con le pedine nere!");
        PTE("Se vuoi chiedere la patta, inserisci 'patta' quando ti viene chiesto se vuoi stampare la scacchiera!");
        names[0] = botNames[rand() % botNames.size()];
        PTE("Il bot si chiama " + names[0] + " e giocherà con le pedine bianche.");
        types.push_back(B);
        types.push_back(U);
    }
    else if (game == "cc") {
        int nameIndex = rand() % 10;
        names[0] = botNames[nameIndex];
        botNames.erase(botNames.begin()+nameIndex);
        names[1] = botNames[rand() % 9];
        PTE("Il bot che giocherà con le pedine bianche si chiama " + names[0] + ".");
        PTE("Il bot che giocherà con le pedine nere si chiama " + names[1] + ".");
        types.push_back(B);
        types.push_back(B);
    }
    else {
        PTE("Input non valido, riprovare; si può inserire solo:");
        goto insertGame;
    }
    ChessBoard board = ChessBoard(CLN(), names[0], names[1]);
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
    if (game == "cc") movesThreshold = 150;
    else movesThreshold = -1;
    bool endgame = false;
    int cond = 0;
    while (/*i != movesThreshold && */!endgame) {
        /*if (game == "cc") {
            cout << board.printBoard();
            this_thread::sleep_for(chrono::seconds(2));
        }*/
        int index = i%2;
        string message = "Turno di " + names[index] + " con le pedine ";
        if (index == 0) message += "bianche!";
        else message += "nere!";
        cond = players[index].GetCondition();
        int drawDecision = rand()%20;
        if (cond >= 9) {
            if (cond-10 != 0) {
                if (game == "pc") {
                    PTE("La configurazione attuale della scacchiera è comparsa per la terza volta! Vuoi dichiarare patta? ");
                    char draw;
                    cin >> draw;
                    if (draw == 'y') {
                        PTE("La partita termina in patta!");
                        endgame = true;
                        cond = 5;
                        continue;
                    }
                    else {
                        PTE("Si continua a giocare!");
                        cond -= 10;
                    }
                }
                else {
                    PTE("La configurazione attuale della scacchiera è comparsa per la terza volta! I bot possono accordarsi per la patta!");
                    int decision = rand()%1000;
                    if (decision == 1) {
                        PTE("I bot si accordano per la patta! La partita termina!");
                        endgame = true;
                        cond = 5;
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
                PTE(names[index] + " è in scaccomatto, " + names[(i+1)%2] + " vince! Ecco la scacchiera finale:");
                cout << board.printBoard();
                endgame = true;
                continue;
            case 1:
                message += " È sotto scacco!";
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
            /*case 4:
                PTE("La partita termina in patta! Sono state eseguite 50 mosse senza spostare pedoni o mangiare pezzi! Ecco la scacchiera finale:");
                cout << board.printBoard();
                endgame = true;
                continue;*/
        }
        PTE(message);
        Gamers p = players[index];
        if (types[index] == 'U') {
            PTE("Se vuoi stampare la scacchiera, inserire 'y': ");
            string code;
            cin >> code;
            if (code == "y") cout << board.printBoard();
            else if (code == "patta") {
                if (drawDecision == 1) {
                    PTE(names[(i+1)%2] + " accetta la patta! La partita termina!");
                    cond = 7;
                    endgame = true;
                    continue;
                }
                else {
                    PTE(names[(i+1)%2] + " non accetta la patta! La partita continua!");
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
            int drawProposal = rand()%169;
            if (drawProposal == 1) {
                message = names[index] + " propone la patta!";
                if (game == "pc") {
                    message += "  Vuoi accettare? ";
                    PTE(message);
                    char answer;
                    cin >> answer;
                    if (answer == 'y') {
                        PTE("Patta accettata! La partita termina!");
                        endgame = true;
                        cond = 7;
                        continue;
                    }
                    else PTE("La partita continua!");
                }
                else {
                    PTE(message, 1 , 250);
                    if (drawDecision == 1) {
                        PTE(names[(i+1)%2] + " accetta la patta! La partita termina!", 1, 250);
                        endgame = true;
                        cond = 7;
                        continue;
                    }
                    else {
                        PTE(names[(i+1)%2] + " non accetta la patta! La partita continua!", 1, 250);
                    }
                }
            }
            bool result = p.Move();
            PTE("Mossa effettuata!");
            if (result) {
                pair<int, int> pos = board.getPawnToPromote();
                char newPiece = players[index].PerformPromotion();
                message = "Promozione effettuata: il pedone in ";
                message += pos.second + 65;
                message += pos.first + 49;
                message += " diventa ";
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
    //aggiorna log con informazioni su vittoria
    if (game == "cc" && i == movesThreshold) {
        PTE("La partita termina in patta! È stata effettuata la " + to_string(movesThreshold) + "esima mossa totale!");
        cond = 6;
    }
    board.updateLogVictory(cond);
    PTE("Grazie per aver giocato!"); 
}