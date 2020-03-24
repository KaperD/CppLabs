#pragma once
#include <Board.h>

enum class GameMode {
    normal,
    silent,
};

struct Turn {
    int x;
    int y;
    bool operator == (Turn other) const {
        return (x == other.x) && (y == other.y);
    }
};

class BoardView {
public:
    BoardView(Board& board) : board_(board) {}
    virtual ~BoardView() = default;

    virtual void printBoard() const = 0;
    virtual Turn getTurn() = 0;
    virtual void printWinner(BoardState p) const = 0;

protected:
    Board& board_;
};

class StdioBoardView : public BoardView {
public:
    StdioBoardView(Board &board, GameMode mode);
    ~StdioBoardView() = default;

    
    void printBoard() const override;
    Turn getTurn() override;
    void printWinner(BoardState p) const override;
private:
    bool wantprint_ = true;
};

class NcursesBoardView : public BoardView {
public:
    NcursesBoardView(Board &board);
    ~NcursesBoardView();

    void printBoard() const override;
    Turn getTurn() override;
    void printWinner(BoardState p) const override;

    void PrintPlayer(Player player, int mode) const;

private:
    int current_x_ = 0;
    int current_y_ = 0;
};