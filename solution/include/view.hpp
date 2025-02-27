#ifndef VIEW_HHP_
#define VIEW_HHP_
#include <boost/config.hpp>
#include "game.hpp"
#include "iostream"
#include "memory"

namespace tictactoe {

// NOLINTNEXTLINE
class BOOST_SYMBOL_VISIBLE View {
public:
    virtual void show_board() = 0;
    virtual void request_move() = 0;
    virtual void set_game(Game *game) = 0;
    virtual std::pair<int, int> parse_move(const std::string &input) = 0;
    virtual ~View() = default;
};
}  // namespace tictactoe

#endif