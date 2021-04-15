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
    int from = 1, to = 7;

    //pg->OrderRide(from, to, Economy);
    //dg->driver = d;
    //for (int i = from; i <= to; i++)
    //{
    //    //driver set is in ride (order)
    //    dg->Move(i);
    //    //
    //    pg->WhereAmI();
    //    //driver set finished ride (order)
    //}
    dg->PrintOrderHistory();
    vector<Order*> av = dg->GetOrdersAvailable();
    
    
    
    cout << "!";
}

