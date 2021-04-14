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
    dg->Move(9);
    pg->CheckRide(0, 10, Business);
    

    cout << "!";
}

