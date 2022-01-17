#include "chessBoard.h"
#include "PTE.cpp"
#include <regex>
using namespace std;

//metodo per cercare tutte le occorrenze di una regex in una stringa
vector<string> regexSearch(string arg, string expr) {
    regex exp{expr};
    smatch res;
    vector<string> results;
    auto searchStart = arg.cbegin();
    while (regex_search(searchStart, arg.cend(), res, exp)) {
        results.push_back(res[0]);
        searchStart = res.suffix().first;
    }
    return results;
}

int main() {
    PTE("Benvenuto nel replay delle partite di scacchi!");
    PTE("Cosa vuoi fare? Per ognuna delle seguenti opzioni inserire:");
    PTE("- replay a video: v 'nome del file di log'");
    PTE("- replay su file: f 'nome del file di log' 'nome del file dove effettuare il replay");
    PTE("Specificare l'estensione .txt dei file; se il file di replay inserito non esiste, verrà creato in questa cartella!");
    string arg;
    getline(cin, arg);
    char op = arg[0];
    //trova nomi dei file in stringa fornita come argomento
    //regex: combinazioni di qualsiasi carattere tranne spazi, almeno due caratteri
    vector<string> files = regexSearch(arg, "[^ ]{2,}");
    if (!(op == 'v' && files.size() == 1 || op == 'f' && files.size() == 2)) {
        PTE("L'input non è valido.");
        return 0;
    }
    string logFile = files[0];
    //se il nome del file non contiene l'estensione, viene aggiunta
    if (logFile.substr(logFile.size()-4) != ".txt") logFile += ".txt";
    ifstream scanner (logFile);
    //controlla se file di log inserito esiste
    if (!scanner.good()) {
        PTE("Il file di log inserito non esiste; reinserirlo.");
        return 0;
    }
    //ottiene nomi giocatori (prime due righe del log)
    string scannerLine;
    getline (scanner, scannerLine);
    string playerWhite = scannerLine.substr(3);
    getline (scanner, scannerLine);
    string playerBlack = scannerLine.substr(3);
    int i = -1;
    char color;
    string promotionPos;
    //se viene effettuato replay su file, viene aperto oggetto per scrivere su file
    ofstream replayFile;
    if (op == 'f') {
        if (files[1].substr(files[1].size()-4) != ".txt") files[1] += ".txt";
        replayFile.open(files[1]);
    }
    ChessBoard board = ChessBoard();
    int movesNumber = 0;
    while (getline(scanner, scannerLine)) {
        color = (i%2 == 0) ? 'B' : 'N';
        string message;
        bool pb = true;
        //terza riga: riga vuota, nessuna mossa
        if (i == -1) {
            pb = false;
            message = "La partita inizia: " + playerWhite + " con le pedine bianche e ";
            message += playerBlack + " con le pedine nere!";
        }
        //ultima riga del log: END: [numero che identifica finale]
        else if (scannerLine.substr(0, 4) == "END:") {
            pb = false;
            int ending = scannerLine[4] - 48;
            switch (ending) {
                case 0: //scaccomatto
                    message = (color == 'B') ? playerWhite : playerBlack;
                    message += " è in scaccomatto, ";
                    message += (color == 'B') ? playerBlack : playerWhite;
                    message += " vince!";
                    break;
                case 2: //stallo
                    message = "È stato raggiunto uno stallo! La partita termina!";
                    break;
                case 3: //patta per mancanza di pezzi
                    message = "La partita termina in patta! Non ci sono abbastanza pezzi per eseguire uno scaccomatto!";
                    break;
                case 4: //patta per 50 mosse
                    message = "La partita termina in patta! Sono state eseguite 50 mosse senza spostare pedoni o mangiare pezzi!";
                    break;
                case 5: //patta per ripetizione di posizione
                    message = (color == 'B') ? playerWhite : playerBlack;
                    message += " dichiara la patta dopo che la stessa posizione si è presentata per la terza volta!";
                    break;
                case 6: //patta per superamento limite di mosse in partita tra bot
                    message = "La partita termina in patta! È stato raggiunto il limite di mosse possibili per una partita tra bot!";
                    break;
                case 7: //patta per accordo
                    message = "I giocatori si accordano per la patta! La partita termina!";
                    break;
            }
            //stampa numero totale di mosse
            message += "\nSono state effettuate " + to_string(movesNumber) + " mosse in totale!";
        }
        //promozione effettuata: p [carattere che identifica nuovo pezzo]
        else if (scannerLine.size() == 3) {
            //viene decrementato l'indice che identifica il giocatore
            color = (--i%2 == 0) ? 'B' : 'N';
            //ottiene carattere che identifica il nuovo pezzo
            char promotionCode = scannerLine[2];
            //effettua promozione su scacchiera
            board.performPromotion(promotionCode);
            message = (color == 'B') ? playerWhite : playerBlack;
            message += " promuove il pedone in " + promotionPos + " in";
            switch (promotionCode) {
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
        //mossa regolare: c[riga di partenza][colonna di partenza] [riga di arrivo][colonna di arrivo]
        //(numerate 0-7) (c presente se giocatore corrente è sotto scacco)
        else {
            bool check = false;
            //controlla se è presente scacco
            if (scannerLine[0] == 'c') {
                check = true;
                scannerLine = scannerLine.substr(1);
            }
            //ottiene coordinate di partenza e arrivo
            char startRow = scannerLine[0];
            char startColumn = scannerLine[1];
            char endRow = scannerLine[3];
            char endColumn = scannerLine[4];
            //crea pair che indicano posizioni (verranno usate in performMove)
            pair<int, int> start = pair<int,int>(startRow-'0', startColumn-'0');
            pair<int, int> end = pair<int, int>(endRow - '0', endColumn - '0');
            //crea stringhe che rappresentano posizioni
            string startString;
            startString.push_back(static_cast<char>(startColumn + 17));
            startString.push_back(static_cast<char>(startRow + 1));
            string endString;
            endString.push_back(static_cast<char>(endColumn + 17));
            endString.push_back(static_cast<char>(endRow + 1));
            message = "Turno di " + ((color == 'B') ? playerWhite : playerBlack);
            if (check) message += " (è sotto scacco!)";
            message += ": " + startString + " in " + endString + "!";
            //se performMove ritorna true, promozione possibile: salva posizione del pedone
            if (board.performMove(start,end,color)) promotionPos = endString;
            //incrementa numero di mosse effettuate
            movesNumber++;
        }
        i++;
        //se replay a video, stampa messaggio costruito e scacchiera attuale a video
        if (op == 'v') {
            PTE(message);
            if (pb) {
                cout << board.printBoard();
                //this_thread::sleep_for(chrono::seconds(3));
            }
        }
        //se replay su file, scrive messaggio costruito e scacchiera attuale sul file
        else {
            replayFile << message << "\n";
            if (pb) replayFile << board.printBoard() << "\n\n";
        }
    }
    if (op == 'f') PTE("Replay effettuato su " + files[1] + "!");
    PTE("Replay finito!");
}