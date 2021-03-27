/*
 * Bus.h
 *
 *  Author: Carter Hawks from CS2336.001
 *  To run: the main() is located in ParkingLot.cpp
 *      Different sections of the code are commented out;
 *      these sections accomplish the different variations of the parking lot.
 */

// Bus: simple class that represents a Bus object. Sole purpose is to return the correct vehicleType enum in the getVehicleType() method.

#ifndef BUS_H_
#define BUS_H_

#include "Vehicle.h"

class Bus: public Vehicle {
public:
	Bus();
	virtual ~Bus();
	int getVehicleType();
};

#endif /* BUS_H_ */
