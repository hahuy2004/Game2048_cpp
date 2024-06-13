#pragma once

#include "LoadSetting.h"
#include "HandleInput.h"
#include "Keymap.h"
#include "Color.h"
#include <Windows.h>

class SettingDisplay {
public:
    static void display(LoadSetting&);
};

void SettingDisplay::display(LoadSetting& setting) {
    int text = Color::White;
    int background = Color::Black; 
    int selected = 1;
    while (true) {
        system("cls");
        HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 15);

        if (1 == selected) {
            SetConsoleTextAttribute(hConsole, selected + background * 16);
        }
        cout << "Enable Undo/Redo:\t\t";
        if (setting.allowUndoRedo()) {
            cout << "Enabled" << endl;
        }
        else {
            cout << "Disable" << endl;
        }

        SetConsoleTextAttribute(hConsole, 15);
        cout << endl;
        if (2 == selected) {
            SetConsoleTextAttribute(hConsole, selected + background * 16);
        }
        cout << "Game size:\t\t";
        if (setting.rows() != 4 && setting.cols() != 4) {
            cout << " <- ";
        }
        cout << setting.rows() << "x" << setting.cols();
        if (setting.rows() != 16 && setting.cols() != 16) {
            cout << " -> ";
        }
        SetConsoleTextAttribute(hConsole, 15);
        cout << endl;

        int c = KeyboardInputHandler::next();
        if (c == Up && selected > 1) {
            selected--;
        }
        else if (c == Down && selected < 4) {
            selected++;
        }
        else if (c == Left && selected == 2) {
            if (setting.rows() != 4 && setting.cols() != 4) {
                setting.setRows(setting.rows() - 1);
                setting.setCols(setting.cols() - 1);
            }
        }
        else if (c == Right && selected == 2) {
            if (setting.rows() != 16 && setting.cols() != 16) {
                setting.setRows(setting.rows() + 1);
                setting.setCols(setting.cols() + 1);
            }
        }
        else if (c == Enter && selected == 1) {
            setting.setAllowUndoRedo(!setting.allowUndoRedo());
        }
        else if (c == 27) {
            break;
        }
        setting.update("Setting/setting.bin");
    }
}