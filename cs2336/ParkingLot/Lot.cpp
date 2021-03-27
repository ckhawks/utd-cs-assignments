/*
 * Lot.cpp
 *
 *  Author: Carter Hawks from CS2336.001
 *  To run: the main() is located in ParkingLot.cpp
 *      Different sections of the code are commented out;
 *      these sections accomplish the different variations of the parking lot.
 */

// Lot: this object is the main container for all of the other child objects.
// It also handles the parking & removal logic for all of the vehicles.

#include "Lot.h"

Lot::Lot() {
	// do nothing
}

Lot::~Lot() {
	// do nothing
}

// initialize the array of Levels
void Lot::addLevels(int count){
	Lot::levels = new Level[count];
}

// return the array of Levels
Level* Lot::getLevels(){
	return Lot::levels;
}

// return a specficied Level object
Level Lot::getLevel(int which){
	return Lot::levels[which];
}

// return the string representation of the Lot
string Lot::toString(){
	string output = "";
	for (int i = 0; i < this->levelCount; i++){
		output = output + "Level " + to_string(i) + ": " + levels[i].toString() + "\n";
	}
	return output;
}


// park vehicle in randomly selected spot
// 	 if spot is taken, choose another random spot.
bool Lot::parkVehicleRandom(Vehicle* v){
	bool parked = false;
	while(parked == false){
		// choose random level
		int levelIndex = rand() % this->levelCount;
		Level level = this->getLevel(levelIndex);
		int rowIndex = rand() % level.rowCount;
		Row row = level.rows[rowIndex];
		int spotIndex = rand() % row.spotCount;
		Spot* spot = row.getSpot(spotIndex);

		bool canPark = false;
		if(v->getVehicleType() == v->V_BUS){
			// check next 4 spots after as well

		} else {
			canPark = spot->canFit(v->getVehicleType());
		}

		if(canPark == true){
			// park the vehicle there
			spot->taken = true;
			parked = true;
			//cout << "parked " << v->getVehicleType() << " in spot " << spotIndex << " on row " << rowIndex << " on level " << levelIndex << endl;
		} else {
			// need to choose different random spot
			//cout << "spot didn't work" << endl;
		}
	}
	return parked;
}

// park vehicle at the first available spot
//   starting at 0, 0, 0, moving towards the last spot on last row on last level
bool Lot::parkVehicleFirst(Vehicle* v){
	bool parked = false;

	// start at level 0, row 0, spot 0
	int levelIndex = 0;
	int rowIndex   = 0;
	int spotIndex  = 0;

	while(parked == false){
		Level level = this->getLevel(levelIndex);
		Row row = level.rows[rowIndex];
		Spot* spot = row.getSpot(spotIndex);

		bool canPark = false;
		if(v->getVehicleType() == v->V_BUS){
			// buses

			// check if there is valid space after current spot for bus
			if(spotIndex + 4 < row.spotCount){
				// check all of the spots for space
				bool spot0 = row.getSpot(spotIndex + 0)->canFit(v->getVehicleType());
				bool spot1 = row.getSpot(spotIndex + 1)->canFit(v->getVehicleType());
				bool spot2 = row.getSpot(spotIndex + 2)->canFit(v->getVehicleType());
				bool spot3 = row.getSpot(spotIndex + 3)->canFit(v->getVehicleType());
				bool spot4 = row.getSpot(spotIndex + 4)->canFit(v->getVehicleType());
				if(spot0 && spot1 && spot2 && spot3 && spot4){
					canPark = true;
				}
			}
		} else {
			// compacts and motorcycles
			canPark = spot->canFit(v->getVehicleType());
		}

		// we know now whether the vehicle can park there or not.

		if(canPark == true){
			if(v->getVehicleType() == Vehicle::V_BUS){
				for(int i = 0; i < 5; i++){
					row.getSpot(spotIndex + i)->taken = true;
				}
				parked = true;
				//cout << "parked BUS " << v->getVehicleType() << " in spots " << spotIndex << " to " << spotIndex + 4 << " on row " << rowIndex << " on level " << levelIndex << endl;
			}

			// park cars and motorcycles
			spot->taken = true;
			parked = true;
			//cout << "parked " << v->getVehicleType() << " in spot " << spotIndex << " on row " << rowIndex << " on level " << levelIndex << endl;
		} else {

			// they could not park, so increment to the next spot in the Lot. (with valid out of bounds overflowing)
			spotIndex = spotIndex + 1;
			if(spotIndex >= row.spotCount){
				rowIndex = rowIndex + 1;
				spotIndex = 0;
			}
			if(rowIndex >= level.rowCount){
				levelIndex = levelIndex + 1;
				rowIndex = 0;
			}
			if(levelIndex >= this->levelCount){
				// there are no possible spots left.
				parked = false;
				break;
			}
		}
	}
	return parked;
}

