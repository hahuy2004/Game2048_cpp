#pragma once

#include "iostream"
#include "SaveSlotDisplay.h"
#include "HandleInput.h"
#include "Keymap.h"

using std::cout, std::endl;

class SaveGame {
public:
    static void saveGame(Player p, PlayerList& save) {
        int choosePlayer = SaveSlotDisplay::choose(save);
        if (save.getPlayers()[choosePlayer].name() == "No data") {
            save.save(p, choosePlayer);
        }
        else {
            system("cls");
            cout << "Overwrite a saved slot?" << endl;
            int k = KeyboardInputHandler::next();
            if (k == Enter) {
                save.save(p, choosePlayer);
            }
            else if (k == 27) {
                saveGame(p, save);
            }
        }
    }
};