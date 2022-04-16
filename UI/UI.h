#ifndef UI_H
#define UI_H

#include <iostream>
#include "../Defs.h"
using namespace std;

class UI
{
private:

    MODE AppMode;

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