// park a Vehicle in a specific spot
bool Lot::parkVehicleSpecific(Vehicle* v, int levelIndex, int rowIndex, int spotIndex){
	bool parked = false;

	Level level = this->getLevel(levelIndex);
	Row row = level.rows[rowIndex];
	Spot* spot = row.getSpot(spotIndex);

	if(v->getVehicleType() == Vehicle::V_BUS){
		// bus
		// check if there is valid space after current spot for bus
		if(spotIndex + 4 < row.spotCount){
			// check all of the spots for space
			bool spot0 = row.getSpot(spotIndex + 0)->canFit(v->getVehicleType());
			bool spot1 = row.getSpot(spotIndex + 1)->canFit(v->getVehicleType());
			bool spot2 = row.getSpot(spotIndex + 2)->canFit(v->getVehicleType());
			bool spot3 = row.getSpot(spotIndex + 3)->canFit(v->getVehicleType());
			bool spot4 = row.getSpot(spotIndex + 4)->canFit(v->getVehicleType());
			if(spot0 && spot1 && spot2 && spot3 && spot4){
				for(int i = 0; i <= 4; i++){
					row.getSpot(spotIndex + i)->taken = true;
				}
				parked = true;
				//cout << "parked BUS " << v->getVehicleType() << " in spots " << spotIndex << " to " << spotIndex + 4 << " on row " << rowIndex << " on level " << levelIndex << endl;
			}
		} else {
			// there are not enough spaces following the selected one for the bus to fit.
			// parking failed.
			return parked;
		}

	} else {

		// car or motorcycle
		if(spot->canFit(v->getVehicleType())){
			// spot is not taken, and vehicle will fit.
			spot->taken = true;
			parked = true;
			//cout << "parked " << v->getVehicleType() << " in spot " << spotIndex << " on row " << rowIndex << " on level " << levelIndex << endl;
		} else {
			// vehicle will not fit in spot or spot is taken
			return parked;
		}
	}

	return parked;
}

// remove a parked vehicle from a specific spot. (or set of spots, for a bus)
bool Lot::removeVehicleSpecific(int levelIndex, int rowIndex, int spotIndex, bool bus = false){
	bool removed = false;

	Level level = this->getLevel(levelIndex);
	Row row = level.rows[rowIndex];
	Spot* spot = row.getSpot(spotIndex);

	if(bus == false){
		// we are dealing with a car or motorcycle, easy peasy.
		if(spot->taken == true){
			spot->taken = false;
			removed = true;
		} else {
			// there is not a vehicle in the spot.
			return removed;
		}
	} else {
		// we are dealing with a bus

		if(spotIndex + 4 < row.spotCount){
			bool spot0 = row.getSpot(spotIndex + 0)->taken;
			bool spot1 = row.getSpot(spotIndex + 1)->taken;
			bool spot2 = row.getSpot(spotIndex + 2)->taken;
			bool spot3 = row.getSpot(spotIndex + 3)->taken;
			bool spot4 = row.getSpot(spotIndex + 4)->taken;
			if(spot0 && spot1 && spot2 && spot3 && spot4){
				for(int i = 0; i <= 4; i++){
					row.getSpot(spotIndex + i)->taken = false;
				}
				removed = true;
				cout << "Removed Bus" << endl;
			} else {
				// some of the spots are not taken, meaning we cannot remove a full bus from this range of spots.
				return removed;
			}
		} else {
			// bus would be out of range
			return removed; // false
		}
	}
	return removed;
}
