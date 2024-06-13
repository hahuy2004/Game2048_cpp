#include "MainMenu.h"

void MainMenu::printMenu() {
    cout << "   2222222        0000000           4444444       888888888" << endl;
    cout << "  2::222::2     0::00000::0        4::44::4      8:::888:::8" << endl;
    cout << " 2222   2::2   0::0     0::0      4::4 4::4     8:::8   8:::8" << endl;
    cout << "       2::2    0::0     0::0     4::4  4::4      8:::888:::8" << endl;
    cout << "     2::2      0::0     0::0    4::44444::444    8:::888:::8" << endl;
    cout << "    2::2       0::0     0::0    44444444::444   8:::8   8:::8" << endl;
    cout << "  2::2_______   0::00000::0            4::4      8:::888:::8" << endl;
    cout << " 222222222222     0000000              4444       888888888" << endl;
    cout << endl << endl;
}

int MainMenu::modeChooser() {
    system("cls");int text = Color::White;
    int background = Color::Black; 
    int selected = 1;
    while (true) {
        system("cls");
        printMenu();
        HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, 15);

        if (1 == selected) {
            SetConsoleTextAttribute(hConsole, selected + background * 16);
        }
        cout << "New game";
        SetConsoleTextAttribute(hConsole, 15);
        cout << endl;
        if (2 == selected) {
            SetConsoleTextAttribute(hConsole, selected + background * 16);
        }
        cout << "Resume";
        SetConsoleTextAttribute(hConsole, 15);
        cout << endl;
        if (3 == selected) {
            SetConsoleTextAttribute(hConsole, selected + background * 16);
        }
        cout << "Setting";
        SetConsoleTextAttribute(hConsole, 15);
        cout << endl;
        if (4 == selected) {
            SetConsoleTextAttribute(hConsole, selected + background * 16);
        }
        cout << "Top-20 list";
        SetConsoleTextAttribute(hConsole, 15);

        int c = KeyboardInputHandler::next();
        if (c == Up && selected > 1) {
            selected--;
        }
        else if (c == Down && selected < 4) {
            selected++;
        }
        else if (c == Enter) break;
    }
    system("cls");
    return selected;
}