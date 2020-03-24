#pragma once
#include <vector>

enum class Player {
    X,
    O,
    Empty
};

enum class BoardState {
    Xwin,
    Owin,
    Draw,
    IsRun,
};

class Board {
public:      
    Board(int height ,int width, int quantity_to_win);

    /** Проверить ход на корректность, если бы он был следующим. */
    bool canMove(int x, int y, Player player);

    /** Сделать ход. UB, если он некорректен. */
    void move(int x, int y, Player player);

    /** Состояние игры: игра идёт, игра кончилась с одним из результатов: ничья, победа одной из сторон. */
    BoardState getState() const;

    Player getCurrentPlayer() const;  

    bool checkDirection(int x, int y, int x_change, int y_change) const;

    const std::vector<std::vector<Player>>& getBoard() const;

    bool isInBoard(int x, int y) const;

private:
    std::vector<std::vector<Player>> board_;
    int height_ = 0;
    int width_ = 0;
    int quantity_to_win_ = 0;
    Player cur_player_ = Player::O;
    int quantity_of_filled_ = 0;
    int last_turn_x_ = 0;
    int last_turn_y_ = 0;
};