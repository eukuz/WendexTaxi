#pragma once
#include <string>
#include "Driver.h"
using namespace std;
class DriverGateway
{
public:
	void Login(string Name);
	void Move(int x);
	Driver* driver;
};

