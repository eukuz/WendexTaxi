#include "PassengerGateway.h"
#include "DBShell.h"
#include <iostream>
#include "Enums.h"


void PassengerGateway::Login(string Name)
{
	this->passenger = DBShell::getPassenger(Name);
}

void PassengerGateway::PrintOrderHistory()
{
	DBShell::PrintOrdersP(this->passenger);
}

void PassengerGateway::CheckRide(int from, int to, CarTypes type)
{
	int distance = from > to ? from - to : to - from;
	cout << "Time :" << distance << " Price: " <<  distance*type<<endl;
}

void PassengerGateway::OrderRide(int from, int to, CarTypes type)
{
	DBShell::OrderRide(this->passenger, from, to, type);

}

void PassengerGateway::WhereAmI()
{
	int x = DBShell::GetPassengerCoordinates(this->passenger);
	if (x != NULL)
		cout << this->passenger->Name << " is at coordinates: " << x<< endl;
	else
		cout << this->passenger->Name << " is'nt at ride " << endl;
}

vector<PaymentMethod*> PassengerGateway::GetListOfMethodsAvailable()
{
	return DBShell::GetListOfPayments();
}

void PassengerGateway::UpdateMyListOfPaymentMethods(vector<PaymentMethod*> payments)
{
	DBShell::SetListOfPayments(this->passenger, payments);
}
