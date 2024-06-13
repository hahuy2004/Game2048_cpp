#pragma once

#include <string>
#include <fstream>

using std::string, std::ifstream, std::ofstream, std::ios;

class LoadSetting {
private:
    bool _allowUndoRedo;
    int _rows;
    int _cols;
public:
    LoadSetting();

    void load(const string&);
    void update(const string&);
    bool allowUndoRedo();
    int rows();
    int cols();
    void setAllowUndoRedo(const bool&);
    void setRows(const int&);
    void setCols(const int&);
};