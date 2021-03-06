// WendexTaxi.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "DBShell.h"
#include "DriverGateway.h"
#include "PassengerGateway.h"
#include "AdminGateway.h"
#include "Enums.h"

int main()
{
	DriverGateway* dg = new DriverGateway();
	PassengerGateway* pg = new PassengerGateway();
	AdminGateway* ag = new AdminGateway();
	dg->Login("Dave"); //Login in the system as a Driver
	pg->Login("Peter");//Login in the system as a Passenger
	ag->Login("Amelie"); //Login in the system as a Passenger

	pg->PrintOrderHistory();

	Driver* d = DBShell::findDriver(Comfort);
	int from = 6, to = 20;

	pg->CheckRide(from, to, Business);  // Checking a ride
	pg->CheckRide(from, to, Comfort);

	pg->OrderRide(from, to, Comfort, 1); // ordering a ride

	vector<Order*> av = dg->GetOrdersAvailable();

	dg->driver = d;
	dg->StartRide(av.at(0)); //accepting a ride by a driver

	for (int i = from; i <= to; i++) //the actual ride
	{
		dg->Move(i);
		pg->WhereAmI(); //Get passenger's coordiantes during the ride
	}
	dg->FinishRide(av.at(0));

	dg->PrintOrderHistory(); //The ride appears in the order history when finished


	pg->PrintOrderHistory(); //get the order history of a passanger and a bill
	int bill = pg->GetBill(10);

	vector<PaymentMethod*> pays = pg->GetListOfMethodsAvailable(); //get & update the list of payment methods
	pg->UpdateMyListOfPaymentMethods(vector<PaymentMethod*>(&pays[0], &pays[2]));


	Car* car = dg->GetMyCar(); //get a car of a Driver

	dg->SetStatus(NotWorking); //Set a status for a driver

	vector <int> adrs = pg->GetListOfPinnedAdresses(); //Get Update Pinned Addresses of a user
	adrs.push_back(42);
	adrs.push_back(11);
	pg->UpdateMyListOfPinnedAddresses(adrs);

	Car cBusiness = Car(-1, "a", Business, 1, "black", "12d"); //Park in front of the enrance check
	Car cComfort = Car(-2, "b", Comfort, 1, "black", "12d");

	cBusiness.ParkInFrontOfTheEntrance();
	cComfort.ParkInFrontOfTheEntrance();

	ag->Block(pg->passenger, true); //Block a passanger
	ag->Block(dg->driver, true); //Block a driver

	pg->OrderRide(1, 2, Business, 1); ////will cause an execption because the passenger is blocked 

	car = dg->GetMyCar(); //get a car of a Driver

	ag->Validate(car, false); //validate or unvalidate a car

	av = dg->GetOrdersAvailable();

	dg->StartRide(av.at(0)); //will cause an execption because the driver is blocked and their car is unvalidated 

	ag->ShowDB();
	cout << "Finished!";
}

