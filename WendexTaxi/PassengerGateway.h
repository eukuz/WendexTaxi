#pragma once
#include <string>
#include <vector>
#include "Passenger.h"
#include "Enums.h"
#include "PaymentMethod.h"
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
	vector<PaymentMethod*> GetListOfMethodsAvailable();
	void UpdateMyListOfPaymentMethods(vector<PaymentMethod*> payments);
};



