#ifndef UI_H
#define UI_H

#include <iostream>
#include <string>
#include <unistd.h>
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
	* Function: FileExists.
	* Checks if a file exists (Needed for the Input & Output Files).
	*/
	bool FileExists(string fileName) const;

    /*
	* Function: GetAppMode.
	* Returns the current Application Mode.
	*/
    MODE GetAppMode() const;
    
    /*
	* Function: SaveOutput.
	* Produces the simulation output file.
	*/
    void SaveOutput() const;
};

#endif