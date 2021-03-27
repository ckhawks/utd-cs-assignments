/*
 * CompactSpot.h
 *
 *  Author: Carter Hawks from CS2336.001
 *  To run: the main() is located in ParkingLot.cpp
 *      Different sections of the code are commented out;
 *      these sections accomplish the different variations of the parking lot.
 */

// CompactSpot: this object is representative for the compact spot in the parking lot.
//  Its only functionality is to determine if a Vehicle is able to park in it or not.

#ifndef COMPACTSPOT_H_
#define COMPACTSPOT_H_

#include "Spot.h"

class CompactSpot: public Spot {
public:
	CompactSpot();
	virtual ~CompactSpot();
	bool canFit(int);
	string toString();
};

#endif /* COMPACTSPOT_H_ */
