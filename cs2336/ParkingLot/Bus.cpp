/*
 * Bus.cpp
 *
 *  Author: Carter Hawks from CS2336.001
 *  To run: the main() is located in ParkingLot.cpp
 *      Different sections of the code are commented out;
 *      these sections accomplish the different variations of the parking lot.
 */

// Bus: simple class that represents a Bus object. Sole purpose is to return the correct vehicleType enum in the getVehicleType() method.

#include "Bus.h"

Bus::Bus() {
	// do nothing
}

Bus::~Bus() {
	// do nothing
}

int Bus::getVehicleType(){
	return V_BUS;
}
