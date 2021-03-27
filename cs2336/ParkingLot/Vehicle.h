/*
 * Vehicle.h
 *
 *  Author: Carter Hawks from CS2336.001
 *  To run: the main() is located in ParkingLot.cpp
 *      Different sections of the code are commented out;
 *      these sections accomplish the different variations of the parking lot.
 */

// Vehicle: an abstract class that illustrates the format for the descendant Vehicle objects. It does nothing on its own.

#ifndef VEHICLE_H_
#define VEHICLE_H_

class Vehicle {
public:
	Vehicle();
	virtual ~Vehicle();
	virtual int getVehicleType();
	static const int V_MOTORCYCLE = 1;
	static const int V_CAR = 2;
	static const int V_BUS = 3;
};

#endif /* VEHICLE_H_ */
