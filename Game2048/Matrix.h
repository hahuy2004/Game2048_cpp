#pragma once

#include <iostream>
#include <iomanip>
#include <random>

using std::cin, std::cout, std::endl, std::setw, std::setfill;

class Matrix {
private:
    int _rows;
    int _columns;
    int _score;
    int **_matrix;
public:
    // constructor
    Matrix() = default;
    Matrix(const int &n, const int &m) : _rows(n), _columns(m), _score(0) {
        _matrix = new int*[_rows];
        for (int i = 0; i < _rows; i++) {
            _matrix[i] = new int[_columns];
            for (int j = 0; j < _columns; j++) {
                _matrix[i][j] = -1;
            }
        }
    }
    Matrix(const Matrix& other) : _rows(other.rows()), _columns(other.columns()), _score(other.score()) {
         _matrix = new int*[_rows];
        for (int i = 0; i < _rows; i++) {
            _matrix[i] = new int[_columns];
            for (int j = 0; j < _columns; j++) {
                _matrix[i][j] = other.at(i, j);
            }
        }
    }
    Matrix(const int& rows, const int& columns, const int& score, int** matrix) : 
        _rows(rows), _columns(columns), _score(score), _matrix(matrix) { }
public:
    // operation
    int score() const;
    void addRandom();
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();
    bool stuck();
    bool full();
    int columns() const;
    int rows() const;
    int at(const int&, const int&) const;
    int maxNumber();
    void freeMemory();
};