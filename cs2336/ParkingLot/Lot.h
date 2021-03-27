/*
 * Lot.h
 *
 *  Author: Carter Hawks from CS2336.001
 *  To run: the main() is located in ParkingLot.cpp
 *      Different sections of the code are commented out;
 *      these sections accomplish the different variations of the parking lot.
 */

// Lot: this object is the main container for all of the other child objects.
// It also handles the parking & removal logic for all of the vehicles.

#ifndef LOT_H_
#define LOT_H_
#include "Level.h"

class Lot {
public:
	Lot();
	virtual ~Lot();
	int levelCount;
	Level *levels;
	void addLevels(int);
	Level* getLevels();
	Level getLevel(int);
	string toString();
	bool parkVehicleRandom(Vehicle*);
	bool parkVehicleFirst(Vehicle*);
	bool parkVehicleSpecific(Vehicle*, int, int, int);
	bool removeVehicleSpecific(int, int, int, bool);
};

#endif /* LOT_H_ */
