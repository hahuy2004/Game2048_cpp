#pragma once

#include "PlayerList.h"
#include "Keymap.h"
#include "HandleInput.h"
#include "Color.h"
#include <Windows.h>
using std::cout, std::endl;

class Top20Display {
public:
    static void display(PlayerList list) {
        cout << "Top\tName\t\tScore\t\tTime" << endl;
        vector<Player> players = list.getPlayers();
        for (int i = 0; i < 20; i++) {
            cout << i + 1 << "\t";
            if (players[i].name() == "No data") {
                cout << endl;
            }
            else {
                cout << players[i].name() << "\t\t";
                cout << players[i].score() << "\t\t";
                cout << players[i].time() << endl;
            }
        }
    }
};