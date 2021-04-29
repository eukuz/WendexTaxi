#pragma once
#include <string>
using namespace std;
class Driver
{
public:
	int ID;
	string Name;
	int CarID;
	bool IsWorking;
	bool IsRiding;
	float Rating;

	Driver(int id, string name, int carid, bool isworking, bool isriding, float rating) :
		ID(id), Name(name), CarID(carid), IsWorking(isworking), IsRiding(isriding), Rating(rating) {};
};

