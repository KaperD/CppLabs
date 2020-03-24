#include "test.h"
#include "Board.h"
#include "GameController.h"

class BoardTest : public Test {
private:
    void testMove() {
        Board b(10, 10, 5);
        b.move(0, 0, Player::O);
        b.move(0, 1, Player::X);
        b.move(1, 0, Player::O);
        b.move(1, 1, Player::X);
        b.move(2, 0, Player::O);
        b.move(2, 1, Player::X);
        b.move(3, 0, Player::O);
        b.move(3, 1, Player::X);
        b.move(9, 9, Player::O);
        b.move(9, 0, Player::X);
        std::vector<std::vector<Player>> tBoard = 
        {
        {Player::O,     Player::O,     Player::O,     Player::O,     Player::Empty, Player::Empty, Player::Empty, Player::Empty, Player::Empty, Player::X},
        {Player::X,     Player::X,     Player::X,     Player::X,     Player::Empty, Player::Empty, Player::Empty, Player::Empty, Player::Empty, Player::Empty},
        {Player::Empty, Player::Empty, Player::Empty, Player::Empty, Player::Empty, Player::Empty, Player::Empty, Player::Empty, Player::Empty, Player::Empty},
        {Player::Empty, Player::Empty, Player::Empty, Player::Empty, Player::Empty, Player::Empty, Player::Empty, Player::Empty, Player::Empty, Player::Empty},
        {Player::Empty, Player::Empty, Player::Empty, Player::Empty, Player::Empty, Player::Empty, Player::Empty, Player::Empty, Player::Empty, Player::Empty},
        {Player::Empty, Player::Empty, Player::Empty, Player::Empty, Player::Empty, Player::Empty, Player::Empty, Player::Empty, Player::Empty, Player::Empty},
        {Player::Empty, Player::Empty, Player::Empty, Player::Empty, Player::Empty, Player::Empty, Player::Empty, Player::Empty, Player::Empty, Player::Empty},
        {Player::Empty, Player::Empty, Player::Empty, Player::Empty, Player::Empty, Player::Empty, Player::Empty, Player::Empty, Player::Empty, Player::Empty},
        {Player::Empty, Player::Empty, Player::Empty, Player::Empty, Player::Empty, Player::Empty, Player::Empty, Player::Empty, Player::Empty, Player::Empty},
        {Player::Empty, Player::Empty, Player::Empty, Player::Empty, Player::Empty, Player::Empty, Player::Empty, Player::Empty, Player::Empty, Player::O},
        };

        DO_CHECK(b.getBoard() == tBoard);
    }


    void testOWinsHorisontal() {
        Board b(10, 10, 5);
        b.move(0, 0, Player::O);
        b.move(0, 1, Player::X);
        b.move(1, 0, Player::O);
        b.move(1, 1, Player::X);
        b.move(2, 0, Player::O);
        b.move(2, 1, Player::X);
        b.move(3, 0, Player::O);
        b.move(3, 1, Player::X);
        b.move(4, 0, Player::O);
        DO_CHECK(b.getState() == BoardState::Owin);
    }

    void testOWinsVertical() {
        Board b(10, 10, 5);
        b.move(0, 0, Player::O);
        b.move(9, 9, Player::X);
        b.move(0, 9, Player::O);
        b.move(9, 0, Player::X);
        b.move(3, 0, Player::O);
        b.move(1, 1, Player::X);
        b.move(3, 1, Player::O);
        b.move(5, 2, Player::X);
        b.move(3, 2, Player::O);
        b.move(3, 5, Player::X);
        b.move(3, 4, Player::O);
        b.move(5, 3, Player::X);
        b.move(3, 3, Player::O);
        DO_CHECK(b.getState() == BoardState::Owin);
    }

    void testOWinsDiagonalLeft() {
        Board b(10, 10, 5);
        b.move(9, 9, Player::O);
        b.move(0, 1, Player::X);
        b.move(8, 8, Player::O);
        b.move(1, 1, Player::X);
        b.move(7, 7, Player::O);
        b.move(2, 1, Player::X);
        b.move(6, 6, Player::O);
        b.move(3, 1, Player::X);
        b.move(5, 5, Player::O);
        DO_CHECK(b.getState() == BoardState::Owin);
    }

    void testOWinsDiagonalRight() {
        Board b(10, 10, 5);
        b.move(0, 4, Player::O);
        b.move(0, 3, Player::X);
        b.move(1, 3, Player::O);
        b.move(1, 2, Player::X);
        b.move(2, 2, Player::O);
        b.move(2, 1, Player::X);
        b.move(3, 1, Player::O);
        b.move(3, 0, Player::X);
        b.move(4, 0, Player::O);
        DO_CHECK(b.getState() == BoardState::Owin);
    }
    

    void testXWinsHorisontal() {
        Board b(10, 10, 5);
        b.move(0, 0, Player::O);
        b.move(9, 2, Player::X);
        b.move(5, 5, Player::O);
        b.move(9, 3, Player::X);
        b.move(2, 2, Player::O);
        b.move(9, 4, Player::X);
        b.move(3, 1, Player::O);
        b.move(9, 5, Player::X);
        b.move(4, 0, Player::O);
        b.move(9, 6, Player::X);
        DO_CHECK(b.getState() == BoardState::Xwin);
    }

    void testXWinsVertical() {
        Board b(10, 10, 5);
        b.move(0, 0, Player::O);
        b.move(4, 2, Player::X);
        b.move(5, 5, Player::O);
        b.move(4, 3, Player::X);
        b.move(9, 9, Player::O);
        b.move(4, 4, Player::X);
        b.move(3, 6, Player::O);
        b.move(4, 5, Player::X);
        b.move(5, 8, Player::O);
        b.move(4, 6, Player::X);
        DO_CHECK(b.getState() == BoardState::Xwin);
    }

