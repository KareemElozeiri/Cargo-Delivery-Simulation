#ifndef UI_CPP
#define UI_CPP

#include "UI.h"

UI::UI() {
    this->AppMode = INTER;
    this->GetIOFiles();
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

void UI::GetIOFiles() {
    string InputFile;
    string OutputFile;

    // Getting the user's input file name.
    cout << "--------------------------------------" << endl;
    cout << "ENTER THE INPUT & OUTPUT FILES NAMES:" << endl;
    cout << "--------------------------------------" << endl;
    cout << "Notes:" << endl;
    cout << "[!]: The Input File Should Be Inside The Loads Directory" << endl;
    cout << "[!]: The Output File Should Be Inside The Outputs Directory" << endl;

    do {
        cout << "[+]: Input File Name: ";
        cin >> InputFile;
    }
    while (!filesystem::exists("Loads/" + InputFile));

    do {
        cout << "[+]: Output File Name: ";
        cin >> OutputFile;
    }
    while (!filesystem::exists("Outputs/" + OutputFile));

    this->InputFileName = "Loads/" + InputFile;
    this->OutputFileName = "Outputs/" + OutputFile;
}

string UI::GetInputFilePath() const {
    return this->InputFileName;
}

string UI::GetOutputFilePath() const {
    return this->OutputFileName;
}

MODE UI::GetAppMode() const {
    return this->AppMode;
}

void UI::PrintMsg(const string &msg) const {
    cout << msg << endl;
}

#endif