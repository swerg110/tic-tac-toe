// TODO
#include "game.hpp"
#include "iostream"
#include "sstream"
#include "view.hpp"

namespace tictactoe {
class ViewCompact : public View {
public:
    // NOLINTNEXTLINE
    std::pair<int, int> parse_move(const std::string &input) final {
        std::pair<int, int> turn = {-2, -2};
        std::stringstream ss(input);

        int column, row;  // NOLINT
        // NOLINTNEXTLINE
        if (ss >> row >> column) {
            ss >> std::ws;
            if (ss.eof()) {
                turn.first = row;
                turn.second = column;
            }
        }

        return turn;
    }

    void set_game(Game *game) final {
        _game = game;
    }

    // NOLINTNEXTLINE
    void show_board() override {
        for (int i = 0; i < BOARD_SIZE; ++i) {
            for (int j = 0; j < BOARD_SIZE; ++j) {
                switch (_game->get_cell(i, j)) {
                    case OptionalPlayer::X:
                        std::cout << "X";
                        break;
                    case OptionalPlayer::O:
#ifdef VIEW_COMPACT_USE_ZERO
                        std::cout << "0";
#else
                        std::cout << "O";
#endif
                        break;
                    case OptionalPlayer::None:
                        std::cout << ".";
                        break;
                }
            }
            std::cout << '\n';
        }
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
};

extern "C" BOOST_SYMBOL_EXPORT const ViewCompact plugin;
const ViewCompact plugin;
}  // namespace tictactoe