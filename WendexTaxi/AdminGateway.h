#pragma once
#include <string>
#include "Admin.h"
#include "Passenger.h"
#include "Driver.h"
#include "Car.h"
using namespace std;
class AdminGateway
{
public:
	Admin* admin;
	void Login(string Name);
	void Block(Driver* driver, bool block);
	void Block(Passenger* passenger, bool block);
	void Validate(Car* car, bool validate);
	

};

