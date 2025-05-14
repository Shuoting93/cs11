#include <iostream>
#include <string>
using namespace std;

// Player class
class Player {
private:
    char symbol;
    string name;

public:
    Player(char sym = 'X', string n = "Player X") : symbol(sym), name(n) {}
    char getSymbol() const { return symbol; }
    string getName() const { return name; }
};

// Board class
class Board {
private:
    char grid[3][3];
    int filledCells;

public:
    Board() : filledCells(0) {
        char ch = '1';
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                grid[i][j] = ch++;
    }

    void drawBoard() const {
        for (int i = 0; i < 3; i++) {
            cout << " " << grid[i][0] << " | " << grid[i][1] << " | " << grid[i][2] << " \n";
            if (i < 2) cout << "---+---+---\n";
        }
    }

    bool isValidMove(int pos) const {
        if (pos < 1 || pos > 9) return false;
        int row = (pos - 1) / 3;
        int col = (pos - 1) % 3;
        return grid[row][col] != 'X' && grid[row][col] != 'O';
    }

    void makeMove(int pos, char symbol) {
        int row = (pos - 1) / 3;
        int col = (pos - 1) % 3;
        grid[row][col] = symbol;
        filledCells++;
    }

    bool checkWin(char sym) const {
        for (int i = 0; i < 3; i++)
            if (grid[i][0] == sym && grid[i][1] == sym && grid[i][2] == sym) return true;
        for (int i = 0; i < 3; i++)
            if (grid[0][i] == sym && grid[1][i] == sym && grid[2][i] == sym) return true;
        if (grid[0][0] == sym && grid[1][1] == sym && grid[2][2] == sym) return true;
        if (grid[0][2] == sym && grid[1][1] == sym && grid[2][0] == sym) return true;
        return false;
    }

    bool isFull() const { return filledCells == 9; }
};

// Game class
class TicTacToe {
private:
    Board board;
    Player players[2];
    int currentPlayerIndex;

public:
    TicTacToe() : currentPlayerIndex(0) {
        players[0] = Player('X', "Player 1");
        players[1] = Player('O', "Player 2");
    }

    void switchTurn() {
        currentPlayerIndex = 1 - currentPlayerIndex;
    }

    void play() {
        cout << "-- Tic Tac Toe -- CSIE@CGU\n";
        cout << "Player 1 (X) - Player 2 (O)\n";
        board.drawBoard();

        while (!board.isFull()) {
            Player& currentPlayer = players[currentPlayerIndex];
            int pos;

            while (true) {
                cout << "==> " << currentPlayer.getName() << " (" << currentPlayer.getSymbol() << "), enter a number:";
                cin >> pos;
                if (board.isValidMove(pos)) break;
                cout << "==> Invalid value, please enter again\n";
            }

            board.makeMove(pos, currentPlayer.getSymbol());
            board.drawBoard();

            if (board.checkWin(currentPlayer.getSymbol())) {
                cout << "==> " << currentPlayer.getName() << " wins!\n";
                return;
            }

            switchTurn();
        }

        cout << "==> Game draw\n";
    }
};

int main() {
    TicTacToe game;
    game.play();
    return 0;
}
