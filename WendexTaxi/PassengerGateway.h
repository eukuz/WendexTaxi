#pragma once
#include <string>
#include "Passenger.h"
#include "Enums.h"
using namespace std;
class PassengerGateway
{
public:
	void Login(string Name);
	Passenger* passenger;
	void PrintOrderHistory();
	//void AddPaymentMethod
	void CheckRide(int from, int to, CarTypes type);
	void OrderRide(int from, int to, CarTypes type); 
	void WhereAmI();
};



