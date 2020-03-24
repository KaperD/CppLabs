#include "Board.h"
#include <algorithm>

static BoardState getWinner(Player p) {
    if (p == Player::X) {
        return BoardState::Xwin;
    }
    return BoardState::Owin;
}


Board::Board(int height ,int width, int quantity_to_win) : height_(height), width_(width), quantity_to_win_(quantity_to_win) {
    board_.resize(height_, std::vector<Player>(width_, Player::Empty));
}


bool Board::canMove(int x, int y, Player player) {
    return (x >= 0 && x < width_
         && y >= 0 && y < height_
         && board_[y][x] == Player::Empty
         && cur_player_ == player);
}


void Board::move(int x, int y, Player player) {
    ++quantity_of_filled_;
    last_turn_x_ = x;
    last_turn_y_ = y;
    board_[y][x] = player;
    if (cur_player_ == Player::X) {
        cur_player_ = Player::O;
    } else {
        cur_player_ = Player::X;
    }
}

bool Board::checkDirection(int x, int y, int x_change, int y_change) const {
    int sequence = 0;
    if (board_[y][x] != Player::Empty) {
        sequence = 1;
    }
    Player previous = board_[y][x];
    x += x_change;
    y += y_change;
    while (x >= 0 && x < width_ && y >= 0 && y < height_) {
        if (board_[y][x] == Player::Empty) {
            sequence = 0;  
        } else if (board_[y][x] == previous) {
            ++sequence;
        } else {
            sequence = 1;
        }
        if (sequence == quantity_to_win_) {
            return true;
        }
        previous = board_[y][x];
        x += x_change;
        y += y_change;
    }
    return false;
}

BoardState Board::getState() const {
    //vertical and horisontal
    if (checkDirection(last_turn_x_, 0, 0, +1) ||
        checkDirection(0, last_turn_y_, +1, 0) ) {
            return getWinner(board_[last_turn_y_][last_turn_x_]);
    }
    //diagonal right
    int right_x = last_turn_x_ + std::min(width_ - 1 - last_turn_x_, last_turn_y_);  
    int right_y = last_turn_y_ - std::min(width_ - 1 - last_turn_x_, last_turn_y_);  
    if (checkDirection(right_x, right_y, -1, +1)) {
        return getWinner(board_[last_turn_y_][last_turn_x_]);
    }
    //diagonal left
    int left_x = last_turn_x_ - std::min(last_turn_x_, last_turn_y_);
    int left_y = last_turn_y_ - std::min(last_turn_x_, last_turn_y_);
    if (checkDirection(left_x, left_y, +1, +1)) {
        return getWinner(board_[last_turn_y_][last_turn_x_]);
    }
    if (quantity_of_filled_ == width_ * height_) {
        return BoardState::Draw;
    }
    return BoardState::IsRun;
}


Player Board::getCurrentPlayer() const {
    return cur_player_;
}


const std::vector<std::vector<Player>>& Board::getBoard() const {
    return board_;
}


bool Board::isInBoard(int x, int y) const {
    return (x >= 0 && x < width_ && y >= 0 && y < height_);
}