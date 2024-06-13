#pragma once

#include <iostream>
#include <string>

using std::string, std::getline, std::cin, std::cout, std::endl;

class PlayerNameInputHandler {
public:
    static string next();
};

string PlayerNameInputHandler::next() {
    string name;

    do {
        system("cls");
        cout << "Enter your name: (within 10 character)" << endl;
        getline(cin, name);
        if(name.empty()) {
            cout << "Cannot leave blank" << endl;
        }
        if (name == "No data") {
            cout << "Not this name";
        }
    } while(name.empty());

    return name;
}