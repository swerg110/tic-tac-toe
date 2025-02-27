#include "game.hpp"
#include <algorithm>
#include <vector>

namespace tictactoe {

Game::Game() {
    for (auto &row : board) {
        std::fill(std::begin(row), std::end(row), OptionalPlayer::None);
    }
}

bool Game::make_move(int x, int y) {
    if (!check(y, x)) {
        return false;
    }

    board[y][x] = current_player;
    free_positions--;

    if (check_win(y, x) || check_draw()) {
        is_game_end = true;
    } else {
        switch_player();
    }

    return true;
}

bool Game::is_end() const {
    return is_game_end;
}

void Game::switch_player() {
    current_player = current_player == OptionalPlayer::O ? OptionalPlayer::X
                                                         : OptionalPlayer::O;
}

bool Game::check(int x, int y) const {
    return x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE &&
           board[x][y] == OptionalPlayer::None;
}

OptionalPlayer Game::who_won() const {
    return current_player;
}

OptionalPlayer Game::get_cell(int x, int y) const {
    return board[x][y];
}

OptionalPlayer Game::get_current_player() const {
    return current_player;
}

bool Game::check_win(int row, int column) const {
    return check_vertical(row, column) || check_horizontal(row, column) ||
           check_diag1(row, column) || check_diag2(row, column);
}

bool Game::check_draw() const {
    return free_positions == 0;
}

bool Game::check_horizontal(int row, int column) const {
    int horizontal_counter = 1;
    for (int i = column + 1; i < BOARD_SIZE && board[row][i] == current_player;
         i++) {
        horizontal_counter++;
    }
    for (int i = column - 1; i > -1 && board[row][i] == current_player; i--) {
        horizontal_counter++;
    }

    return horizontal_counter >= WIN_SEQUENCE_LENGTH;
}

bool Game::check_vertical(int row, int column) const {
    int vertical_counter = 1;

    for (int i = row + 1; i < BOARD_SIZE && board[i][column] == current_player;
         i++) {
        vertical_counter++;
    }
    for (int i = row - 1; i > -1 && board[i][column] == current_player; i--) {
        vertical_counter++;
    }

    return vertical_counter >= WIN_SEQUENCE_LENGTH;
}

bool Game::check_diag1(int row, int column) const {
    int diagonal_counter_1 = 1;
    for (int i = 1; i < WIN_SEQUENCE_LENGTH; i++) {
        if (row - i >= 0 && column + i < BOARD_SIZE &&
            board[row - i][column + i] == current_player) {
            diagonal_counter_1++;
        } else {
            break;
        }
    }
    for (int i = 1; i < WIN_SEQUENCE_LENGTH; i++) {
        if (row + i < BOARD_SIZE && column - i >= 0 &&
            board[row + i][column - i] == current_player) {
            diagonal_counter_1++;
        } else {
            break;
        }
    }

    return diagonal_counter_1 >= WIN_SEQUENCE_LENGTH;
}

bool Game::check_diag2(int row, int column) const {
    int diagonal_counter_2 = 1;

    for (int i = 1; i < WIN_SEQUENCE_LENGTH; i++) {
        if (row - i >= 0 && column - i >= 0 &&
            board[row - i][column - i] == current_player) {
            diagonal_counter_2++;
        } else {
            break;
        }
    }

    for (int i = 1; i < WIN_SEQUENCE_LENGTH; i++) {
        if (row + i < BOARD_SIZE && column + i < BOARD_SIZE &&
            board[row + i][column + i] == current_player) {
            diagonal_counter_2++;
        } else {
            break;
        }
    }

    return diagonal_counter_2 >= WIN_SEQUENCE_LENGTH;
}

}  // namespace tictactoe