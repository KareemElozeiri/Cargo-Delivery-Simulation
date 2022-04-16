#pragma once
#include <iostream>

enum MODE {
	INTER,	// Interactive mode
	STEP,	// Step-by-step mode
	SILENT // Silent mode
};

enum EVENT {
	R,	// Ready Event
	P,	// Promotion Event
	X	// Cancellation Event
};

enum CARGOTYPE {
	N,	// Normal Cargo
	S,	// Special Cargo
	V	// VIP Cargo
};



