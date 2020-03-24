#include <fstream>
#include <iostream>
#include <utility>

#include "matrix.h"

const char* MatrixException::what() const noexcept {
    return reason_.c_str();
}

void Matrix::loadMatrixFromFile(std::string fileName) {
    try {
        std::ifstream file(fileName);
        if (!file.is_open()) {
            throw MatrixException("LOAD: unable to open file.");
        }
        int rows = 0;
        int cols = 0;
        file >> rows;
        file >> cols;
        if (!file.good()) {
            throw MatrixException("LOAD: invalid file format.");
        }
        std::vector<std::vector<int>> copy(rows, std::vector<int>(cols));
        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                int x = 0;
                file >> x;
                if (file.eof()) {
                    throw MatrixException("LOAD: invalid file format.");
                }
                copy[row][col] = x;
            }
        }
        std::swap(matrix_, copy);
    } catch (const std::bad_alloc& ex) {
        throw MatrixException("Unable to allocate memory.");
    } catch (const MatrixException& ex) {
        throw ex;
    }
}

void Matrix::printMatrix() const noexcept {
    for (auto row : matrix_) {
        for (int elem : row) {
            std::cout << elem << ' ';
        }
        std::cout << '\n';
    }
}

void Matrix::printElement(int row, int col) const { 
    try {
        int elem = matrix_.at(row).at(col);
        std::cout << elem << '\n';
    } catch (const std::out_of_range& ex) {
        throw MatrixException("ACCESS: bad index.");
    }
}

void Matrix::addMatrix(const Matrix& other) {
    int my_number_of_rows = matrix_.size();
    int my_number_of_cols = 0;
    if (my_number_of_rows > 0) {
        my_number_of_cols = matrix_[0].size();
    }
    int other_number_of_rows = other.matrix_.size();
    int other_number_of_cols = 0;
    if (other_number_of_rows > 0) {
        other_number_of_cols = other.matrix_[0].size();
    }
    if (my_number_of_rows == other_number_of_rows && my_number_of_cols == other_number_of_cols) {
        for (int row = 0; row < my_number_of_rows; ++row) {
            for (int col = 0; col < my_number_of_cols; ++col) {
                matrix_[row][col] += other.matrix_[row][col];
            }
        }
    } else {
        throw MatrixException("ADD: dimensions do not match.");
    }
}

void Matrix::mulMatrix(const Matrix& other) {
    int my_number_of_rows = matrix_.size();
    int my_number_of_cols = 0;
    if (my_number_of_rows > 0) {
        my_number_of_cols = matrix_[0].size();
    }
    int other_number_of_rows = other.matrix_.size();
    int other_number_of_cols = 0;
    if (other_number_of_rows > 0) {
        other_number_of_cols = other.matrix_[0].size();
    }
    if (my_number_of_cols == other_number_of_rows) {
        try {
            std::vector<std::vector<int>> copy(my_number_of_rows, std::vector<int>(other_number_of_cols));
            for (int row = 0; row < my_number_of_rows; ++row) {
                for (int col = 0; col < other_number_of_cols; ++col) {
                    int elem = 0;
                    for (int k = 0; k < my_number_of_cols; ++k) {
                        elem += matrix_[row][k] * other.matrix_[k][col];
                    }
                    copy[row][col] = elem;
                }
            }
            std::swap(matrix_, copy);
        } catch (const std::bad_alloc& ex) {
            throw MatrixException("Unable to allocate memory.");
        }
    } else {
        throw MatrixException("MUL: #arg1.columns != #arg2.rows.");
    }
}