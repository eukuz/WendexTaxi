#pragma once
#include <string>
#include "Passenger.h"
#include "Driver.h"
#include "Car.h"
using namespace std;
class DBShell
{
public:
	static Passenger* getPassenger(string Name);
	static Driver* getDriver(string Name);
	static void MoveDriver(Driver* driver, int x);
	static void PrintOrders(Passenger* passenger);
	static void GetCar(string Number);
};

