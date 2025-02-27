#ifdef _MSC_VER
#include <crtdbg.h>
#endif

#include <boost/dll/import.hpp>
#include <boost/version.hpp>
#include "game.hpp"
#include "iostream"
#include "sstream"
#include "string"
#include "view.hpp"

#if BOOST_VERSION >= 107600
// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define boost_dll_import_symbol ::boost::dll::import_symbol

#else
// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define boost_dll_import_symbol ::boost::dll::import
#endif

int main([[maybe_unused]] int argc, const char *argv[]) {
#ifdef _MSC_VER
    _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE | _CRTDBG_MODE_DEBUG);
    _CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDERR);
    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE | _CRTDBG_MODE_DEBUG);
    _CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDERR);
#endif

    tictactoe::Game game;  // NOLINT
    const std::string view_option =
        argv[1];  // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    boost::shared_ptr<tictactoe::View> view;
    std::cout << '\n';

    auto load_view = [&](const std::string &view_option) {
        // NOLINTNEXTLINE
        const boost::dll::shared_library lib(
            view_option, boost::dll::load_mode::append_decorations
        );
        view = boost_dll_import_symbol<tictactoe::View>(lib, "plugin");
        view->set_game(&game);
        view->show_board();
    };

    load_view(view_option);

    std::pair<int, int> turn;
    std::string input;

    while (true) {
        view->request_move();
        std::getline(std::cin, input);

        if (input.empty()) {
            return 0;
        }

        if (input.starts_with("view-")) {
            load_view(input);
            continue;
        }

        turn = view->parse_move(input);
        if (turn.first == -1 && turn.second == -1) {
            return 0;
        }

        // check bad_move
        if (!game.make_move(turn.second, turn.first)) {
            std::cout << "Bad move!"
                      << "\n";
            continue;
        }

        if (game.is_end()) {
            break;
        }

        std::cout << '\n';
        view->show_board();
    }

    std::cout << '\n';
    view->show_board();
    switch (game.who_won()) {
        case tictactoe::OptionalPlayer::X:
            std::cout << "X wins!\n";
            break;
        case tictactoe::OptionalPlayer::O:
            std::cout << "O wins!\n";
            break;
        case tictactoe::OptionalPlayer::None:
            std::cout << "Draw.\n";
            break;
    }

    return 0;
}
