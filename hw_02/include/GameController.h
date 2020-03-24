#pragma once
#include "BoardView.h"
#include <memory>

enum class ViewMode {
    stdio,
    curses,
};

class GameController {
public:
    GameController(Board& board, GameMode game_mode, ViewMode view_mode);
    ~GameController() = default;

    void runGame();


private:
    Board& board_;
    std::shared_ptr<BoardView> view_;
    bool wantprint_;
};