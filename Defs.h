#pragma once
#include <iostream>

// enum class to prevent conversions to int values
// Each memeber is treated as an object type

enum class MODE {
	INTER,	// Interactive mode
	STEP,	// Step-by-step mode
	SILENT // Silent mode
};

enum class EVENT {
	R,	// Ready Event
	P,	// Promotion Event
	X	// Cancellation Event
};

enum class CARGOTYPE {
	N,	// Normal Cargo
	S,	// Special Cargo
	V	// VIP Cargo
};

enum class TRUCKTYPE {
	NT,	// Normal Truck
	ST,	// Special Truck
	VT	// VIP Truck
};


