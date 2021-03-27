/*
 * LargeSpot.h
 *
 *  Author: Carter Hawks from CS2336.001
 *  To run: the main() is located in ParkingLot.cpp
 *      Different sections of the code are commented out;
 *      these sections accomplish the different variations of the parking lot.
 */

// LargeSpot: this object is representative for the large spot in the parking lot.
//  Its only functionality is to determine if a Vehicle is able to park in it or not.

#ifndef LARGESPOT_H_
#define LARGESPOT_H_

#include "Spot.h"

class LargeSpot: public Spot {
public:
	LargeSpot();
	virtual ~LargeSpot();
	bool canFit(int);
	string toString();
};

#endif /* LARGESPOT_H_ */
