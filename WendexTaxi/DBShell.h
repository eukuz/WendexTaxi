#pragma once
#include <string>
#include "Passenger.h"
#include "Driver.h"
using namespace std;
class DBShell
{
public:
	static Passenger* getPassenger(string Name);
	static Driver* getDriver(string Name);
};

