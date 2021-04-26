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


    /*pg->PrintOrderHistory();
    

    pg->CheckRide(0, 10, Business);
    pg->CheckRide(10, 2, Economy);

    Driver* d = DBShell::findDriver(Economy);
    int from = 1, to = 7;

    pg->OrderRide(from, to, Economy);

    vector<Order*> av = dg->GetOrdersAvailable();

    dg->driver = d;
    dg->StartRide(av.at(0));
    for (int i = from; i <= to; i++)
    {
        dg->Move(i);
        pg->WhereAmI();
    }
    
    dg->FinishRide(av.at(0));*/

    //dg->PrintOrderHistory();
    
   
 /*   vector<PaymentMethod*> pays = pg->GetListOfMethodsAvailable();

    pg->UpdateMyListOfPaymentMethods(vector<PaymentMethod*>(&pays[0],&pays[2]));*/

 /*   pg->PrintOrderHistory(); //get the order history of a passanger and a bill
    int bill = pg->GetBill(2);
    */

    //Car* car = dg->GetMyCar(); //get a car of a Driver
    //
    //dg->SetStatus(NotWorking); //Set a status for a driver



    //vector <int> adrs = pg->GetListOfPinnedAdresses(); //Get Update Pinned Addresses of a user
    //adrs.push_back(13);
    //adrs.push_back(28);
    //pg->UpdateMyListOfPinnedAddresses(adrs);


    pg->PrintOrderHistory();

    cout << "Finished!";
}

