/*
 * MotorcycleSpot.cpp
 *
 *  Author: Carter Hawks from CS2336.001
 *  To run: the main() is located in ParkingLot.cpp
 *      Different sections of the code are commented out;
 *      these sections accomplish the different variations of the parking lot.
 */

// MotorcycleSpot: this object is representative for the motorcycle spot in the parking lot.
//  Its only functionality is to determine if a Vehicle is able to park in it or not.

#include "MotorcycleSpot.h"

MotorcycleSpot::MotorcycleSpot() {
	// do nothing
}

MotorcycleSpot::~MotorcycleSpot() {
	// do nothing
}

bool MotorcycleSpot::canFit(int vehicleType){
	if((vehicleType == Vehicle::V_MOTORCYCLE) && (taken == false)){
		return true;
	}

	return false;
}

string MotorcycleSpot::toString(){
	if(taken){
		return "M";
	} else {
		return "m";
	}
}
