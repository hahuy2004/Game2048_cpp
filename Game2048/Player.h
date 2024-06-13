#pragma once

#include "Progress.h"
#include <string>

using std::string;

class Player {
private:
    string _name;
    Progress _progress;
    int _score;
    double _time;
public:
    // constructor
    Player();
    Player(const string&, const Progress&);
    Player(const string&, const Progress&, const int&);
    Player(const string&, const Progress&, const int&, const int&);
    // operation
    Progress& getProgress();
    string name() const;
    double time() const;
    int score() const;
    void setScore(const int&);
    void setTime(const double&);
    void freeMemory();
};

Player::Player() :
    _name("No data"), _time(0), _score(0) { }

Player::Player(const string& name, const Progress& progress) :
    _name(name), _progress(progress), _time(0) { }

Player::Player(const string& name, const Progress& progress, const int& time) :
    _name(name), _progress(progress), _time(time) { }

Player::Player(const string& name, const Progress& progress, const int& time, const int& score) :
    _name(name), _progress(progress), _time(time), _score(score) { }

Progress& Player::getProgress() {
    return _progress;
}

string Player::name() const {
    return _name;
}

double Player::time() const {
    return _time;
}

int Player::score() const {
    return _score;
}

void Player::setScore(const int& score) {
    this->_score = score;
}

void Player::setTime(const double& time) {
    this->_time = time;
}

void Player::freeMemory() {
    _progress.freeMemory();
}