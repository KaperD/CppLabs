#include "BoardView.h"
#include <ncurses.h>

#define X_COLOR 1
#define O_COLOR 2


void NcursesBoardView::PrintPlayer(Player player, int mode) const {
    if (player == Player::X) {
        attron(COLOR_PAIR(X_COLOR));
        addch('X' | mode);
        attroff(COLOR_PAIR(X_COLOR));
    } else if (player == Player::O) {
        attron(COLOR_PAIR(O_COLOR));
        addch('O' | mode);
        attroff(COLOR_PAIR(O_COLOR));
    } else {
        addch('.' | mode);
    }
}


NcursesBoardView::NcursesBoardView(Board &board) : BoardView(board) {
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, true); 
    start_color();
    init_pair(X_COLOR, COLOR_RED, COLOR_BLACK);
    init_pair(O_COLOR, COLOR_GREEN, COLOR_BLACK);
}


NcursesBoardView::~NcursesBoardView() {
    endwin();
}


void NcursesBoardView::printBoard() const {
    clear();
    auto board = board_.getBoard();
    for (size_t row = 0; row < board.size(); ++row) {
        for (size_t column = 0; column < board[row].size(); ++column) {
            int mode = A_NORMAL;
            if ((int)column == current_x_ && (int)row == current_y_) {
                mode = A_STANDOUT;
            }
            PrintPlayer(board[row][column], mode);
            if (column + 1 != board[row].size()) {
                addch(' ');
            }
        }
        addch('\n');
    }
    addch('\n');
    printw("Current player: ");
    PrintPlayer(board_.getCurrentPlayer(), A_NORMAL);
    refresh(); 
}


Turn NcursesBoardView::getTurn() {
    while(true) {
        printBoard();
        auto action = getch();
        if (action == KEY_UP) {
            if (board_.isInBoard(current_x_, current_y_ - 1)) {
                --current_y_;
            }
        } else if (action == KEY_DOWN) {
            if (board_.isInBoard(current_x_, current_y_ + 1)) {
                ++current_y_;
            }
        } else if (action == KEY_LEFT) {
            if (board_.isInBoard(current_x_ - 1, current_y_)) {
                --current_x_;
            }
        } else if (action == KEY_RIGHT) {
            if (board_.isInBoard(current_x_ + 1, current_y_)) {
                ++current_x_;
            }
        } else if (action == ' ') {
            if (board_.canMove(current_x_, current_y_, board_.getCurrentPlayer())) {
                return {current_x_, current_y_};
            }
        } else if (action == 'x') {
            return {-1, -1};
        }
    }
}


void NcursesBoardView::printWinner(BoardState p) const {
    printBoard();
    addch('\n');
    if (p == BoardState::Owin) {
        printw("O wins!");
    } else if (p == BoardState::Xwin) {
        printw("X wins!");
    } else {
        printw("Draw.");
    }
    addch('\n');
    printw("Press any key to exit...");
    getch();
}