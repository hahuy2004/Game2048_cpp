#include "LoadSetting.h"
LoadSetting::LoadSetting() : _allowUndoRedo(false), _rows(4), _cols(4) {}

void LoadSetting::load(const string& fileName) {
    ifstream fin;
    fin.open(fileName, ios::binary);

    if (!fin.is_open()) {
        throw "Cannot open setting file";
    }

    fin.read(reinterpret_cast<char*>(&_allowUndoRedo), sizeof(bool));
    fin.read(reinterpret_cast<char*>(&_rows), sizeof(int));
    fin.read(reinterpret_cast<char*>(&_cols), sizeof(int));

    fin.close();
}

void LoadSetting::update(const string& fileName) {
    ofstream fout;
    fout.open(fileName, ios::binary);

    if (!fout.is_open()) {
        throw "Cannot open setting file";
    }

    fout.write(reinterpret_cast<char*>(&_allowUndoRedo), sizeof(bool));
    fout.write(reinterpret_cast<char*>(&_rows), sizeof(int));
    fout.write(reinterpret_cast<char*>(&_cols), sizeof(int));

    fout.close();
}

bool LoadSetting::allowUndoRedo() {
    return _allowUndoRedo;
}

int LoadSetting::rows() {
    return _rows;
}

int LoadSetting::cols() {
    return _cols;
}

void LoadSetting::setAllowUndoRedo(const bool& allow) {
    _allowUndoRedo = allow;
}

void LoadSetting::setRows(const int& rows) {
    _rows = rows;
}

void LoadSetting::setCols(const int& cols) {
    _cols = cols;
}