    void testXWinsDiagonalLeft() {
        Board b(10, 10, 5);
        b.move(0, 5, Player::O);
        b.move(4, 2, Player::X);
        b.move(1, 6, Player::O);
        b.move(4, 3, Player::X);
        b.move(2, 7, Player::O);
        b.move(4, 4, Player::X);
        b.move(3, 8, Player::O);
        b.move(4, 5, Player::X);
        b.move(4, 0, Player::O);
        b.move(4, 6, Player::X);
        DO_CHECK(b.getState() == BoardState::Xwin);
    }

    void testXWinsDiagonalRight() {
        Board b(10, 10, 5);
        b.move(0, 5, Player::O);
        b.move(9, 0, Player::X);
        b.move(1, 6, Player::O);
        b.move(8, 1, Player::X);
        b.move(2, 7, Player::O);
        b.move(7, 2, Player::X);
        b.move(3, 0, Player::O);
        b.move(6, 3, Player::X);
        b.move(4, 0, Player::O);
        b.move(5, 4, Player::X);
        DO_CHECK(b.getState() == BoardState::Xwin);
    }


    void testStateIsRun() {
        Board b(10, 10, 5);
        int cnt = 0;
        if (b.getState() == BoardState::IsRun) ++cnt;
        b.move(0, 5, Player::O);
        if (b.getState() == BoardState::IsRun) ++cnt;
        b.move(9, 0, Player::X);
        if (b.getState() == BoardState::IsRun) ++cnt;
        b.move(1, 6, Player::O);
        if (b.getState() == BoardState::IsRun) ++cnt;
        b.move(8, 1, Player::X);
        if (b.getState() == BoardState::IsRun) ++cnt;
        b.move(2, 7, Player::O);
        if (b.getState() == BoardState::IsRun) ++cnt;
        b.move(7, 2, Player::X);
        if (b.getState() == BoardState::IsRun) ++cnt;
        b.move(3, 0, Player::O);
        if (b.getState() == BoardState::IsRun) ++cnt;
        b.move(6, 3, Player::X);
        if (b.getState() == BoardState::IsRun) ++cnt;
        b.move(4, 0, Player::O);
        if (b.getState() == BoardState::IsRun) ++cnt;
        b.move(5, 9, Player::X);
        if (b.getState() == BoardState::IsRun) ++cnt;
        DO_CHECK(cnt == 11);
    }

    void testSwichPlayer() {
        std::vector<Player> v;
        std::vector<Player> needel = {Player::O, Player::X, Player::O, Player::X};
        Board b(10, 10, 5);
        v.push_back(b.getCurrentPlayer());
        b.move(0, 5, Player::O);
        v.push_back(b.getCurrentPlayer());
        b.move(9, 0, Player::X);
        v.push_back(b.getCurrentPlayer());
        b.move(9, 1, Player::O);
        v.push_back(b.getCurrentPlayer());
        DO_CHECK(v == needel);
    }
    
    void testBadTurnSamePosition() {
        Board b(10, 10, 5);
        b.move(0, 5, Player::O);
        b.move(9, 0, Player::X);
        DO_CHECK(b.canMove(0, 5, Player::O) == false);
    }

    void testBadTurnOutOfBoard() {
        Board b(10, 10, 5);
        bool t = false;
        t |= b.canMove(-4, 5, Player::O);
        t |= b.canMove(-1, -8, Player::X);
        t |= b.canMove(2424, 10, Player::O);
        t |= b.canMove(0, 10, Player::X);
        t |= b.canMove(5, -3, Player::Empty);
        DO_CHECK(t == false);
    }

    void testBadTurnMultiple() {
        Board b(10, 10, 5);
        b.move(0, 5, Player::O);
        bool t = false;
        t |= b.canMove(0, 5, Player::X);
        t |= b.canMove(0, 5, Player::X);
        t |= b.canMove(0, 5, Player::X);
        t |= b.canMove(0, 5, Player::O);
        DO_CHECK(t == false);
    }

    static Player changePlayer(Player p) {
        if (p == Player::X) {
            return Player::O;
        }
        return Player::X;
    }

    void testDraw() {
        Board b(10, 10, 5);
        Player firstP;
        Player secondP;
        for (int k = 0; k < 10; k += 2) {
            firstP = Player::O;
            secondP = Player::X;
            for (int i = 0; i < 10; ++i) {
                if (k == 8 && i == 9) break;
                b.move(i, k, firstP);
                b.move(i, k + 1, secondP);
                if (i % 2 == 1) {
                    firstP = changePlayer(firstP);
                    secondP = changePlayer(secondP);
                }
            }
        }
        b.move(9, 8, firstP);
        DO_CHECK(b.getState() == BoardState::IsRun);
        b.move(9, 9, secondP);
        DO_CHECK(b.getState() == BoardState::Draw);
    }

    
public:
    void runAllTests() override {
        testMove();
        testOWinsHorisontal();
        testOWinsVertical();
        testOWinsDiagonalLeft();
        testOWinsDiagonalRight();
        testXWinsHorisontal();
        testXWinsVertical();
        testXWinsDiagonalLeft();
        testXWinsDiagonalRight();
        testStateIsRun();
        testSwichPlayer();
        testBadTurnSamePosition();
        testBadTurnOutOfBoard();
        testBadTurnMultiple();
        testDraw();
    }
};

int main() {
    BoardTest bt;
    bt.runAllTests();
    if (!Test::showFinalResult()) {
        return 1;
    }

    return 0;
}
