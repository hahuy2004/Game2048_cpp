#include "HandleInput.h"

int KeyboardInputHandler::next() {
    unsigned char key = _getch();

    if (Keys::Arrow == key) {
        unsigned char arrow = _getch();

        switch (arrow) {
        case Keys::Up:
            return Up;
            break;
        case Keys::Down:
            return Down;
            break;
        case Keys::Left:
            return Left;
            break;
        case Keys::Right:
            return Right;
            break;
        }
    }
    else {
        switch (key) {
        case Keys::Enter:
            return Enter;
            break;
        case 27:
            return 27;
            break;
        case 82: case 114:
            return Redo;
            break;
        case 84: case 117:
            return Undo;
            break;
        }
    }
    return next();
}