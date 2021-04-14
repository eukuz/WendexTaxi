#pragma once
#include <string>
using namespace std;
class Passenger
{
public:
	int ID;
	string Name;
	float Rating;

	Passenger(int id, string name, float rating) :ID(id), Name(name), Rating(rating) {};
	
};

