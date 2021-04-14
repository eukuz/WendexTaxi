// WendexTaxi.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "DBShell.h"
#include "DriverGateway.h"
#include "PassengerGateway.h"
#include "Enums.h"

int main()
{
    DriverGateway* dg = new DriverGateway();
    PassengerGateway* pg = new PassengerGateway();
    dg->Login("Dave");
    pg->Login("Peter");
    pg->PrintOrderHistory();

    pg->CheckRide(0, 10, Business);
    pg->CheckRide(10, 2, Economy);

    Driver* d = DBShell::findDriver(Economy);

    pg->OrderRide(-1, 12, Economy);
    

    cout << "!";
}

