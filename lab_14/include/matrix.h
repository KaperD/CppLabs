#pragma once
#include <string>
#include <vector>

class MatrixException : public std::exception {
public:
    MatrixException(std::string reason) : reason_(reason) {}
    const char* what() const noexcept override;

private:
    std::string reason_;
};

class Matrix {
public:
    void loadMatrixFromFile(std::string fileName);
    void printMatrix() const noexcept;
    void printElement(int row, int col) const;
    void addMatrix(const Matrix& other);
    void mulMatrix(const Matrix& other);

private:
    std::vector<std::vector<int>> matrix_;
};