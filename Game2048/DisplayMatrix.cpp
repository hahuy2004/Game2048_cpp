#include "DisplayMatrix.h"

void DisplayMatrix::display(const Matrix &matrix) {
    hline(matrix.columns() * 6 + 1);
    HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    for (int i = 0; i < matrix.rows(); i++) {
        cout << "|";
        for (int j = 0; j < matrix.columns(); j++) {
            cout << setw(5) << setfill(' ');
            if (-1 == matrix.at(i, j)) {
                cout << " ";
            }
            else {
                SetConsoleTextAttribute(hConsole, matrix.at(i, j) % 100);
                cout << Utils::String::centering(std::to_string(matrix.at(i, j)), 5);
                SetConsoleTextAttribute(hConsole, 15);
            }
            cout << "|";
        }
        cout << endl;
        hline(matrix.columns() * 6 + 1);
    }
}

void DisplayMatrix::hline(const int &size) {
    cout << setw(size) << setfill('-') << "-" << endl;
}