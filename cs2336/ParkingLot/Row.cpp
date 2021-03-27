/*
 * Row.cpp
 *
 *  Author: Carter Hawks from CS2336.001
 *  To run: the main() is located in ParkingLot.cpp
 *      Different sections of the code are commented out;
 *      these sections accomplish the different variations of the parking lot.
 */

// Row: a class that holds spots. Rows are created inside of a level. They are used to organize and manage the child spots

#include "Row.h"
#include "CompactSpot.h"
#include "Spot.h"

Row::Row() {
	spotCount = 0;
}

Row::~Row() {
	// do nothing
}

// return the spots vector
std::vector<Spot*>  Row::getSpots(){
	return this->spots;
}

string Row::toString(){
	//cout << "begin printing row" << endl;
	string output = "";
	for (int i = 0; i < this->spotCount; i++){
		//cout << "printing a spot" << endl;
		output = output + this->getSpot(i)->toString();
	}
	return output;
}

// return the spot located at a specific index
Spot* Row::getSpot(int index){
	return this->spots[index];
}

// set a spot to a specific spot object (descendant of Spot class)
// basically just add it to the spots vector
void Row::setSpot(int index, Spot* spot){
	spots.push_back(spot);
}
