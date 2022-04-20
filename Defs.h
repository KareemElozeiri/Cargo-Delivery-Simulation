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

// enum class to prevent conversions to int values
// Each memeber is treated as an object type
enum class CARGOTYPE {
	N,	// Normal Cargo
	S,	// Special Cargo
	V	// VIP Cargo
};

enum TRUCKTYPE {
	NT,	// Normal Truck
	ST,	// Special Truck
	VT	// VIP Truck
};


