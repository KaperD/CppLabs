#include <Board.h>
#include <BoardView.h>
#include <GameController.h>
#include <iostream>
#include <string>
#include "test.h"

int main(int argc, char* argv[]) {  
    GameMode game_mode = GameMode::normal;  
    ViewMode view_mode = ViewMode::stdio;
    if (argc == 2) {
        if (std::string(argv[1]) == "silent") {
            game_mode = GameMode::silent;
        } else if (std::string(argv[1]) == "curses") {
            view_mode = ViewMode::curses;
        }
    }
    Board board(10, 10, 5);
    GameController game(board, game_mode, view_mode);
    game.runGame();

    return 0;
}