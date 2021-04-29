#pragma once
#include <string>
#include "Driver.h"
#include "Order.h"
#include "Car.h"
#include "Enums.h"
#include <vector>
using namespace std;
class DriverGateway
{
public:
	void Login(string Name);
	void Move(int x);
	Driver* driver;
	void PrintOrderHistory();
	void StartRide(Order* order);
	void FinishRide(Order* order);
	Car* GetMyCar();
	vector<Order*> GetOrdersAvailable();
	void SetStatus(DriverStatus status);
};

