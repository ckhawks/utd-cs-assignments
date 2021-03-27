/*
 * ParkingLot.cpp
 *
 *  Author: Carter Hawks from CS2336.001
 *  To run: the main() is located in ParkingLot.cpp
 *      Different sections of the code are commented out;
 *      these sections accomplish the different variations of the parking lot.
 */

// ParkingLot: the main driver class for the project.
//	It handles the user input for the program,
//	instantiating the Lot object and its' descendants,
//	and finally the main work of the program: parking and removing vehicles.

#include <iostream>
#include <string>
#include <vector>
#include "Lot.h"
#include "Row.h"
#include "CompactSpot.h"
#include "LargeSpot.h"
#include "MotorcycleSpot.h"
#include "Spot.h"
#include "Motorcycle.h"
#include "Compact.h"
#include "Bus.h"

using namespace std;

// It is my design to place motorcycle spots towards the front, and bus spots towards the back.
// I do this so that when I'm checking if a vehicle can park, it takes the first available spot.
// Spots of the same type are placed consecutively.

// default values
// not constants, because they can be modified by the user.
int NUM_OF_LEVELS = 5;
int SPOTS_PER_LEVEL = 30;
int SPOTS_PER_ROW = 10;
int LARGE_SPOTS_PERCENT = 20;
int MOTORCYCLE_SPOTS_PERCENT = 20;

// wrapper method for parking a vehicle
// argument 1: the Lot to park in
// argument 2: enum value of vehicle type. Vehicle::V_CAR/V_BUS/V_MOTORCYCLE
// argument 3: how to park the vehicle. 1 = randomly, anything else = first available spot
// argument 4: how many vehicles to park that way.
void parkVehicle(Lot* L, int type = Vehicle::V_CAR, int how = 0, int count = 1){

	// decrement count every iteration
	while(count > 0){

		// create the vehicle
		Vehicle* m;
		if(type == Vehicle::V_CAR){
			m = new Compact();
			cout << "Parking a Car" << endl;
		} else if(type == Vehicle::V_MOTORCYCLE){
			m = new Motorcycle();
			cout << "Parking a Motorcycle" << endl;
		} else if(type == Vehicle::V_BUS){
			m = new Bus();
			cout << "Parking a Bus" << endl;
		} else {
			cout << "Not enough arguments." << endl;
			return;
		}

		// choose how to park vehicle
		if(how == 1){

			// park in random spot
			bool parked = L->parkVehicleRandom(m);
			if(parked == true){
				cout << L->toString() << endl;
			} else {
				cout << "Parking Failed. Final state:" << endl;
				break;
			}
		} else {

			// park in first available spot, default operation
			bool parked = L->parkVehicleFirst(m);
			if(parked == true){
				cout << L->toString() << endl;
			} else {
				cout << "Parking Failed. Final state:" << endl;
				break;
			}
		}
		count = count - 1;
	}

}

// wrapper method for adding a vehicle in a specific spot.
// argument 1: the Lot to park in
// argument 2: enum value of vehicle type. Vehicle::V_CAR/V_BUS/V_MOTORCYCLE
// argument 3: the level index to park in
// argument 4: the row   index to park in
// argument 5: the spot  index to park in
void parkVehicleSpot(Lot* L, int type = Vehicle::V_CAR, int level = 0, int row = 0, int spot = 0){
	// create the vehicle
	Vehicle* m;
	if(type == Vehicle::V_CAR){
		m = new Compact();
		cout << "Parking a Car" << endl;
	} else if(type == Vehicle::V_MOTORCYCLE){
		m = new Motorcycle();
		cout << "Parking a Motorcycle" << endl;
	} else if(type == Vehicle::V_BUS){
		m = new Bus();
		cout << "Parking a Bus" << endl;
	} else {
		cout << "Not enough arguments." << endl;
		return;
	}

	bool parked = L->parkVehicleSpecific(m, level, row, spot);
	if(parked == true){
	} else {
		cout << "Parking Failed. Final state: " << endl;
	}
	cout << L->toString() << endl;
}

// wrapper method for removing a vehicle from a specific spot.
// argument 1: the Lot to park in
// argument 2: the level index to remove vehicle at
// argument 3: the row   index to remove vehicle at
// argument 4: the spot  index to remove vehicle at
// argument 5: whether or not a bus is being removed.
void removeVehicleSpot(Lot* L, int level = 0, int row = 0, int spot = 0, int bus = false){
	cout << "Removing vehicle" << endl;
	bool removed = L->removeVehicleSpecific(level, row, spot, bus);
	if(removed == true){
		// do nothing
	} else {
		cout << "Removal Failed. Final state: " << endl;
	}
	cout << L->toString() << endl;
}

