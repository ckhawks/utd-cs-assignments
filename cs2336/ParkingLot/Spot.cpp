/*
 * Spot.cpp
 *
 *  Author: Carter Hawks from CS2336.001
 *  To run: the main() is located in ParkingLot.cpp
 *      Different sections of the code are commented out;
 *      these sections accomplish the different variations of the parking lot.
 */

// Spot: an abstract class that illustrates the format for the descendant Spot objects. It does nothing on its own.

#include "Spot.h"

Spot::Spot() {
	taken = false;
}

Spot::~Spot() {
	// do nothing
}

// this method should never be called, but we provide "spot" as a default value anyways.
string Spot::toString(){
	return "spot";
}
