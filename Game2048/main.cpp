#include <iostream>
#include "HandleInput.h"
#include "PlayerNameInputHandler.h"
#include "Matrix.h"
#include "MainMenu.h"
#include "DisplayMatrix.h"
#include "LoadSetting.h"
#include "MainGame.h"
#include "SettingDisplay.h"  
#include "vector.h"
#include "SaveSlotDisplay.h"
#include "Top20Display.h"
#include "SaveGame.h"
#include "string.h"

using std::cout, std::cin, std::endl;

int main() {
    string settingFile = "setting.bin";
    LoadSetting setting;
    setting.load(settingFile);

    vector<string> saveFile;
    saveFile.push_back("Save/p1.bin");
    saveFile.push_back("Save/p2.bin");
    saveFile.push_back("Save/p3.bin");
    saveFile.push_back("Save/p4.bin");
    saveFile.push_back("Save/p5.bin");
    PlayerList save;
    save.readFile(saveFile);
    
    vector<string> topListFile;
    topListFile.push_back("Records/p1.bin");
    topListFile.push_back("Records/p2.bin");
    topListFile.push_back("Records/p3.bin");
    topListFile.push_back("Records/p4.bin");
    topListFile.push_back("Records/p5.bin");
    topListFile.push_back("Records/p6.bin");
    topListFile.push_back("Records/p7.bin");
    topListFile.push_back("Records/p8.bin");
    topListFile.push_back("Records/p9.bin");
    topListFile.push_back("Records/p10.bin");
    topListFile.push_back("Records/p11.bin");
    topListFile.push_back("Records/p12.bin");
    topListFile.push_back("Records/p13.bin");
    topListFile.push_back("Records/p14.bin");
    topListFile.push_back("Records/p15.bin");
    topListFile.push_back("Records/p16.bin");
    topListFile.push_back("Records/p17.bin");
    topListFile.push_back("Records/p18.bin");
    topListFile.push_back("Records/p19.bin");
    topListFile.push_back("Records/p20.bin");
    PlayerList top20;
    top20.readFile(topListFile);

    do {
        int opt = MainMenu::modeChooser();
        system("cls");
        if (1 == opt) {
            cout << "Enter player name: ";
            string pName = PlayerNameInputHandler::next();
            Progress progress(setting);
            Player p(pName, progress);

            int win = Game::display(p, setting.allowUndoRedo());
            if (!win) {
                SaveGame::saveGame(p, save);
                break;
            }
            else {
                int top = top20.update(p);
                if (top == -1) {
                    cout << "You are out of top 20. Better luck next time" << endl;
                }
                else {
                    cout << "You are in top " << top << " players" << endl;
                }
                system("pause");
            }
            p.freeMemory();
        }
        else if (2 == opt) {
            int choosePlayer = SaveSlotDisplay::choose(save);
            Player p = save.getPlayers()[choosePlayer];

            if (p.name() == "No data") {
                continue;
            }

            Game::display(p, setting.allowUndoRedo());
            int win = Game::display(p, setting.allowUndoRedo());
            if (!win) {
                SaveGame::saveGame(p, save);
            }
            else {
                int top = top20.update(p);
                if (top == -1) {
                    cout << "You are out of top 20. Better luck next time" << endl;
                }
                else {
                    cout << "You are in top " << top << " players" << endl;
                }
            }
            p.freeMemory();
        }
        else if (3 == opt) {
            SettingDisplay::display(setting);
            continue;
        }
        else {
            Top20Display::display(top20);
        }

        if (KeyboardInputHandler::next() == 27) break;        
    } while (true);

    save.writeFile(saveFile);
    top20.writeFile(topListFile);

    save.freeMemory();
    top20.freeMemory();
    
    return 0;
}