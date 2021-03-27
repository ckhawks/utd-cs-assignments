/*
 * CompactSpot.cpp
 *
 *  Author: Carter Hawks from CS2336.001
 *  To run: the main() is located in ParkingLot.cpp
 *      Different sections of the code are commented out;
 *      these sections accomplish the different variations of the parking lot.
 */

// CompactSpot: this object is representative for the compact spot in the parking lot.
//  Its only functionality is to determine if a Vehicle is able to park in it or not.

#include "CompactSpot.h"

CompactSpot::CompactSpot() {
	taken = false;
}

CompactSpot::~CompactSpot() {
	// do nothing
}

bool CompactSpot::canFit(int vehicleType){
	if((vehicleType == Vehicle::V_MOTORCYCLE || vehicleType == Vehicle::V_CAR) && (taken == false)){
		return true;
	}

	return false;
}

string CompactSpot::toString(){
	if(taken){
		return "C";
	} else {
		return "c";
	}
}
