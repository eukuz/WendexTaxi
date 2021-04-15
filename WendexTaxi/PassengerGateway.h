#pragma once
#include <string>
#include <vector>
#include "Passenger.h"
#include "Enums.h"
#include "PaymentMethod.h"
#include "Order.h"
using namespace std;
class PassengerGateway
{
public:
	void Login(string Name);
	Passenger* passenger;
	void PrintOrderHistory();
	static int CheckRide(int from, int to, CarTypes type);
	void OrderRide(int from, int to, CarTypes type); 
	int GetBill(int OrderID); 
	void WhereAmI();
	vector<PaymentMethod*> GetListOfMethodsAvailable();
	void UpdateMyListOfPaymentMethods(vector<PaymentMethod*> payments);
};



