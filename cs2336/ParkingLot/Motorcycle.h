/*
 * Motorcycle.h
 *
 *  Author: Carter Hawks from CS2336.001
 *  To run: the main() is located in ParkingLot.cpp
 *      Different sections of the code are commented out;
 *      these sections accomplish the different variations of the parking lot.
 */

// Motorcycle: simple class that represents a Motorcycle object. Sole purpose is to return the correct vehicleType enum in the getVehicleType() method.

#ifndef MOTORCYCLE_H_
#define MOTORCYCLE_H_

#include "Vehicle.h"

class Motorcycle: public Vehicle {
public:
	Motorcycle();
	virtual ~Motorcycle();
	int getVehicleType();
};

#endif /* MOTORCYCLE_H_ */
