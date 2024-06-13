#pragma once

#include "Player.h"
#include "vector.h"
#include "string.h"
#include "file.h"
#include <fstream>

using std::ifstream, std::ofstream, std::ios;

class PlayerList {
private:
    vector<Player> _players;
public:
    // constructor
    PlayerList() = default;
    // operation
    void readFile(vector<string>&);
    void writeFile(vector<string>&);
    vector<Player> getPlayers();
    int update(const Player&);
    void save(const Player&, const int&);
    int find(const string&);
    void freeMemory();

    class ReadPlayer {
    public:
        static Player read(const string&);
    };
};

Player PlayerList::ReadPlayer::read(const string& fileName) {
    ifstream fin;
    fin.open(fileName, ios::binary);

    if (!fin.is_open()) {
        throw "Cannot open file";
    }
    if (File::checkEmpty(fileName)) {
        fin.close();
        return Player();
    }

    int nameSize;
    fin.read(reinterpret_cast<char*>(&nameSize), sizeof(int));

    char* cname = new char[nameSize];
    fin.read(cname, nameSize);
    string name = Utils::String::ctostr(cname, nameSize);

    int score;
    double time;
    fin.read(reinterpret_cast<char*>(&score), sizeof(int));
    fin.read(reinterpret_cast<char*>(&time), sizeof(double));

    int rows, cols, data, cache;
    fin.read(reinterpret_cast<char*>(&rows), sizeof(int));
    fin.read(reinterpret_cast<char*>(&cols), sizeof(int));
    fin.read(reinterpret_cast<char*>(&data), sizeof(int));
    fin.read(reinterpret_cast<char*>(&cache), sizeof(int));

    stack<Matrix> data_;
    for (int idx = 0; idx < data; idx++) {
        int s;
        fin.read(reinterpret_cast<char*>(&s), sizeof(int));
        int** matrix = new int*[rows];
        for (int j = 0; j < rows; j++) {
            matrix[j] = new int[cols];
            for (int k = 0; k < cols; k++) {
                int value = -1;
                fin.read(reinterpret_cast<char*>(&value), sizeof(int));
                matrix[j][k] = value;
            }
        }
        Matrix m(rows, cols, score, matrix);
        data_.push_back(m);
    }

    stack<Matrix> cache_;
    for (int idx = 0; idx < cache; idx++) {
        int s;
        fin.read(reinterpret_cast<char*>(&s), sizeof(int));
        int** matrix = new int*[rows];
        for (int j = 0; j < rows; j++) {
            matrix[j] = new int[cols];
            for (int k = 0; k < cols; k++) {
                int value;
                fin.read(reinterpret_cast<char*>(&value), sizeof(int));
                matrix[j][k] = value;
            }
        }

        Matrix m(rows, cols, s, matrix);
        cache_.push_back(m);
    }

    Progress progress(data_, cache_);
    delete cname;
    fin.close();
    Player p(name, progress, time, score);
    return p;
}

void PlayerList::readFile(vector<string>& fileNames) {
    for (int i = 0; i < fileNames.size(); i++) {
        string fileName = fileNames[i];
        Player p = ReadPlayer::read(fileName);
        cout << "here" << endl;
        _players.push_back(p);
    }
}

void PlayerList::writeFile(vector<string>& fileNames) {
    for (int i = 0; i < fileNames.size(); i++) {
        ofstream fout;
        string fileName = fileNames[i];
        fout.open(fileName, ios::binary);

        if (!fout.good()) {
            throw "Cannot open file";
        }

        if (_players[i].name() == "No data") {
            fout.close();
            continue;
        }

        int nameSize = _players[i].name().size();
        fout.write(reinterpret_cast<char*>(&nameSize), sizeof(int));
        char* cname = Utils::String::cstring(_players[i].name());
        fout.write(cname, nameSize);

        int score = _players[i].score();
        double time = _players[i].time();
        fout.write(reinterpret_cast<char*>(&score), sizeof(int));
        fout.write(reinterpret_cast<char*>(&time), sizeof(double));

        stack<Matrix> data_ = _players[i].getProgress().getData();
        stack<Matrix> cache_ = _players[i].getProgress().getCache();

        int rows = _players[i].getProgress().getCurrent().rows();
        int cols = _players[i].getProgress().getCurrent().columns();
        int data = data_.size();
        int cache = cache_.size();

        fout.write(reinterpret_cast<char*>(&rows), sizeof(int));
        fout.write(reinterpret_cast<char*>(&cols), sizeof(int));
        fout.write(reinterpret_cast<char*>(&data), sizeof(int));
        fout.write(reinterpret_cast<char*>(&cache), sizeof(int));

        for (int j = 0; j < data; j++) {
            int s = data_[j].score();
            fout.write(reinterpret_cast<char*>(&s), sizeof(int));
            for (int k = 0; k < rows; k++) {
                for (int l = 0; l < cols; l++) {
                    int value = data_[j].at(k, l);
                    fout.write(reinterpret_cast<char*>(&value), sizeof(int));
                }
            }
        }

        for (int j = 0; j < cache; j++) {
            int s = cache_[j].score();
            fout.write(reinterpret_cast<char*>(&s), sizeof(int));
            for (int k = 0; k < rows; k++) {
                for (int l = 0; l < cols; l++) {
                    int value = cache_[j].at(k, l);
                    fout.write(reinterpret_cast<char*>(&value), sizeof(int));
                }
            }
        }

        fout.close();
    }
}

vector<Player> PlayerList::getPlayers() {
    return _players;
}

int PlayerList::update(const Player& p) {
    int pIndex = find(p.name());
    if (pIndex != -1) {
        if (p.score() >= _players[pIndex].score()) {
            if (p.score() == _players[pIndex].score() && p.time() >= _players[pIndex].time()) {
                return -1;
            }
            _players.erase(pIndex);
        }
        else {
            return -1;
        }
    }

    int index = 0;
    while (index < _players.size()) {
        if (_players[index].score() == p.score() && _players[index].time() > p.time()) {
            break;
        }
        else if (_players[index].score() < p.score()) {
            break;
        }
        index++;
    }

    if (index > 19) {
        return -1;
    }

    _players.insert(p, index);
    if (_players.size() > 20) {
        _players.pop();
    }
    return index + 1;
}

void PlayerList::save(const Player& p, const int& index) {
    _players[index] = p;
}

int PlayerList::find(const string& name) {
    for (int i = 0; i < _players.size(); i++) {
        if (_players[i].name() == name) {
            return i;
        }
    }
    return -1;
}

void PlayerList::freeMemory() {
    for (int i = 0; i < _players.size(); i++) {
        _players[i].freeMemory();
    }
    _players.clear();
}