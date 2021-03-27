/*
 * Level.cpp
 *
 *  Author: Carter Hawks from CS2336.001
 *  To run: the main() is located in ParkingLot.cpp
 *      Different sections of the code are commented out;
 *      these sections accomplish the different variations of the parking lot.
 */

// Level: this object acts as a container for the descendant Row objects. It does not do anything on its own.

#include "Level.h"

Level::Level() {
	// do nothing
}

Level::~Level() {
	// do nothing
}

string Level::toString(){
	//cout << rowCount << endl;
	string output = "";
	for (int i = 0; i < rowCount; i++){
		//cout << "hellooooo" << endl;
		//output = output + "Row " + to_string(i) + ": " + this->rows[i].toString() + " ";
		output = output + this->rows[i].toString() + " ";
	}
	return output;
}

