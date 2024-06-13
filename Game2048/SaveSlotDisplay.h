#pragma once

#include "PlayerList.h"
#include "Keymap.h"
#include "HandleInput.h"
#include "Color.h"
#include <Windows.h>
using std::cout, std::endl;

class SaveSlotDisplay {
public:
    static int choose(PlayerList list) {
        system("cls");int text = Color::White;
        int background = Color::Black; 
        int selected = 1;

        vector<Player> players = list.getPlayers();
        
        while (true) {
            system("cls");
            HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, 15);
            
            for (int i = 0; i < players.size(); i++) {
                if (i == selected - 1) {
                    SetConsoleTextAttribute(hConsole, selected + background * 16);
                    SlotDisplay::display(players[i]);
                    SetConsoleTextAttribute(hConsole, 15);
                }
                else {
                    SlotDisplay::display(players[i]);
                }
            }

            int c = KeyboardInputHandler::next();
            if (c == Up && selected > 1) {
                selected--;
            }
            else if (c == Down && selected < 5) {
                selected++;
            }
            else if (c == Enter) break;
        }
        return selected - 1;
    }

    class SlotDisplay {
    public:
        static void display(Player p) {
            cout << endl;
            if (p.name() == "No data") {
                cout << "Empty" << endl << endl;
            }
            else {
                cout << p.name() << endl;
                cout << "Score: " << p.score() << endl;
                cout << "Time: " << p.time() << endl;
            }
            cout << endl;
        }
    };
};