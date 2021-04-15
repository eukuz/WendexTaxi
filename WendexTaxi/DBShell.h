#pragma once
#include "Passenger.h"
#include "Driver.h"
#include "Car.h"
#include "Enums.h"
#include "Order.h"
#include <vector>
using namespace std;
class DBShell
{
public:
	static Passenger* getPassenger(string Name);
	static Driver* getDriver(string Name);
	static Driver* findDriver(CarTypes type);
	static void MoveDriver(Driver* driver, int x);
	static void PrintOrdersP(Passenger* passenger);
	static void PrintOrdersD (Driver* driver);
	static void GetCar(string Number);
	static void OrderRide(Passenger* p, int from, int to, CarTypes type);
	static int GetPassengerCoordinates(Passenger* p);
	static vector <Order*> GetOrders(Driver* d);
	static void StartRide(Driver* d,Order* o);
	static void UpdateDriverStatus(Driver* d, DriverStatus status);
	static void FinishRide(Driver* d,Order* o);
};

