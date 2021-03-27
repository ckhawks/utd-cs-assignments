/*
 * MotorcycleSpot.h
 *
 *  Author: Carter Hawks from CS2336.001
 *  To run: the main() is located in ParkingLot.cpp
 *      Different sections of the code are commented out;
 *      these sections accomplish the different variations of the parking lot.
 */

// MotorcycleSpot: this object is representative for the motorcycle spot in the parking lot.
//  Its only functionality is to determine if a Vehicle is able to park in it or not.

#ifndef MOTORCYCLESPOT_H_
#define MOTORCYCLESPOT_H_

#include "Spot.h"

class MotorcycleSpot: public Spot {
public:
	MotorcycleSpot();
	virtual ~MotorcycleSpot();
	bool canFit(int);
	string toString();
};

#endif /* MOTORCYCLESPOT_H_ */
