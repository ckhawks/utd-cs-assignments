/*
 * Vehicle.cpp
 *
 *  Author: Carter Hawks from CS2336.001
 *  To run: the main() is located in ParkingLot.cpp
 *      Different sections of the code are commented out;
 *      these sections accomplish the different variations of the parking lot.
 */

// Vehicle: an abstract class that illustrates the format for the descendant Vehicle objects. It does nothing on its own.

#include "Vehicle.h"

Vehicle::Vehicle() {
	// do nothing
}

Vehicle::~Vehicle() {
	// do nothing
}

// this doesn't really need to be here, remove later
int Vehicle::getVehicleType(){
	return 0;
}
