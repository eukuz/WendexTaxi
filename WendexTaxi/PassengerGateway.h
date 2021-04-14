#pragma once
#include <string>
#include "Passenger.h"
using namespace std;
class PassengerGateway
{
public:
	void Login(string Name);
	Passenger* passenger;

};

