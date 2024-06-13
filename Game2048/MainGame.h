#pragma once

#include "string.h"
#include "Player.h"
#include "HandleInput.h"
#include "DisplayMatrix.h"
#include "PlayerList.h"
#include "Timer.h"

class Game {
private:
public:
    static bool display(Player&, bool);
};

bool Game::display(Player& p, bool rule) {
    bool result = true;
    Stopwatch time;
    time.start();
    do {
        p.setTime(time.elapsed_seconds());
        system("cls");
        p.setScore(p.getProgress().getCurrent().score());
        cout << "Score: " << p.score() << endl << endl;
        Matrix matrix(p.getProgress().getCurrent());

        if (matrix.stuck()) {
            time.stop();
            result = true;
            system("cls");
            cout << "You lost!" << endl;
            if (rule) {
                cout << "Try again?" << endl;
                int t = KeyboardInputHandler::next();
                if (27 == t) {
                    break;
                }
                if (Enter == t) {
                    p.getProgress().undo();
                    time.start();
                    continue;
                }
            }
            else {
                break;
            }
        }
        else if (matrix.maxNumber() == 2048) {
            time.stop();
            result = 1;
            system("cls");
            cout << "Congratulation!\nDo you want to continue?" << endl;
            int c = KeyboardInputHandler::next();
            if (27 == c) {
                break;
            }
            time.start();
        }

        DisplayMatrix::display(matrix);
        int k = KeyboardInputHandler::next();

        if (k == Up) {
            matrix.moveUp();
            matrix.addRandom();
            p.getProgress().update(matrix);
        }
        if (k == Down) {
            matrix.moveDown();
            matrix.addRandom();
            p.getProgress().update(matrix);
        }
        if (k == Left) {
            matrix.moveLeft();
            matrix.addRandom();
            p.getProgress().update(matrix);
        }
        if (k == Right) {
            matrix.moveRight();
            matrix.addRandom();
            p.getProgress().update(matrix);
        }
        if (k == Undo && rule) {
            try {
                p.getProgress().undo();
            } catch (...) {
                cout << "Cannot undo" << endl;
            }
        }
        if (k == Redo && rule) {
            try {
                p.getProgress().redo();
            } catch (...) {
                cout << "Cannot redo" << endl;
            }
        }
        if (k == 27) {
            time.stop();
            system("cls");
            cout << "Do you want to exit?" << endl;
            k = KeyboardInputHandler::next();
            if (k == Enter) {
                p.setTime(time.elapsed_seconds());
                return false;
            }
            time.start();
        }
    } while (true);
    p.setTime(time.elapsed_seconds());
    return result;
}