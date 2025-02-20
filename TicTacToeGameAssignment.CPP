#include <iostream>
#include <vector>
#include <stdexcept>

class TicTacToe {
private:
    std::vector<std::vector<char>> board;
    int size;
    char currentPlayer;

public:
    TicTacToe(int n = 3) : size(n), currentPlayer('X'), board(n, std::vector<char>(n, '-')) {}

    void printBoard() const {
        for (const auto &row : board) {
            for (const auto &cell : row) {
                std::cout << cell << ' ';
            }
            std::cout << '\n';
        }
        std::cout << '\n';
    }

    void makeMove(int move) {
        if (move < 1 || move > size * size) {
            throw std::out_of_range("Move must be within valid range");
        }
        int row = (move - 1) / size;
        int col = (move - 1) % size;
        if (board[row][col] != '-') {
            throw std::invalid_argument("Cell is already occupied");
        }
        board[row][col] = currentPlayer;
    }

    bool isComplete() const {
        for (const auto &row : board) {
            for (char cell : row) {
                if (cell == '-') return false;
            }
        }
        return true;
    }

    bool checkWin() const {
        // Check rows, columns and diagonals
        int countDiag1 = 0, countDiag2 = 0;
        for (int i = 0; i < size; ++i) {
            int countRow = 0, countCol = 0;
            for (int j = 0; j < size; ++j) {
                if (board[i][j] == currentPlayer) ++countRow;
                if (board[j][i] == currentPlayer) ++countCol;
            }
            if (countRow == size || countCol == size) return true;

            if (board[i][i] == currentPlayer) ++countDiag1;
            if (board[i][size - i - 1] == currentPlayer) ++countDiag2;
        }
        if (countDiag1 == size || countDiag2 == size) return true;

        return false;
    }

    void nextPlayer() {
        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }

    char getCurrentPlayer() const {
        return currentPlayer;
    }
};

int main() {
    TicTacToe game;
    bool hasWinner = false;

    while (!game.isComplete() && !hasWinner) {
        game.printBoard();
        int move;
        std::cout << "Player " << game.getCurrentPlayer() << ", enter your move: ";
        try {
            std::cin >> move;
            game.makeMove(move);
            hasWinner = game.checkWin();
            if (!hasWinner) {
                game.nextPlayer();
            }
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << '\n';
        }
    }

    game.printBoard();
    if (hasWinner) {
        std::cout << "Player " << game.getCurrentPlayer() << " wins!\n";
    } else {
        std::cout << "It's a draw.\n";
    }

    return 0;
}
