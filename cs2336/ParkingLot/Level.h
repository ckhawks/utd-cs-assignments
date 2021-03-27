/*
 * Level.h
 *
 *  Author: Carter Hawks from CS2336.001
 *  To run: the main() is located in ParkingLot.cpp
 *      Different sections of the code are commented out;
 *      these sections accomplish the different variations of the parking lot.
 */

// Level: this object acts as a container for the descendant Row objects. It does not do anything on its own.

#ifndef LEVEL_H_
#define LEVEL_H_
#include "Row.h"

class Level {
public:
	Level();
	virtual ~Level();
	int rowCount;
	Row* rows;
	string toString();
};

#endif /* LEVEL_H_ */
