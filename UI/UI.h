#ifndef UI_H
#define UI_H

#include <iostream>
#include <string>
#include <filesystem>
#include "../Defs.h"
using namespace std;

class UI
{
private:

    MODE AppMode;
	string InputFileName;
	string OutputFileName;

public:

    /*
	* Function: UI.
	* Default Constructor.
	*/
    UI();

    /*
	* Function: ~UI.
	* Destructor.
	*/
    ~UI();

    /*
	* Function: SetAppMode.
	* Sets the Application Mode.
	*/
    void SetAppMode();

	/*
	* Function: GetIOFiles.
	* Reads the Input & Output Files Names.
	*/
    void GetIOFiles();

    /*
	* Function: GetAppMode.
	* Returns the current Application Mode.
	*/
    MODE GetAppMode() const;

	/*
	* Function: GetInputFilePath.
	* Returns the path of the input file.
	*/
    string GetInputFilePath() const;

	/*
	* Function: GetOutputFilePath.
	* Returns the path of the output file.
	*/
    string GetOutputFilePath() const;
    
    /*
	* Function: SaveOutput.
	* Produces the simulation output file.
	*/
    void SaveOutput() const;

    /*
	* Function: PrintMsg.
	* Prints a message to the CLI.
	*/
    void PrintMsg(const string &msg) const;

	/*
	* Function: InteractiveInterfaceUpdate.
	* Updates the interface when the AppMode is set to Interactive.
	*/
	void InteractiveInterfaceUpdate(string currentTime, string InteractiveData) const;

	/*
	* Function: StepInterfaceUpdate.
	* Updates the interface when the AppMode is set to Step-By-Step.
	*/
	void StepInterfaceUpdate() const;

	/*
	* Function: SilentInterfaceUpdate.
	* Updates the interface when the AppMode is set to Silent.
	*/
	void SilentInterfaceUpdate() const;
};

#endif