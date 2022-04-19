#ifndef UI_CPP
#define UI_CPP

#include "UI.h"

UI::UI() {
    this->AppMode = INTER;
    this->SetAppMode();
}

UI::~UI() {}

void UI::SetAppMode() {
    int ModeChoice = -1;
    // Getting the user's choice of the app mode.
    while(ModeChoice < 0 || ModeChoice > 2) {
        cout << "----------------------------" << endl;
        cout << "SELECT THE APPLICATION MODE:" << endl;
        cout << "----------------------------" << endl;
        cout << "[0]: Interactive Mode" << endl;
        cout << "[1]: Step-By-Step Mode" << endl;
        cout << "[2]: Silent Mode" << endl;
        cout << ">> ";
        cin >> ModeChoice;
    }
    // Assigning the correct value to the AppMode variable.
    switch (ModeChoice) {
        case 0:
            this->AppMode = INTER;
            break;
        case 1:
            this->AppMode = STEP;
            break;
        default:
            this->AppMode = SILENT;
    }
}

MODE UI::GetAppMode() const {
    return this->AppMode;
}

#endif