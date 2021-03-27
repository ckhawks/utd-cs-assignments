/*
 * Compact.h
 *
 *  Author: Carter Hawks from CS2336.001
 *  To run: the main() is located in ParkingLot.cpp
 *      Different sections of the code are commented out;
 *      these sections accomplish the different variations of the parking lot.
 */

// Compact: simple class that represents a Compact object. Sole purpose is to return the correct vehicleType enum in the getVehicleType() method.

#ifndef COMPACT_H_
#define COMPACT_H_

#include "Vehicle.h"

class Compact: public Vehicle {
public:
	Compact();
	virtual ~Compact();
	int getVehicleType();
};

#endif /* COMPACT_H_ */
