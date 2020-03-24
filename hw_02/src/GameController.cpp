#include "GameController.h"
#include <utility>

static const Turn exit_turn = {-1, -1};

GameController::GameController(Board& board, GameMode game_mode, ViewMode view_mode) : board_(board) {
    if (game_mode == GameMode::silent) {
        wantprint_ = false;
    } else {
        wantprint_ = true;
    }

    if (view_mode == ViewMode::stdio) {
        view_ = std::make_shared<StdioBoardView>(board_, game_mode);
    } else {
        view_ = std::make_shared<NcursesBoardView>(board_);
    }
}
void GameController::runGame() {
    while (true) {
        auto turn = view_->getTurn();
        if (turn == exit_turn) break;
        board_.move(turn.x, turn.y, board_.getCurrentPlayer());
        auto state = board_.getState();
        if (state != BoardState::IsRun) {
            view_->printWinner(state);
            break;
        }
    }
}