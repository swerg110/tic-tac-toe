#ifndef GAME_HPP_
#define GAME_HPP_

#include <array>

namespace tictactoe {

enum class OptionalPlayer { X, O, None };

constexpr int BOARD_SIZE = 10;
constexpr int WIN_SEQUENCE_LENGTH = 5;

struct Game {
private:
    std::array<std::array<OptionalPlayer, BOARD_SIZE>, BOARD_SIZE> board{};
    OptionalPlayer current_player = OptionalPlayer::O;
    bool is_game_end = false;
    int free_positions = BOARD_SIZE * BOARD_SIZE;
    [[nodiscard]] bool check_horizontal(int row, int column) const;
    [[nodiscard]] bool check_vertical(int row, int column) const;
    [[nodiscard]] bool check_diag1(int row, int column) const;
    [[nodiscard]] bool check_diag2(int row, int column) const;

    void switch_player();

public:
    Game();

    bool make_move(int x, int y);
    [[nodiscard]] bool is_end() const;
    [[nodiscard]] OptionalPlayer get_cell(int x, int y) const;
    [[nodiscard]] OptionalPlayer who_won() const;
    [[nodiscard]] OptionalPlayer get_current_player() const;

    [[nodiscard]] bool check(int x, int y) const;
    [[nodiscard]] bool check_win(int row, int column) const;
    [[nodiscard]] bool check_draw() const;
};
}  // namespace tictactoe

#endif