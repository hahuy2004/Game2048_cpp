#include "Progress.h"

Progress::Progress(LoadSetting setting) {
    Matrix matrix(setting.rows(), setting.cols());
    matrix.addRandom();
    matrix.addRandom();
    _data.push_back(matrix);
}

Progress::Progress(stack<Matrix> data, stack<Matrix> cache) :
    _data(data), _cache(cache) { }

Matrix Progress::getCurrent() {
    return _data.top();
}

void Progress::update(Matrix newMatrix) {
    _cache.clear();
    _data.push_back(newMatrix);
}

void Progress::undo() {
    if (1 == _data.size()) {
        throw "Nothing to undo";
    }

    _cache.push_back(_data.top());
    _data.pop();
}

void Progress::redo() {
    if (_cache.empty()) {
        throw "Nothing to redo";
    }

    _data.push_back(_cache.top());
    _cache.pop();
}

stack<Matrix> Progress::getData() {
    return _data;
}

stack<Matrix> Progress::getCache() {
    return _cache;
}

void Progress::freeMemory() {
    for (int i = 0; i < _data.size(); i++) {
        _data[i].freeMemory();
    }
    _data.clear();

    for (int i = 0; i < _cache.size(); i++) {
        _cache[i].freeMemory();
    }
    _cache.clear();
}