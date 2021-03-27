/*
 * Row.h
 *
 *  Author: Carter Hawks from CS2336.001
 *  To run: the main() is located in ParkingLot.cpp
 *      Different sections of the code are commented out;
 *      these sections accomplish the different variations of the parking lot.
 */

// Row: a class that holds spots. Rows are created inside of a level. They are used to organize and manage the child spots

#ifndef ROW_H_
#define ROW_H_

#include "Spot.h"
#include <vector>
#include <memory>

using namespace std;

class Row {
public:
	Row();
	virtual ~Row();
	int spotCount;
	std::vector<Spot*>  spots;
	void setupSpots();
	std::vector<Spot*>  getSpots();
	string toString();
	void setSpot(int, Spot*);
	Spot* getSpot(int);
};

#endif /* ROW_H_ */
