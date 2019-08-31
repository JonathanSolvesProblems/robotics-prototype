#include <Arduino.h>
#include <vector>

class Sensor{
public:
	Sensor(int, string, int); // initializes device address, name, and sensitivity factor
	void setConfigurationRegisters(const int &);
	void setDataRegisters(const int &);
	float sensitivityFactor; // From datasheet
private:
	int address;
	string name;
	std::vector<int> configurationRegisters;
	std::vector<int> configurationRegistersValues;
	std::vector<int> dataRegistersAddresses;
	float sensitivityFactor; // From datasheet
};