int main() {

	cout << "Welcome to Carter Hawks' Parking Lot Manager." << endl;

	// User Input: Levels in garage
	cout << "How many levels would you like in your garage? (default 5) ";
	string input1;
	getline(cin, input1);
	if(input1.empty() == false && input1 != ""){
		NUM_OF_LEVELS = stoi(input1);
	}
	cout << endl;

	// User Input: Spots per level
	cout << "How many spots would you like on each level? (default 30) ";
	string input2;
	getline(cin, input2);
	if(input2.empty() == false && input2 != ""){
		SPOTS_PER_LEVEL = stoi(input2);
	}
	cout << endl;

	// User Input: Spots per row
	cout << "How many spots would you like per row? (default 10) ";
	string input3;
	getline(cin, input3);
	if(input3.empty() == false && input3 != ""){
		SPOTS_PER_ROW = stoi(input3);
	}
	cout << endl;

	// User Input: Percent large spots
	cout << "What percent of spots would you like to be large? (default 20%) ";
	string input4;
	getline(cin, input4);
	if(input4.empty() == false && input4 != ""){
		LARGE_SPOTS_PERCENT = stoi(input4);
	}
	cout << endl;

	// User Input: Percent motorcycle spots
	cout << "What percent of spots would you like to be motorcycle? (default 20%) ";
	string input5;
	getline(cin, input5);
	if(input5.empty() == false && input5 != ""){
		MOTORCYCLE_SPOTS_PERCENT = stoi(input5);
	}
	cout << endl;

	//compute totals of each spot per level
	int DESIRED_MOTORCYCLE_SPOTS = SPOTS_PER_LEVEL * (0.01 * MOTORCYCLE_SPOTS_PERCENT);
	int DESIRED_LARGE_SPOTS = SPOTS_PER_LEVEL * (0.01 * LARGE_SPOTS_PERCENT);

	// compute rows in each level
	int ROWS_PER_LEVEL = SPOTS_PER_LEVEL / SPOTS_PER_ROW;

	// create lot
	Lot* L = new Lot();

	// create levels in Lot
	L->addLevels(NUM_OF_LEVELS);
	L->levelCount = NUM_OF_LEVELS;
	for(int i = 0; i < NUM_OF_LEVELS; i++){

		// create level contents
		Level level = L->getLevel(i);
		level.rows = new Row[ROWS_PER_LEVEL];
		level.rowCount = ROWS_PER_LEVEL;

		int motorcycleSpotsToAdd = DESIRED_MOTORCYCLE_SPOTS;
		int compactSpotsToAdd = SPOTS_PER_LEVEL - DESIRED_MOTORCYCLE_SPOTS - DESIRED_LARGE_SPOTS;
		int largeSpotsToAdd = DESIRED_LARGE_SPOTS;

		for(int j = 0; j < ROWS_PER_LEVEL; j++){

			// create row in Level
			level.rows[j].spotCount = SPOTS_PER_ROW;
			for(int k = 0; k < SPOTS_PER_ROW; k++){

				// create spots in Row
				// this section makes it such that the motorcycle spots are created first
				// followed by the compact spots
				// followed by the large spots
				Spot* spot;
				if(motorcycleSpotsToAdd > 0){
					spot = new MotorcycleSpot();
					motorcycleSpotsToAdd = motorcycleSpotsToAdd - 1;
				} else if(compactSpotsToAdd > 0){
					spot = new CompactSpot();
					compactSpotsToAdd = compactSpotsToAdd - 1;
				} else if(largeSpotsToAdd > 0){
					spot = new LargeSpot();
					largeSpotsToAdd = largeSpotsToAdd - 1;
				} else {
					// should be unreachable.
					cout << "UNREACHABLE" << endl;
				}

				level.rows[j].setSpot(k, spot);

			}
		}
		L->levels[i] = level;
	}

	// print empty starting lot
	cout << L->toString() << endl;

	// Uncomment/comment any of the following lines to test functionality.
	parkVehicle(L, Vehicle::V_MOTORCYCLE, 0, 1);
	parkVehicle(L, Vehicle::V_CAR, 0, 1);
	parkVehicle(L, Vehicle::V_BUS, 0, 1);
	parkVehicle(L, Vehicle::V_MOTORCYCLE, 0, 1);
	removeVehicleSpot(L, 0, 0, 6);
	removeVehicleSpot(L, 0, 2, 4, true);
	//parkVehicle(L, Vehicle::V_CAR, 0, 1); // park 1 car in the first available spot
	//parkVehicle(L, Vehicle::V_MOTORCYCLE, 1, 3); // park 3 motorcycles in the random spot
	//parkVehicle(L, Vehicle::V_BUS, 0, 2); // park 2 buses in first available spot

	//parkVehicleSpot(L, Vehicle::V_CAR, 0, 1, 0); // park a car at level 0, row 1, spot 0
	//parkVehicleSpot(L, Vehicle::V_CAR, 0, 1, 1); // park a car at level 0, row 1, spot 1
	//removeVehicleSpot(L, 0, 1, 0, false); // remove a car from level 0, row 1, spot 0

	//parkVehicleSpot(L, Vehicle::V_BUS, 1, 2, 4); // park a bus on level 1, row 2, spot 4
	//removeVehicleSpot(L, 1, 2, 4, true); // remove a bus at level 1, row 2, spot 4

	//parkVehicleSpot(L, Vehicle::V_CAR, 0, 1, 1); // park a car at level 0, row 1, spot 1


	delete L;

	return 0;
}
