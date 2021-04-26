#pragma once
#include "Passenger.h"
#include "Driver.h"
#include "Admin.h"
#include "Car.h"
#include "Enums.h"
#include "Order.h"
#include "PaymentMethod.h"
#include <vector>
using namespace std;
class DBShell
{
public:
	static Passenger* getPassenger(string Name);
	static Driver* getDriver(string Name);
	static Admin* getAdmin(string Name);
	static Driver* findDriver(CarTypes type);
	static void MoveDriver(Driver* driver, int x);
	static void PrintOrdersP(Passenger* passenger);
	static void PrintOrdersD (Driver* driver);
	static Car* GetCar(int carId);
	static void OrderRide(Passenger* p, int from, int to, CarTypes type);
	static int GetPassengerCoordinates(Passenger* p);
	static vector <Order*> GetOrders(Driver* d);
	static void StartRide(Driver* d,Order* o);
	static void UpdateDriverStatus(Driver* d, DriverStatus status);
	static void FinishRide(Driver* d,Order* o);
	static vector <PaymentMethod*> GetListOfPayments();
	static void SetListOfPayments(Passenger* p, vector<PaymentMethod*> payments);
	static vector <int> GetListOfPinnedAdresses(Passenger* p);
	static void SetListOfPinnedAdresses(Passenger* p, vector<int> addresses);
	static Order* GetOrderByID(int orderID);
	static void Block(Driver* driver, bool block);
	static void Block(Passenger* passenger, bool block);
	static void Validate(Car* car, bool block);
};

