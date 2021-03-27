/*
 * Spot.h
 *
 *  Author: Carter Hawks from CS2336.001
 *  To run: the main() is located in ParkingLot.cpp
 *      Different sections of the code are commented out;
 *      these sections accomplish the different variations of the parking lot.
 */

// Spot: an abstract class that illustrates the format for the descendant Spot objects. It does nothing on its own.

#ifndef SPOT_H_
#define SPOT_H_

#include "Vehicle.h"
#include <string>
#include <iostream>

using namespace std;

class Spot {
public:
	Spot();
	virtual ~Spot();
	bool taken;
	virtual bool canFit(int) = 0;
	virtual string toString() = 0;
};

#endif /* SPOT_H_ */
