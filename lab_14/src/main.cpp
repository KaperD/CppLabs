#include <iostream>
#include <string>
#include <sstream>

#include "matrix.h"

int main() {
    std::string command;
    std::string action;
    std::vector<Matrix> regs(10);

    while (getline(std::cin, command)) {
        try {
            std::stringstream input(command);
            input >> action;
            if (action == "load") {
                char c = 0;
                int reg = 0;
                std::string filename;
                input >> c >> reg >> filename;
                regs.at(reg).loadMatrixFromFile(filename);
            } else if (action == "print") {
                char c = 0;
                int reg = 0;
                input >> c >> reg;
                regs.at(reg).printMatrix();
            } else if (action == "add") {
                char c = 0;
                int lhs = 0;
                int rhs = 0;
                input >> c >> lhs >> c >> rhs;
                regs.at(lhs).addMatrix(regs.at(rhs));
            } else if (action == "mul") {
                char c = 0;
                int lhs = 0;
                int rhs = 0;
                input >> c >> lhs >> c >> rhs;
                regs.at(lhs).mulMatrix(regs.at(rhs));
            } else if (action == "elem") {
                char c = 0;
                int reg = 0;
                int row, col;
                input >> c >> reg >> row >> col;
                regs.at(reg).printElement(row, col);
            } else if (action == "exit") {
                return 0;
            } else {
                std::cout << "Unknown command.\n";
            }
        } catch (const MatrixException& ex) {
            std::cout << ex.what() << '\n';
        } catch (std::exception& ex) {
            std::cout << ex.what() << '\n';
        } catch (...) {
            return 1;
        }
    }

    return 0;
}