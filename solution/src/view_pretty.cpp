#include <sstream>
#include "game.hpp"
#include "iostream"
#include "view.hpp"

namespace tictactoe {
class ViewPretty : public View {
public:
    void set_game(Game *game) final {
        _game = game;
    }

    // NOLINTNEXTLINE
    std::pair<int, int> parse_move(const std::string &input) final {
        std::pair<int, int> turn = {-2, -2};
        std::stringstream ss(input);
        ss >> std::ws;

        std::string trim_input;
        ss >> trim_input;

        const char letter = trim_input[0];
        const char number = trim_input[1];

        // NOLINTNEXTLINE
        if (trim_input.size() == 2 && isalpha(letter) && isdigit(number)) {
            turn.second = (letter - 'a');
            turn.first = (BOARD_SIZE - 1) - (number - '0');
        }

        return turn;
    }

    void show_board() final {
        draw_border();
        for (int r = 0; r < BOARD_SIZE; r++) {
            draw_row(r);
        }
        draw_columns_info();
    }

    // NOLINTNEXTLINE
    void request_move() final {
        switch (_game->get_current_player()) {
            case OptionalPlayer::X:
                std::cout << "X move: ";
                break;
            case OptionalPlayer::O:
                std::cout << "O move: ";
                break;
            case OptionalPlayer::None:
                std::cout << "Ooops, this is bug(";
                break;
        }
    }

private:
    Game *_game{};

    static void draw_border() {
        std::cout << "  +";
        for (int i = 0; i < BOARD_SIZE; i++) {
            std::cout << "----+";
        }
        std::cout << '\n';
    }

    void draw_row(int row) const {
        std::cout << (BOARD_SIZE - 1) - row << " |";
        for (int col = 0; col < BOARD_SIZE; col++) {
            draw_upper_half(row, col);
            std::cout << "|";
        }
        std::cout << '\n';

        std::cout << "  |";
        for (int col = 0; col < BOARD_SIZE; col++) {
            draw_lower_half(row, col);
            std::cout << "|";
        }
        std::cout << '\n';

        draw_border();
    }

    // NOLINTNEXTLINE
    static void draw_columns_info() {
        std::cout << "  ";
        for (int i = 0; i < BOARD_SIZE; i++) {
            std::cout << "  " << static_cast<char>('a' + i) << "  ";
        }
        std::cout << " \n";
    }

    // NOLINTNEXTLINE
    void draw_upper_half(int row, int col) const {
        switch (_game->get_cell(row, col)) {
            case OptionalPlayer::X:
                std::cout << " \\/ ";
                break;
            case OptionalPlayer::O:
                std::cout << " @@ ";
                break;
            case OptionalPlayer::None:
                std::cout << "    ";
                break;
        }
    }

    // NOLINTNEXTLINE
    void draw_lower_half(int row, int col) const {
        switch (_game->get_cell(row, col)) {
            case OptionalPlayer::X:
                std::cout << " /\\ ";
                break;
            case OptionalPlayer::O:
                std::cout << " @@ ";
                break;
            case OptionalPlayer::None:
                std::cout << "    ";
                break;
        }
    }
};

extern "C" BOOST_SYMBOL_EXPORT const ViewPretty plugin;
const ViewPretty plugin;
}  // namespace tictactoe