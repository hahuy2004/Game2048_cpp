#include "Matrix.h"

void Matrix::addRandom() {
    if (full()) return;
    srand(time(NULL));

    int x, y;
    do {
        x = rand() % _rows;
        y = rand() % _columns;
    } while (_matrix[x][y] != -1);
    if (rand() % 100 > 60)
        _matrix[x][y] = 4;
    else
        _matrix[x][y] = 2;
}

void Matrix::moveUp() {
    for (int i = 0; i < _columns; i++) {
        int ceil = 0;
        for (int j = 1; j < _rows; j++) {
            if (-1 == _matrix[ceil][i]) { // if the top-most value is blank, move current value to top
                _matrix[ceil][i] = _matrix[j][i];
                _matrix[j][i] = - 1;
                continue;
            }
            if (-1 != _matrix[j][i] && _matrix[j][i] == _matrix[ceil][i]) {
                _matrix[ceil][i] += _matrix[j][i];
                _matrix[j][i] = -1;
                _score += _matrix[ceil][i];
                ceil++;
            }
            else if (-1 != _matrix[j][i] && _matrix[j][i] != _matrix[ceil][i]) {
                ceil++;
                if (ceil != j) {
                    _matrix[ceil][i] = _matrix[j][i];
                    _matrix[j][i] = - 1;
                }
            }
        }
    }
}

void Matrix::moveDown() {
    for (int i = _columns - 1; i >= 0; i--) {
        int floor = _rows - 1;
        for (int j = _rows - 2; j >= 0; j--) {
            if (-1 == _matrix[floor][i]) { // if the bottom value is blank, move current value to bottom
                _matrix[floor][i] = _matrix[j][i];
                _matrix[j][i] = - 1;
                continue;
            }
            if (-1 != _matrix[j][i] && _matrix[j][i] == _matrix[floor][i]) {
                _matrix[floor][i] += _matrix[j][i];
                _matrix[j][i] = -1;
                _score += _matrix[floor][i];
                floor--;
            }
            else if (-1 != _matrix[j][i] && _matrix[j][i] != _matrix[floor][i]) {
                floor--;
                if (floor != j) {
                    _matrix[floor][i] = _matrix[j][i];
                    _matrix[j][i] = - 1;
                }
            }
        }
    }
}

void Matrix::moveLeft() {
    for (int i = 0; i < _rows; i++) {
        int leftSide = 0;
        for (int j = 1; j < _columns; j++) {
            if (-1 == _matrix[i][leftSide]) { // if the left-most value is blank, move current value to left
                _matrix[i][leftSide] = _matrix[i][j];
                _matrix[i][j] = - 1;
                continue;
            }
            if (-1 != _matrix[i][j] && _matrix[i][j] == _matrix[i][leftSide]) {
                _matrix[i][leftSide] += _matrix[i][j];
                _matrix[i][j] = -1;
                _score += _matrix[i][leftSide];
                leftSide++;
            }
            else if (-1 != _matrix[i][j] && _matrix[i][j] != _matrix[i][leftSide]) {
                leftSide++;
                if (leftSide != j) {
                    _matrix[i][leftSide] = _matrix[i][j];
                    _matrix[i][j] = - 1;
                }
            }
        }
    }
}

void Matrix::moveRight() {
    for (int i = _rows - 1; i >= 0; i--) {
        int rightSide = _columns - 1;
        for (int j = _columns - 2; j >= 0; j--) {
            if (-1 == _matrix[i][rightSide]) { // if the right-most value is blank, move current value to right
                _matrix[i][rightSide] = _matrix[i][j];
                _matrix[i][j] = - 1;
                continue;
            }
            if (-1 != _matrix[i][j] && _matrix[i][j] == _matrix[i][rightSide]) {
                _matrix[i][rightSide] += _matrix[i][j];
                _matrix[i][j] = -1;
                _score += _matrix[i][rightSide];
                rightSide--;
            }
            else if (-1 != _matrix[i][j] && _matrix[i][j] != _matrix[i][rightSide]) {
                rightSide--;
                if (rightSide != j) {
                    _matrix[i][rightSide] = _matrix[i][j];
                    _matrix[i][j] = - 1;
                }
            }
        }
    }
}

bool Matrix::stuck() { // check if the game is over or not, if the game is not over return false
    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _columns; j++) {
            // if there is a blank cell, return false
            if (_matrix[i][j] == -1) return false;
            // if selected cell is equal to any adjacent cells, return false
            if (i > 0 && _matrix[i][j] == _matrix[i - 1][j]) return false;
            if (i < _rows - 1 && _matrix[i][j] == _matrix[i + 1][j]) return false;
            if (j > 0 && _matrix[i][j] == _matrix[i][j - 1]) return false;
            if (j < _columns - 1 && _matrix[i][j] == _matrix[i][j + 1]) return false;
        }
    }
    // if no conditions is met, end the game
    return true;
}

bool Matrix::full() {
    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _columns; j++) {
            if (-1 == _matrix[i][j]) return false;
        }
    }
    return true;
}

int Matrix::score() const {
    return _score;
}

int Matrix::columns() const {
    return _columns;
}

int Matrix::rows() const {
    return _rows;
}

int Matrix::at(const int& i, const int& j) const {
    return _matrix[i][j];
}

int Matrix::maxNumber() {
    int result = -1;
    for (int i = 0; i < _rows; i++) {
        for (int j = 0; j < _columns; j++) {
            if (result < _matrix[i][j]) {
                result = _matrix[i][j];
            }
        }
    }

    return result;
}

void Matrix::freeMemory() {
    for (int i = 0; i < _rows; i++) {
        delete _matrix[i];
        _matrix[i] = nullptr;
    }
    delete _matrix;
    _matrix = nullptr;
}