/*
 * LargeSpot.cpp
 *
 *  Author: Carter Hawks from CS2336.001
 *  To run: the main() is located in ParkingLot.cpp
 *      Different sections of the code are commented out;
 *      these sections accomplish the different variations of the parking lot.
 */

// LargeSpot: this object is representative for the large spot in the parking lot.
//  Its only functionality is to determine if a Vehicle is able to park in it or not.

#include "LargeSpot.h"

LargeSpot::LargeSpot() {
	// do nothing
}

LargeSpot::~LargeSpot() {
	// do nothing
}


bool LargeSpot::canFit(int vehicleType){
	if((vehicleType == Vehicle::V_BUS || vehicleType == Vehicle::V_CAR || vehicleType == Vehicle::V_MOTORCYCLE) && (taken == false)){
		return true;
	}

	return false;
}

string LargeSpot::toString(){
	//cout << "printing this motorcycle spot" << endl;
	if(taken){
		return "B";
	} else {
		return "l";
	}
}
