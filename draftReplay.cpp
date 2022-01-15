#include "chessBoard.h"
#include "PTE.cpp"
#include <regex>
using namespace std;

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
    vector<string> files = regexSearch(arg, "[^ ]{2,}");
    //se mi rispondono di sì, [\[][^\[\]]+[\]]
    if (!(op == 'v' && files.size() == 1 || op == 'f' && files.size() == 2)) {
        PTE("L'input non è valido.");
        return 0;
    }
    string logFile = files[0];
    if (logFile.substr(logFile.size()-4) != ".txt") logFile += ".txt";
    ifstream scanner (logFile);
    if (!scanner.good()) {
        PTE("Il file di log inserito non esiste; reinserirlo.");
        return 0;
    }
    string scannerLine;
    getline (scanner, scannerLine);
    string playerWhite = scannerLine.substr(3);
    getline (scanner, scannerLine);
    string playerBlack = scannerLine.substr(3);
    int i = -1;
    char color;
    string promotionPos;
    ofstream replayFile;
    if (op == 'f') {
        string tmp = files[1];
        if (tmp.substr(tmp.size()-4) != ".txt") tmp += ".txt";
        replayFile.open(tmp);
    }
    ChessBoard board = ChessBoard();
    while (getline(scanner, scannerLine)) {
        color = (i%2 == 0) ? 'B' : 'N';
        string message;
        bool pb = true;
        if (i == -1) {
            pb = false;
            message = "La partita inizia: " + playerWhite + " con le pedine bianche e ";
            message += playerBlack + " con le pedine nere!";
        }
        else if (scannerLine.substr(0, 4) == "END:") {
            pb = false;
            int ending = scannerLine[4] - 48;
            switch (ending) {
                case 0:
                    message = (color == 'B') ? playerWhite : playerBlack;
                    message += " è in scaccomatto, ";
                    message += (color == 'B') ? playerBlack : playerWhite;
                    message += " vince!";
                    break;
                case 2:
                    message = "È stato raggiunto uno stallo! La partita termina!";
                    break;
                case 3:
                    message = "La partita termina in patta! Non ci sono abbastanza pezzi per eseguire uno scaccomatto!";
                    break;
                case 4:
                    message = "La partita termina in patta! Sono state eseguite 50 mosse senza spostare pedoni o mangiare pezzi!";
                    break;
                case 5:
                    message = (color == 'B') ? playerWhite : playerBlack;
                    message += " dichiara la patta dopo che la stessa posizione si è presentata per la terza volta!";
                    break;
                case 6:
                    message = "La partita termina in patta! È stato raggiunto il limite di mosse possibili per una partita tra bot!";
                    break;
                case 7:
                    message = "I giocatori si accordano per la patta! La partita termina!";
                    break;
            }
        }
        else if (scannerLine.size() == 3) {
            color = (--i%2 == 0) ? 'B' : 'N';
            char promotionCode = scannerLine[2];
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
        else {
            bool check = false;
            if (scannerLine[0] == 'c') {
                check = true;
                scannerLine = scannerLine.substr(1);
            }
            char startRow = scannerLine[0];
            char startColumn = scannerLine[1];
            char endRow = scannerLine[3];
            char endColumn = scannerLine[4];
            pair<int,int> start = pair<int,int>(startRow-'0', startColumn-'0');
            pair<int, int> end = pair<int, int>(endRow - '0', endColumn - '0');
            string startString;
            startString.push_back(static_cast<char>(startColumn + 17));
            startString.push_back(static_cast<char>(startRow + 1));
            string endString;
            endString.push_back(static_cast<char>(endColumn + 17));
            endString.push_back(static_cast<char>(endRow + 1));
            message = "Turno di " + ((color == 'B') ? playerWhite : playerBlack);
            if (check) message += " (è sotto scacco!)";
            message += ": " + startString + " in " + endString + "!";
            if (board.performMove(start,end,color)) promotionPos = endString;
        }
        i++;
        if (op == 'v') {
            PTE(message);
            if (pb) {
                cout << board.printBoard();
                this_thread::sleep_for(chrono::seconds(3));
            }
        }
        else {
            replayFile << message << "\n";
            if (pb) replayFile << board.printBoard() << "\n\n";
        }
    }
    if (op == 'f') PTE("Replay effettuato su " + files[1] + "!");
    PTE("Replay finito!");
}