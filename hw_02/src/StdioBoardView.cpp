#include <BoardView.h>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>


static std::ostream& operator<<(std::ostream& os, const Player p);


StdioBoardView::StdioBoardView(Board &board, GameMode mode) : BoardView(board) {
    if (mode == GameMode::silent) {
        wantprint_ = false;
    }
}


void StdioBoardView::printBoard() const {
    std::cout << '\n';
    auto board = board_.getBoard();
    for (auto row : board) {
        for (auto point : row) {
            std::cout << point;
        }
        std::cout << '\n';
    }
}


Turn StdioBoardView::getTurn() {
    if (wantprint_) { 
        printBoard();
    }
    int x, y;
    while (true) {
        std::cout << board_.getCurrentPlayer() << " move: ";
        std::string line;
        std::getline(std::cin, line);
        std::istringstream str(line);
        std::vector<std::string> tokens;
        std::copy(std::istream_iterator<std::string>(str),
                  std::istream_iterator<std::string>{},
                  std::back_inserter(tokens));

        if (tokens.size() == 2) {
            std::stringstream numbers;
            numbers << tokens[0] << ' ' << tokens[1];
            numbers >> y >> x;
            if ((numbers.eof() && board_.canMove(x, y, board_.getCurrentPlayer())) || (x == -1 && y == -1)) {
                return {x, y};
            }
        }
        std::cout << "Bad move!\n";
    }
}


void StdioBoardView::printWinner(BoardState p) const {
    printBoard();
    if (p == BoardState::Draw) {
        std::cout << "Draw.\n";
    } else if (p == BoardState::Xwin) {
        std::cout << "X wins!\n";
    } else if (p == BoardState::Owin) {
        std::cout << "O wins!\n";
    }
}


static std::ostream& operator<<(std::ostream& os, const Player p) {
    if (p == Player::X) {
        os << 'X';
    } else if (p == Player::O) {
        os << 'O';
    } else if (p == Player::Empty) {
        os << '.';
    }   
    return os;
}