#include "Sensor.h"

/****************
public functions
****************/

// Constructor
Sensor::Sensor(int addr, string name, int s){
	address = addr; 		// initialize device address
	name = name; 			// initialize device name
	sensitivityFactor = s;	// initialize the sensitivity factor
}

// Assigns register-value pairs
void Sensor::setConfigurationRegisters(const int (&arr)){
	for(size_t i = 0; i < arr.size(); i += 2){
		configurationRegistersAddresses.push_back(arr[i]);
		configurationRegistersValues.push_back(arr[i + 1]);
	}
}

void Sensor::setDataRegisters(const int (&arr)){
	for(size_t i = 0; i < arr.size(); i += 2){
		dataRegistersAddresses.push_back(arr[i]);
	}	
}

/****************
private functions
****************/