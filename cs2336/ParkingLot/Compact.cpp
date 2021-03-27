/*
 * Compact.cpp
 *
 *  Author: Carter Hawks from CS2336.001
 *  To run: the main() is located in ParkingLot.cpp
 *      Different sections of the code are commented out;
 *      these sections accomplish the different variations of the parking lot.
 */

// Compact: simple class that represents a Compact object. Sole purpose is to return the correct vehicleType enum in the getVehicleType() method.

#include "Compact.h"

Compact::Compact() {
	// do nothing
}

Compact::~Compact() {
	// do nothing
}

int Compact::getVehicleType(){
	return V_CAR;
}
